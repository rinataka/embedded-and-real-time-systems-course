// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022), 
// Work package 4, 
// Exercise 2: ANALOG TIMER
// Submission code: 754-Cc
// tinkerCad link: https://www.tinkercad.com/things/jswD3d5kL1p-brave-gaaris-trug/editel?sharecode=5hnaq_DJHEOdriZh9E1SndFJzdqjSjGmA4bGBgpunXc

// import servo library
#include <Servo.h> 

//define pins the servos are connected to
#define SEC_SERVO_PIN 13 
#define MIN_SERVO_PIN 10

Servo servoSec; //decalre servo for seconds
Servo servoMin; //declare servo for minutes
//initilise variables for positions of the servos in degrees (0-180)
int posSec = 0;  //postions for servo that counts seconds
int posMin = 0;  //postions for servo that counts minutes

void setup()
{
  //attach servos to pins
  servoSec.attach(SEC_SERVO_PIN); //servo that represents seconds
  servoMin.attach(MIN_SERVO_PIN); //servo that represents minutes

  Serial.begin(9600); //for printing to monitor
}

void loop()
{
  delay(1000); //wait one second  
  posSec+=3;//3 degrees represents a second, add to posSec
  posMin = (posSec/180)*3; //calculate posMin depending on posSec, 3 degrees represents one minute
  //change position of servos 
  servoSec.write(posSec%180); //modulo to make sure it writes a degree between 0 and 180
  servoMin.write(posMin%180); //modulo to make sure it writes a degree between 0 and 180
  // print to monitor
  Serial.print(posMin/3); //calculate minutes depending on current degree position, every three degrees represents one minute
  Serial.print(":");
  Serial.println((posSec/3)%60); // calculate seconds depending on current degree position, every third degrees represents one second, resets to 0 every 60 seconds (%)

}
