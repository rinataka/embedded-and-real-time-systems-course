// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022)
// Work package 3
// Exercise 4: KEYBOARD SCANNING V 2.0
// Submission code: 761-D!?5
// https://www.tinkercad.com/things/5pjPgDY0JAm-exerc34/editel?sharecode=BBOyKznt8zSTtowFb57Q6EItsdKDFDwrf09hXeamgTw

// Include this library to use it to read a keyboard input.
#include <Keypad.h>

// Bellow (lines 12 to 15) we define the names for the pins 7, 6, 5, 4.
#define COLUMN_1 7 
#define COLUMN_2 6
#define COLUMN_3 5
#define COLUMN_4 4

// Bellow (lines 18 to 21) we define the names for the pins 11, 10, 9, 8.
#define ROW_1 11
#define ROW_2 10
#define ROW_3 9
#define ROW_4 8

// Four rows
const byte ROWS = 4;
// Four columns
const byte COLUMNS = 4;
// Define array keys that we will store the keyboard we use. 
char keys[ROWS][COLUMNS] = 
{
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

// Connect to the row pinouts of the keypad.
byte row_pins[ROWS] = {ROW_1, ROW_2, ROW_3, ROW_4}; 
// Connect to the column pinouts of the keypad
byte column_pins[COLUMNS] = {COLUMN_1, COLUMN_2, COLUMN_3, COLUMN_4}; 

// Instantiates a Keypad object that uses pins 11, 10, 9, 8 as row pins and 7, 6, 5, 4 as column pins.
// The keypad has 4 rows and 4 columns, resulting in 16 keys.
Keypad keypad = Keypad(makeKeymap(keys), row_pins, column_pins, ROWS, COLUMNS);

// Set up serial port.
void setup()
{
  // Open the serial port at 9600 bps (bits per second), 
  // To use Serial.println()
  Serial.begin(9600); 
<<<<<<< HEAD
  
=======
>>>>>>> main
}

// In this loop we use the keypad obkject to read the pressed key. 
void loop(){
  // Call the getKey() function from the keypad object to get the pressed key and assigned it to the variable key.
  char key = keypad.getKey();

  // Prints the pressed key when there is no pressed key..
  if (key != NO_KEY){
    Serial.println(key); // Print the value of key.
  }
}