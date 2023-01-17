// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// group: 13 (2022), 
// Work package 3, 
// Exercise 1.2: SET-UP, 
// Submission code: 761-D!?5
// https://www.tinkercad.com/things/8a6Np2u6cje-exerc312/editel?sharecode=FRwr3BUe9CvB2wd-RbkVVEe-kqYiKr-ZS915Y8IN5bA

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