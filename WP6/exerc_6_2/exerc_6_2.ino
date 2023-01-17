// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022), 
// Work package 6, 
// Exercise 2: PARKING ASSISTANCE SYSTEM 
// Tinkercad: https://www.tinkercad.com/things/fCGJqcvHIcG-incredible-kasi-stantia/editel?sharecode=rQzy_3IjV_v2Yl0Q6yabLNgHedcDHjOXn7SLmbDnvfc
// Submission code: A352*



// Define the names for the pins 7, 9, 5, 4, 3 and 2.
#define ULTRASONIC_SENSOR_PIN 7
#define PIEZO_PIN 9
#define RED_LED_PIN_5 5
#define RED_LED_PIN_4 4
#define RED_LED_PIN_3 3
#define RED_LED_PIN_2 2


// Open serial port, set up each pin.
void setup()
{
  pinMode(ULTRASONIC_SENSOR_PIN, OUTPUT); // Set ULTRASONIC_SENSOR_PIN as OUTPUT.
  digitalWrite(ULTRASONIC_SENSOR_PIN, LOW); // Start ultrasonic sensor with zero value.
  pinMode(PIEZO_PIN, OUTPUT); // Set the speaker, PIEZO_PIN as OUTPUT.
  pinMode(RED_LED_PIN_5, OUTPUT); // Set RED_LED_PIN_5 as OUTPUT.
  pinMode(RED_LED_PIN_4, OUTPUT); // Set RED_LED_PIN_4 as OUTPUT.
  pinMode(RED_LED_PIN_3, OUTPUT); // Set RED_LED_PIN_3 as OUTPUT.
  pinMode(RED_LED_PIN_2, OUTPUT); // Set RED_LED_PIN_2 as OUTPUT.
  
  // Open the serial port at 9600 bps (bits per second).
  Serial.begin(9600);
}


// Measure distance with the ultrasonic sensor and depensing on the distance values
// a tone from the speaker indicates how close an object is. Also depending on the distance
// four leds will indicate how close the object is.
void loop()
{
  // Measure distance and print the values.
  Serial.print("Distance to object: ");
  int distance_in_cm = measureDistance(); // Call the measureDistance() function.
  Serial.print(distance_in_cm);
  Serial.println(" centimeters.");
  
  // If the object is closer than 25 cm, make the four leds blink 
  // and activate a tone from the speaker. 
  if(distance_in_cm < 25)
  {
    blink(); // Make all four leds blink.
    activateTone(distance_in_cm); // Activate tone from the speaker.
  }
  // If the object is between 25 cm and 30 cm, turn on all four leds and activate tone from the speaker. 
  else if(distance_in_cm >= 25 && distance_in_cm < 30)
  {
    turnOnLeds(); // Turn on all four leds.
    activateTone(distance_in_cm); // Activate tone from the speaker.
  }
  // If the object is between 30 cm and 200 cm, turn on the first led only and activate tome from the speaker.  
  else if(distance_in_cm >= 30 && distance_in_cm < 200)
  {
    turnOffLeds(); // First turn off all the leds.
    turnOnFirstLed(); // Turn on only the first led.
    activateTone(distance_in_cm); // Activate tone from the speaker.
  }
  // If the distance is between 200 cm and 250 cm, activate tone from the speaker and turn off the leds.
  else if(distance_in_cm >= 200 && distance_in_cm < 250)
  {
    activateTone(distance_in_cm); // Activate tone from the sepaker
    turnOffLeds(); // Turn off the four leds.
  }
  // Otherwise, turn off the fours leds and do not activate tone from the speaker.
  else
  {
    turnOffLeds();
  }
  
 // Wait for 150 milliseconds.
  delay(150);
}



// ****** Function measureDistance() ******
// No program arguments supported and returns distance as a long type.
// It measures using a ultrasonic sensor. First it outputs a pulse into the ultrasonic sensor pin, 
// then sets such a pin as input and listens for the returned pulse using the function pulseIn(). 
long measureDistance()
{
  // Factor to convert time into distance.
  float const time_to_distance = 0.01723;
  
  // Set ULTRASONIC_SENSOR_PIN as Output. 
  pinMode(ULTRASONIC_SENSOR_PIN, OUTPUT);
  
  // Write a zero to the output to clear the system and wait 2 microseconds.
  digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
  delayMicroseconds(2);
  
  // Write a one to the output to send a ping and wait for 10 microseconds.
  digitalWrite(ULTRASONIC_SENSOR_PIN, HIGH);
  delayMicroseconds(10);
  
  // Write a zero to the output to stop sending the ping.
  digitalWrite(ULTRASONIC_SENSOR_PIN, LOW);
  
  // Set ULTRASONIC:SENSOR_PIN to INPUT.
  pinMode(ULTRASONIC_SENSOR_PIN, INPUT);
   
  // Read a pulse from ULTRASONIC_SENSOR_PIN, 
  // pulseIn() waits for the pin to go from LOW to HIGH, starts timing, 
  // then waits for the pin to go LOW and stops timing. Finally, 
  // it returns the length of the pulse in microseconds. 
  // Next we convert the length of the pulse into distance in centimeters.
  return time_to_distance * pulseIn(ULTRASONIC_SENSOR_PIN, HIGH); 
}
// ------ End measureDistance() ------


// ****** Function blink() ******
// It takes no program arguments and does not return anything.
// Turn all four leds on then waits 20 milliseconds, turn off all four leds ans waits 20 milliseconds.
void blink()
{
  turnOnLeds(); // Turn on all four leds.
  delay(20); // Wait 20 milliseconds.
  turnOffLeds(); // Turn off all four leds.
  delay(20); // Wait 20 milliseoncds.
}
// ------ End blink() ------


// ****** Function turnOnLeds() ******
// It takes no program arguments and does not return anything.
// Sets all four led pins to a HIGH value.
void turnOnLeds()
{
  digitalWrite(RED_LED_PIN_5, HIGH); // Turn on RED_LED_PIN_5.
  digitalWrite(RED_LED_PIN_4, HIGH); // Turn on RED_LED_PIN_4.
  digitalWrite(RED_LED_PIN_3, HIGH); // Turn on RED_LED_PIN_3.
  digitalWrite(RED_LED_PIN_2, HIGH); // Turn on RED_LED_PIN_2.
}
// ------ End turnOnLeds() ------


// ****** Function turnOffLeds() ******
// It takes no program arguments and does not return anything.
// Sets all four led pins to a LOW value.
void turnOffLeds()
{
  digitalWrite(RED_LED_PIN_5, LOW); // Turn off RED_LED_PIN_5
  digitalWrite(RED_LED_PIN_4, LOW); // Turn off RED_LED_PIN_4
  digitalWrite(RED_LED_PIN_3, LOW); // Turn off RED_LED_PIN_3
  digitalWrite(RED_LED_PIN_2, LOW); // Turn off RED_LED_PIN_2
}
// ------ End turnOffLeds() ------


// ****** Function turnOnFirstLed() ******
// It takes no program arguments and does not return anything.
// Turn on only the fisrt led.
void turnOnFirstLed()
{
  digitalWrite(RED_LED_PIN_5, HIGH); // Turn on RED_LED_PIN_5
}
// ------ End turnOnFirstLed() ------


// ****** Function activateTone() ******
// Takes as input argument the distance measured by the ultrasonic sensor.
// Activate a tone from the speaker by setting the duration of the tone as well as its pitch according to the input distance.
// This function does not return anything.
void activateTone(int distance)
{
  // Convert a distance in the range of 0 cm and 250 cm into a pitch (frequency) in a range of 2000 and 52 Hertz.
  int pitch = map(distance, 0, 250, 2000, 52);
  // Convert a distance in the range of 0 cm and 250 cm into a duration in a range of 400 and 10 milliseconds.
  int duration = map(distance, 0, 250, 400, 10);
  // tone() generates a square wave of the specified frequency (and 50% duty cycle) on a pin for a given duration.
  tone(PIEZO_PIN, pitch, duration);
}
// ------ End activateTone() ------
