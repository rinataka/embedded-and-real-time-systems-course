// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022), 
// Work package 3, 
// Exercise 2: TEMPERATURE AND LIGHT METER  
// Submission code: 761-D!?5

#include <Servo.h>

// Defining Variables
int photoSensor = 0; // variable to store read value from A1
double photoPercentege = 0.0; // variable to store calculated light intensity in percentege
int tempSensor = 0; // variable to store read value from A0
double tempC = 0.0; // variable to store calculated temp in celsius
double voltage = 0.0; // variable to store calculated voltage 

//Defining pins for led lights
#define RED_LED 13 
#define GREEN_LED 11
#define BLUE_LED 9

// min and max values of photoresistor with the resistor resistance set to 20 Ω
const int MIN = 0;
const int MAX = 39;

void setup()
{
    pinMode(A0, INPUT); // analog photoresistor
    pinMode(A1, INPUT); // analog tempsensor

    pinMode(RED_LED, OUTPUT);   // red light
    pinMode(GREEN_LED, OUTPUT); // green light
    pinMode(BLUE_LED, OUTPUT);  // bluelight

    Serial.begin(9600);
}

void loop()
{
    // read temp sensor value
    tempSensor = analogRead(A1);
    // calculate voltage
    voltage = tempSensor * (5019.5 / 1024.0); // 5000 to get millivots.
                                              // convert millivolts into temperature
    tempC = (voltage - 500.0) / 10.0;   // 500 is the offset
    // print out the temperature
    Serial.print(tempC);
    Serial.println(" degrees in C");

    // read photoresistor
    photoSensor = analogRead(A0);
    // calculate percentege of photoSensor
    photoPercentege = map((photoSensor), MIN, MAX, 0, 100);
    // print the photoresistor value in percentege
    Serial.println(photoPercentege);

    checkDependency(); /* calling function checkDependency() with no program arguments 
    supported and no return value. Function call to check dependency between light intensity 
    and temperature, and indicate dependency through led*/
    
    delay(500); // Wait for 500 millisecond(s)
}

void checkDependency()
{
    // when photoresistor is 0%
    if (photoPercentege == 0.0)
    {
        if (tempC <= -12) // if temp is -12 or less
        {                                  
            digitalWrite(GREEN_LED, HIGH); // green light will turn on
            digitalWrite(RED_LED, LOW);
            digitalWrite(BLUE_LED, LOW);
        }
        else
        {
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(RED_LED, HIGH); // else red light will turn on which indiciates too high temp
            digitalWrite(BLUE_LED, LOW);
        }
    }
    else if (photoPercentege >= 1.0 && photoPercentege <= 20.0)
    { // when photoresistor is 1% -20%
        if (tempC >= -12 && tempC <= 0) // if temp is -12 - 0
        {                                 
            digitalWrite(GREEN_LED, HIGH); // green light will turn on
            digitalWrite(RED_LED, LOW);
            digitalWrite(BLUE_LED, LOW);
        }
        else if (tempC >= 0) // if temp is 0 or higher
        { 
            digitalWrite(BLUE_LED, LOW);
            digitalWrite(RED_LED, HIGH); // red light will turn on which indiciates too high temp
            digitalWrite(GREEN_LED, LOW);
        }
        else
        {
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(RED_LED, LOW);
            digitalWrite(BLUE_LED, HIGH); // else blue led will turn on which indicates too low temp
        }
    }
    else if (photoPercentege >= 21.00 && photoPercentege <= 60.0)
    { // when photoresistor is 21 - 60 %
        if (tempC >= 0 && tempC <= 20) // if temp 0-20
        {                                  
            digitalWrite(GREEN_LED, HIGH); // green light turn on
            digitalWrite(RED_LED, LOW);
            digitalWrite(BLUE_LED, LOW);
        }
        else if (tempC >= 21)  // if temp is 21 or higher
        {                               
            digitalWrite(BLUE_LED, LOW); // red light will turn on which indiciates too high temp
            digitalWrite(RED_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);
        }
        else
        {
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(RED_LED, LOW);
            digitalWrite(BLUE_LED, HIGH); // else blue led will turn on which indicates too low temp
        }
    }
    else if (photoPercentege >= 61.00 && photoPercentege <= 100.0)
    { // when photoresistor is 61-100%
        if (tempC >= 21)
        {
            digitalWrite(GREEN_LED, HIGH); // if temp is 21 or higher the green light will turn on
            digitalWrite(RED_LED, LOW);
            digitalWrite(BLUE_LED, LOW);
        }
        else
        {
            digitalWrite(BLUE_LED, HIGH); // else blue led will turn on which indicates too low temp
            digitalWrite(RED_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
        }
    }
}
