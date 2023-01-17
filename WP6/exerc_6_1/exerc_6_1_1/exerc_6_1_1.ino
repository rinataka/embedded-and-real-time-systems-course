// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022), 
// Work package 6, 
// Exercise 1: DC MOTOR CONTROLLER, Task 1
// Tinkercad: https://www.tinkercad.com/things/87kYbyaoxcm-exerc611/editel?sharecode=mL1bJuiAnBECSMK8v2WwnUJrcBxMFzvaGE3nFTdvgkc
// Submission code: A352*

// Includes parts from WP 6 Exercise 1 Template DIT 632

#define ENCA 2
#define ENCB 3
#define PWM1 5
#define PWM2 6

int pos = 0; // Position in ticks

int degtarget = 0; // Target position in degrees

int speed = 0; // Desired motor speed

int e = 0; // error or distance to target

int a = 0; // a-encoder signal
int b = 0; // b-encoder signal


void setup() {
 
  Serial.begin(9600);
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);  

  // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
  analogWrite(PWM2, 10); 
  delay(1000); // TinkerCad bug
  analogWrite(PWM1, 10);
  // Get input 
  speed = getSpeedInput();
}

void loop() {
  
    // Stop the motor, but not to zero because then TinkerCad dies....
  analogWrite(PWM1, 10);
  delay(1000); // TinkerCad...bug
  analogWrite(PWM2, 10);
  
    // Check if motor rotated all the way around, and reset counter
    if (pos > 2299){
      pos = pos - 2299;
    }
    if (pos < 0){
      pos = 2299 + pos;
    }
  
    // Send speed signal to motor
    // Rotating clockwise
    if(speed >= 0){
      if (speed > 100) // motor does not react with too high inputs
        speed = 100;
      analogWrite(PWM2, 0);
      analogWrite(PWM1, speed); //new position from incrementing with postive value -> turn  clockwise
    }
  
    // Rotating counter-clockwise
    else{
      if (-speed > 100) // motor does not react with too low inputs
        speed = -100; 
      analogWrite(PWM1, 0);
      analogWrite(PWM2, -speed); //new position from incrementing with negative value -> turn counter clockwise
    }
    
}

int getSpeedInput(){
  int ready = 0;
  char buf[3];
  int input = -1;
  Serial.println("Enter speed (positive for clockwise, negative for counter clockwise):");
    while(!ready){
    ready = Serial.readBytes(buf,3);
    input = atoi(&buf[0]);
  }
  
  if (input > 254){ //speed cannot be more than 255...
    return 255;
  }
  else if (input < -254){ //...or less than -254
    return -255;
  }  
  else
   return input;
}
