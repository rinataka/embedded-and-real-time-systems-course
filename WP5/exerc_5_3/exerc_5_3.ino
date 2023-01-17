// (C) Lina Boman, Graciela Coate Cano, Jina Dawood,
// Group: 13 (2022),
// Work package 5,
// Exercise 3: TEMPERATURE AND LIGHT METER
// Submission code: Czg532

/* NOTE: this exercise is based on the code from:
    " (C) Lina Boman, Graciela Coate Cano, Jina Dawood,
    Group: 13 (2022),
    Work Package 3,
    Exercise 2: TEMPERATURE AND LIGHT METER ".
    Adapted to run on the physical ARDUINO UNO R3 board. */

// Defining Variables
int photo_sensor = 0; // Variable to store read value from pin A0.
int photo_percentage = 0; // Variable to store calculated light intensity in percentage.
int temperature_sensor = 0; // Variable to store read value from pin A1.

float temperature_celsius = 0.0; // Variable to store calculated temperature in Celsius
float voltage = 0.0; // Variable to store the calculated voltage.

// Define pins for led lights, photoresistor sensor and temperature sensor.
#define RED_LED_PIN 13
#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 9
#define PHOTORESISTOR_SENSOR_PIN A0
#define TEMPERATURE_SENSOR_PIN A1

// Min and max values of photoresistor with the resistor resistance set to 10 kΩ.
const int MIN = 0;
const int MAX = 1023;

// Set up the pins to outputs.
void setup()
{
  // Configure led_pin as aoutput, correpsonding one red, one green and one blue.
  pinMode(RED_LED_PIN, OUTPUT);   // Red led.
  pinMode(GREEN_LED_PIN, OUTPUT); // Green led.
  pinMode(BLUE_LED_PIN, OUTPUT);  // Blue led.

  /* Note: the temperature sensor and photoresistor signals go to the analog input pins,
      so, they do not have to be set up as input, since they already are input pins. */

  // Opens the serial port at 9600 bps (bits per second),
  // To use ptint function.
  Serial.begin(9600);
}


// Measure temperature and ligth intensity at a given frequency.
// If the values of the temperature and light are inside the ranges, given by the table in the exercise 3 (WP5),
// the sensor measured considered as normal and the green led is turned on.
// otherwise, if the temperature is colder, for a given light intensity, the blue led is turned on,
// and when the temperatures are warmer for the given ligth intensity, the red led is turned on.
// Only one led is turned on at a time.

void loop()
{
  // Read temperature sensor value.
  temperature_sensor = analogRead(TEMPERATURE_SENSOR_PIN);
  // Convert the ADC reading to voltage. According to the data sheet of the sensor.
  voltage = (temperature_sensor / 1024.0) * 5.0;
  // Convert the voltage temperature in Celsius. According to the data sheet of the sensor.
  temperature_celsius = (voltage - 0.5) * 100;
  // Print out the temperature.
  Serial.print(temperature_celsius);
  Serial.println(" degrees in C");


  photo_sensor = analogRead(PHOTORESISTOR_SENSOR_PIN); // Read the photoresistor.
  delay(5);  // Wait for 5 milliseconds.
  photo_percentage = map(photo_sensor, MIN, MAX, 0, 100);  // Calculate percentage of photo_sensor.
  Serial.print(photo_percentage); // Print the photoresistor value in percentage.
  Serial.println(" photo percentage.");

  checkDependency(); // Call function checkDenendency().

  delay(1000); // Wait for 1000 milliseconds
}


// Function checkDependency() with no program arguments supported and no return value.
// Check dependency between light intensity and temperature, and indicate dependency through the leds red, green and blue.
void checkDependency()
{
  // When the photoresistor value is 0%.
  if (photo_percentage == 0.0)
  {
    // If the temperature is less than -12 Celsius.
    if (temperature_celsius < -12) 
    {
      // For the given interval of the photoresistor value, 
      // if the temperature is less than -12 Celsius 
      // we have normal values, we turn on the green led only.
      
      digitalWrite(GREEN_LED_PIN, HIGH); // Green led is turned on.
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      Serial.println("................. Normal Values .................");
    }
    else
    {
      // The temperature is higher for a photoresistor value of 0%,
      // we turn on the red led only.
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, HIGH); // Red led is turned on.
      digitalWrite(BLUE_LED_PIN, LOW);
    }
  }
  // When the photoresistor value is between 1% and 20%.
  else if (photo_percentage >= 1.0 && photo_percentage <= 20.0)
  { 
    // Given normal values, the green light turns on, the blue and red lights turn off.
    // The temperature is between -12 Celsius and 0 Celsius.
    if (temperature_celsius >= -12 && temperature_celsius < 0)
    {
      // For the given interval of the photoresistor value, 
      // if the temperature is greater or equal than -12 Celsius 
      // and less or equal to 0 Celsius, we have normal values, we turn on the green led only.
      digitalWrite(GREEN_LED_PIN, HIGH); // Green led is turned on.
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      Serial.println("................. Normal Values .................");
    }
    // If the temperature is 0 or higher.
    else if (temperature_celsius >= 0) 
    {
      // This temperature is considered high when the photoresistor value is greater or equal than 1% and less or equal than 20%.
      // In this case we turn on the red led only.
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, HIGH); // Red led is turned on.
      digitalWrite(GREEN_LED_PIN, LOW);
    }
    else
    {
      // This temperature is considered low when the photoresistor value is between 1% and 20%.
      // In this case we turn on the blue led only. 
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, HIGH); // Blue led is turned on.
    }
  }
  // If the photoresistor value is between 21% and 60%. 
  else if (photo_percentage >= 21.00 && photo_percentage <= 60.0)
  { 
    if (temperature_celsius >= 0 && temperature_celsius <= 20) // If temp 0-20
    {
      // For the given interval of the photoresistor value, 
      // if the temperature is between 0 Celsius and 20 Celsius 
      // we have normal values, we turn on the green led only.
      digitalWrite(GREEN_LED_PIN, HIGH); // Green led is turned on.
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      Serial.println("................. Normal Values .................");
    }
    else if (temperature_celsius >= 21) 
    {
      // If temperature is 21 Celsius or higher, the temperature is considered high and the red led is turned on only.
      digitalWrite(BLUE_LED_PIN, LOW); // Red light is turned on.
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
    }
    else
    {
      // If temperature is lower than 0 Celsius, the temperature is considered low and the blue led is turned on only. 
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, HIGH); // Blue led is turned on.
    }
  }
  // If the photoresistor values is between 61% and 100%.
  else if (photo_percentage >= 61.00 && photo_percentage <= 100.0)
  { 
    if (temperature_celsius >= 21)
    {
      // The temperature is greater or equal than 21 Celsius and is considered a normal value
      // then the green led is turned on.
      digitalWrite(GREEN_LED_PIN, HIGH); // Green led is turned on.
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      Serial.println("................. Normal Values .................");
    }
    else
    {
      // The temperature is lower than 21 Celsius and is considered low, so the blue led is turned on.
      digitalWrite(BLUE_LED_PIN, HIGH); // Blue led turned on.
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
    }
  }
}
