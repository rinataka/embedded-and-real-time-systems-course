// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022), 
// Work package 5, 
// Exercise 1: TEMPERATURE METER 
// Submission code: Czg532

// reused code from wp4 exercise 1. Did small changes such as removing the use of 
//timerOne library and instead using DHT library to read the temperature. 

#include <DHT.h>

// pins
#define RED_LED 13
#define ORANGE_LED 11
#define GREEN_LED 9
#define BLUE_LED 7
#define WHITE_LED 5
#define DHTPIN 2 // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // define DHT 11 to read temperature 

float tempC = 0.0;   // variable to store temperature in celsius

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// initializing variables with different temperatures
int const minusTen = -10;

int const zero = 0;

int const ten = 10;

int const twenty = 20;

int const thirty = 30;

int const fourty = 40;

void setup()
{
  // Open the serial port at 9600 bps (bits per second),
  // To use Serial.println()
  Serial.begin(9600);

dht.begin(); // Initialize the DHT sensor
  
  // Configure led pins to output
  pinMode(RED_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
}

void loop()
{

  tempC = dht.readTemperature(); // read temperature and store in variable 
  
  // print temperature
  Serial.print(tempC);
  Serial.println(" degrees in C");
 
  turn_led(); // calling function to turn on leds based on temperature
  delay(500); // Wait for 500 millisecond(s)
}

void turn_led()
{
  // when temperature is -10 - 0
  if (tempC >= minusTen && tempC <= zero)
  {
    digitalWrite(WHITE_LED, HIGH); // first white led will turn on and the rest will turn off
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > zero && tempC <= ten)
  {
    // when temperature is 1-10
    digitalWrite(WHITE_LED, HIGH); // white led will turn on
    digitalWrite(BLUE_LED, HIGH);  // blue led will turn on and the rest will turn off
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > ten && tempC <= twenty)
  {
    // when temperature is 11-20
    digitalWrite(WHITE_LED, HIGH); // white led will turn on
    digitalWrite(BLUE_LED, HIGH);  // blue led will turn on
    digitalWrite(GREEN_LED, HIGH); // green led will turn on and the rest will turn off
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > twenty && tempC <= thirty)
  {
    // when temperature is 21 - 30
    digitalWrite(WHITE_LED, HIGH);  // white led will turn on
    digitalWrite(BLUE_LED, HIGH);   // blue led will turn on
    digitalWrite(GREEN_LED, HIGH);  // green led will turn on
    digitalWrite(ORANGE_LED, HIGH); // orange led will turn on and the rest will turn off
    digitalWrite(RED_LED, LOW);
  }
  else if (tempC > thirty && tempC <= fourty)
  {
    // when temperature is 31 - 40
    // all lights will turn on 
    digitalWrite(WHITE_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(ORANGE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  }
  else
  {
    // when temperature is outside range which is -10 - 40
    // all light will be turned off
    digitalWrite(RED_LED, LOW);
    digitalWrite(ORANGE_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(WHITE_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
}