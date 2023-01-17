// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022), 
// Work package 5, 
// Exercise 1: SET-UP  
// Submission code: Czg532

// reused code from wp3 exercise 1. 

#define PIN_LED_2 4
#define PIN_BUTTON 2
#define PIN_LED_1 7

void setup()
{
  // Open the serial port at 9600 bps (bits per second)
  Serial.begin(9600); 
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

void loop()
{
  // Needs Serial.begin(9600); in the setup()
  digitalWrite(PIN_LED_1, HIGH);
  delay(200);
  digitalWrite(PIN_LED_1, LOW);
  delay(200);
  digitalWrite(PIN_LED_2, digitalRead(PIN_BUTTON));
  delay(100); // Wait for 100 millisecond(s)
}