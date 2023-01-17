// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022)
// Work package 4
// Exercise 3: ADDRESSABLE LEDS.
// Submission code: 754-Cc
// https://www.tinkercad.com/things/gIWgcrw0Nsc-sizzling-trug-bojo/editel?sharecode=mM_hLxMztOd6jdjT_ol94-e7FmgbOCt90Levfl5QAqo

// Library to use the NeoPixel ring.
#include <Adafruit_NeoPixel.h>

// Bellow (lines 12, 13 and 14) we define the names for the pins 6, 5 and A0.
#define NEOPIXEL_RING_PIN 6
#define LED_PIN 5
#define TEMPERATURE_SENSOR_PIN A0

// Initialize number_of_leds to 24, since the ring has 24 leds. 
int const number_of_leds = 24;

// NeoPixel constructor whit three program parameters: number_of_leds, NEOPIXEL_RING_PIN , and pixel type.
Adafruit_NeoPixel neopixel_ring = Adafruit_NeoPixel(number_of_leds, NEOPIXEL_RING_PIN , NEO_GRB + NEO_KHZ800);

// Opens serial port, sets up each pin.
void setup()
{
  // Opens the serial port at 9600 bps (bits per second), 
  // to use Serial.println()
  Serial.begin(9600);
  neopixel_ring.begin(); // Configures NeoPixel pin for output.
  
  // Set TEMPERATURE_SENSOR_PIN as input
  pinMode(TEMPERATURE_SENSOR_PIN, INPUT);
  // Set LED_PIN as output.
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize the leds to white
  for(byte i = 0; i < number_of_leds; i++)
  {
    // Colors go from 0 to 255, each value corresponds to Red, Green and Blue.
    neopixel_ring.setPixelColor(i, 0, 0, 0); 
    // Transmits pixel data in RAM to NeoPixels.
    neopixel_ring.show(); 
  }
}

// In the following loop, it measures periodically the temperature
// and displays the value based on the temperature sensor on the NeoPixel ring.
// When it reaches the maximum value (when all the leds in the ring are on), 
// it turns on a single red led to indicate that it sensed the maximum temperature.
void loop()
{
  // Turn off the single led.
  digitalWrite(LED_PIN, LOW);
  
  // Read temperature sensor value.
  int temperature_sensor = analogRead(TEMPERATURE_SENSOR_PIN);

  // Calculate voltage from the value read from the temperature sensor,
  // Below we define a factor to perform the voltage convertion (5000 to get millivots,
  // convert millivolts into temperature).
  double const sensor_readings_to_millivolts_factor = 5019.5 / 1024.0;
  // Perform the conversion to voltage.
  double const voltage = temperature_sensor * sensor_readings_to_millivolts_factor; 
  
  // Define these constants to convert the voltage to temperature in celsius.
  double const voltage_offset = 500.0;
  // Factor used for the conversion to celsius.
  double const voltage_to_celsius_factor = 1 / 10.0;
  // Perfomr conversion to celsius.
  double const temperature_celsius = (voltage - voltage_offset) * voltage_to_celsius_factor;
  // print out the temperature in celsius
  Serial.print(temperature_celsius);
  Serial.println(" degrees in C");
  
  // We want the leds in the neopixel ring to change lineally proportional to the changes in the temperature sensor,
  // i.e., when te temperature is at its minimum value (-40 celsius), we want to turn on only one led (led with index zero),
  // then when the temperature is at its maximum value (125 celsius), we want to turn on all the leds in the ring (leds from index zero
  // to index 23) and when the temperature is at its mid value, we want to turn on only oe half of the ring
  // (leds with indices from zero to eleven). 
  // Considering the above points (pairs of temperature values and led indices from the ring)
  // we compute the equation of a line, 
  // which is used to convert each temperature value into their corresponding maximum led index that should be turn on.
  // To compute the slope and the y-intercept of the line equation, we consider the following points: 
  // (-40 celsius, index 0 of the neopixel ring led),
  // and (125 celsius, index 23 of the neopixel ring led).
  double const slope = 23.0 / 165.0; // Calculated the slope of the line equation.
  double const y_intercept = 920.0 / 165.0; // Calculated y-intercept of the line equiation.
  // Using line equation, we obtain the maximum index of the led to be turn on.
  double led_number = slope * temperature_celsius + y_intercept; // y = m * x + b
  int max_number_of_leds_on = (int) led_number; // Casting to integer.
  Serial.print(" MAX number of leds on: "); // Show the number of leds to be turned on.
  Serial.println(max_number_of_leds_on + 1); // +1, as our leds are indexed from 0 to 23.
  
  
  // Turn on the leds with indices 0 to max_number_of_leds_on.
  for(byte i = 0; i <= max_number_of_leds_on; i++)
  {
    // Turn on the ith led and set the color Red = 0, Green = 128 and Blue = 255. Sets a blueish color.
    neopixel_ring.setPixelColor(i, 0, 128, 255);
  }
  // Turn off the rest of the leds.
  for (byte j = max_number_of_leds_on + 1; j < number_of_leds; j++)
  {
    // Turn off the ith led by setting Red = 0, Green = 0 and Blue = 0.
    neopixel_ring.setPixelColor(j, 0, 0, 0);
  }
  
  // Turn on the single red led when the maximum temperature is reached.
  if (max_number_of_leds_on >= number_of_leds - 1)
  {
    // Turn on LED_PIN
    digitalWrite(LED_PIN, HIGH); 
  }
  
  // Call the show function from the neopixel_ring
  neopixel_ring.show();
  // Adds a delay of 100 millisecond.
  delay(100);
}