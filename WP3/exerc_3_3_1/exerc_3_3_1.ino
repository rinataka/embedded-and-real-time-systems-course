// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022), 
// Work package 3, 
// Exercise 2: TEMPERATURE METER V 2.0 
// Submission code: 761-D!?5


// Defining Variables
int tempSensor = 0; // variable to store read input from A0
double tempC = 0.0;  // variable to store calculated temperature in celcius
double voltage = 0.0;  // variable to store calculated voltage

void setup()
{
    pinMode(A0, INPUT); // pin for analog temp36
    Serial.begin(9600);
}

void loop()
{
    // read temp sensor value
    tempSensor = analogRead(A0);
    // calculate voltage
    voltage = tempSensor * (5019.5 / 1024.0); // 5000 to get millivots.
    // print voltage 
    Serial.print(voltage);    
    Serial.println(" voltage");
    // convert millivolts into temperature
    tempC = (voltage - 500.0) / 10.0;         // 500 is the offset
    // print out the temperature
    Serial.print(tempC); 
    Serial.println(" degrees in C");

    delay(500); // Wait for 500 millisecond(s)
}
