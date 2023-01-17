// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, 
// Group: 13 (2022)
// Work package 3
<<<<<<< HEAD
// Exercise 3: KEYBOARD SCANNING
=======
// Exercise 3.1: KEYBOARD SCANNING
>>>>>>> main
// Submission code: 761-D!?5
// https://www.tinkercad.com/things/lMjYPtmwYBl-exerc3keyboardscanning/editel?sharecode=ezWrE18_jc_CkJhw_0fqFHIfroiZdJfamFKPYqth2Ng

// Bellow (lines 9 to 12) we define the names for the pins 7, 6, 5, 4.
#define COLUMN_1 7 
#define COLUMN_2 6
#define COLUMN_3 5
#define COLUMN_4 4

// Bellow (lines 15 to 18) we define the names for the pins 11, 10, 9, 8.
#define ROW_1 11
#define ROW_2 10
#define ROW_3 9
#define ROW_4 8

// Set up each pin and opens serial port.
void setup()
{
  // Opens the serial port at 9600 bps (bits per second), 
  // to use Serial.println()
  Serial.begin(9600); 
  
  // COLUMNS are input
  pinMode(COLUMN_1, INPUT); // COLUMN_1 will be input.
  pinMode(COLUMN_2, INPUT); // COLUMN_2 will be input.
  pinMode(COLUMN_3, INPUT); // COLUMN_3 will be input.
  pinMode(COLUMN_4, INPUT); // COLUMN_4 will be input.
  
  // ROWS are output
  pinMode(ROW_1, OUTPUT); // ROW_1 will be output.
  pinMode(ROW_2, OUTPUT); // ROW_2 will be output
  pinMode(ROW_3, OUTPUT); // ROW_3 will be output
  pinMode(ROW_4, OUTPUT); // ROW_4 will be output
}

// Function printPressedKey() has two program arguments and does not return anything.
// This function receives two parameters off_row and pressed_key, 
// which say the number of the row that has a LOW value and the input value converted to decimal, respectively.
void printPressedKey(int off_row, int pressed_key)
{
  // *** ROW_1 off ***
  // If pressed key equals to 6, and the first row is off, then key 1 was pressed.
  if ((pressed_key == 6) && (off_row == 1))
  {
    Serial.println("1"); // Prints 1.
  }
  // If pressed key equals to 10, and the first row is off, then key 2 was pressed.
  if ((pressed_key == 10) && (off_row == 1))
  {
    Serial.println("2"); // Prints 2.
  }
  // If pressed key equals to 12, and the first row is off, then key 3 was pressed.
  if ((pressed_key == 12) && (off_row == 1))
  {
    Serial.println("3"); // Prints 3.
  }
  // If pressed key equals to 14, and the first row is off, then key A was pressed.
  if ((pressed_key == 14) && (off_row == 1))
  {
    Serial.println("A"); // Prints A.
  }
  // --- end ROW_1 off ---
  
  
  // *** ROW_2 off ***
  // If pressed key equals to 6, and the second row is off, then key 4 was pressed.
  if ((pressed_key == 6) && (off_row == 2))
  {
    Serial.println("4"); // Prints 4.
  }
   // If pressed key equals to 10, and the second row is off, then key 5 was pressed.
  if ((pressed_key == 10) && (off_row == 2))
  {
    Serial.println("5"); // Prints 5.
  }
   // If pressed key equals to 12, and the second row is off, then key 6 was pressed.
  if ((pressed_key == 12) && (off_row == 2))
  {
    Serial.println("6"); // Prints 6.
  }
   // If pressed key equals to 14, and the second row is off, then key B was pressed.
  if ((pressed_key == 14) && (off_row == 2))
  {
    Serial.println("B"); // Prints B
  }
  // --- end ROW_2 off
  
  
  // *** ROW_3 off ***
  // If pressed key equals to 6, and the third row is off, then key 7 was pressed.
   if ((pressed_key == 6) && (off_row == 3))
  {
    Serial.println("7"); // Prints 7.
  }
   // If pressed key equals to 10, and the third row is off, then key 8 was pressed.
  if ((pressed_key == 10) && (off_row == 3))
  {
    Serial.println("8"); // Prints 8.
  }
   // If pressed key equals to 12, and the third row is off, then key 9 was pressed.
  if ((pressed_key == 12) && (off_row == 3))
  {
    Serial.println("9"); // Prints 9.
  }
   // If pressed key equals to 14, and the third row is off, then key C was pressed.
  if ((pressed_key == 14) && (off_row == 3))
  {
    Serial.println("C"); // Prints C.
  }
  // --- end ROW_3 off
  
  
  // *** ROW_4 off ***
  // If pressed key equals to 6, and the fourth row is off, then key * was pressed.
  if ((pressed_key == 6)  && (off_row == 4))
  {
    Serial.println("*"); // Prints *.
  }
  // If pressed key equals to 10, and the fourth row is off, then key 0 was pressed.
  if ((pressed_key == 10) && (off_row == 4))
  {
    Serial.println("0"); // Prints 0.
  }
  // If pressed key equals to 12, and the fourth row is off, then key # was pressed.
  if ((pressed_key == 12) && (off_row == 4))
  {
    Serial.println("#"); // Printa #.
  }
  // If pressed key equals to 14, and the fourth row is off, then key D was pressed.
  if ((pressed_key == 14) && (off_row == 4))
  {
    Serial.println("D"); // Prints D.
  }
  // --- end ROW_4 off 
}

// In the following loop, reads the pressed key and print the value of that key.
// The main idea of this implementation is that, given a known output to the rows of the keyboard (with the output pins),
// the input received from the comlumns (the input pins) should correspond to a binary value unique for the key that was pressed.
// For instance, when the rows have the following output value 0 1 1 1 and assuming the pressed key is "1",
// the expected output from the columns should be 0 1 1 0. Similarly if the output value is 1 0 1 1 and assuming the key is "B",
// the expected output should be 1 1 1 0, and so on.
void loop()
{
  int miliseconds = 100; // Set the milliseconds to 100. 
  int pressed_key = 0; // Initialize press_key to zero. 
  
  // *** Set ROW_1 to off (LOW value), while keeping the rest to HIGH value ***
  digitalWrite(ROW_1, LOW); // Set ROW_1 (the MSB) to LOW value.
  digitalWrite(ROW_2, HIGH); // Set ROW_2 to HIGH value.
  digitalWrite(ROW_3, HIGH); // Set ROW_3 to HIGH value.
  digitalWrite(ROW_4, HIGH); // Set ROW_4 (the LSB) to HIGH value.

  int column_1 = digitalRead(COLUMN_1); // Reads column 1.
  int column_2 = digitalRead(COLUMN_2); // Reads column 2.
  int column_3 = digitalRead(COLUMN_3); // Reads column 3.
  int column_4 = digitalRead(COLUMN_4); // Reads column 4.
  // Converts the binary value received from the columns to decimal and assigned to pressed_key. 
  // The weigths for each column are: (MSB) 2^3 = 8, 2^2 = 4, 2^1 = 2, (LSB) 2^0 = 1
  pressed_key = column_1 * 8 + column_2 * 4 + column_3 * 2 + column_4 * 1;
  // Set off_row to 1 to indicate that the row 1 is the only one with LOW value (it is off)
  int off_row_1 = 1; 
  // Prints the pressed key.
  printPressedKey(off_row_1, pressed_key);
  // --- end ROW_1 off ---
  
  
  // *** Set ROW_2 to off (LOW value), while keeping the rest to HIGH value ***
  digitalWrite(ROW_1, HIGH); // Set ROW_1 (the MSB) to HIGH value.
  digitalWrite(ROW_2, LOW); // Set ROW_2 to LOW value.
  digitalWrite(ROW_3, HIGH); // Set ROW_3 to HIGH value.
  digitalWrite(ROW_4, HIGH); // Set ROW_4 (LSB) to HIGH value.
  
  column_1 = digitalRead(COLUMN_1); // Reads column 1.
  column_2 = digitalRead(COLUMN_2); // Reads column 2.
  column_3 = digitalRead(COLUMN_3); // Reads column 3.
  column_4 = digitalRead(COLUMN_4); // Reads column 4.
  // Converts the binary value received from the columns to decimal and assigned to pressed_key. 
  // The weigths for each column are: (MSB) 2^3 = 8, 2^2 = 4, 2^1 = 2, (LSB) 2^0 = 1
  pressed_key = column_1 * 8 + column_2 * 4 + column_3 * 2 + column_4 * 1;
  // Set off_row to 2 to indicate that the row 2 is the only one with LOW value (it is off)
  int off_row_2 = 2;
  // Prints the pressed key.
  printPressedKey(off_row_2, pressed_key);
  // --- end ROW_2 off ---
  
  
  // *** Set ROW_3 to off (LOW value), while keeping the rest to HIGH value ***
  digitalWrite(ROW_1, HIGH); // Set ROW_1 (MSB) to HIGH value.
  digitalWrite(ROW_2, HIGH); // Set ROW_2 to HIGH value.
  digitalWrite(ROW_3, LOW); // Set ROW_3 to LOW value.
  digitalWrite(ROW_4, HIGH); // Set ROW_4 (LSB) to HIGH value.
  
  column_1 = digitalRead(COLUMN_1); // Reads column 1.
  column_2 = digitalRead(COLUMN_2); // Reads column 2.
  column_3 = digitalRead(COLUMN_3); // Reads column 3.
  column_4 = digitalRead(COLUMN_4); // Reads column 4.
  // Converts the binary value received from the columns to decimal and assigned to pressed_key. 
  // The weigths for each column are: (MSB) 2^3 = 8, 2^2 = 4, 2^1 = 2, (LSB) 2^0 = 1
  pressed_key = column_1 * 8 + column_2 * 4 + column_3 * 2 + column_4 * 1;
  // Set off_row to 3 to indicate that the row 3 is the only one with LOW value (it is off)
  int off_row_3 = 3;
  // Prints the pressed key.
  printPressedKey(off_row_3, pressed_key);
  // --- end ROW_3 off ---
  
  
  // *** Set ROW_4 to off (LOW value), while keeping the rest to HIGH value ***
  digitalWrite(ROW_1, HIGH); // Set ROW_1 (MSB) to HIGH value.
  digitalWrite(ROW_2, HIGH); // Set ROW_2 to HIGH value.
  digitalWrite(ROW_3, HIGH); // Set ROW_3 to HIGH value.
  digitalWrite(ROW_4, LOW); // Set ROW_3 (LSB) to LOW value.
  
  column_1 = digitalRead(COLUMN_1); // Reads column 1.
  column_2 = digitalRead(COLUMN_2); // Reads column 2.
  column_3 = digitalRead(COLUMN_3); // Reads column 3.
  column_4 = digitalRead(COLUMN_4); // Reads column 4.
  // Converts the binary value received from the columns to decimal and assigned to pressed_key. 
  // The weigths for each column are: (MSB) 2^3 = 8, 2^2 = 4, 2^1 = 2, (LSB) 2^0 = 1
  pressed_key = column_1 * 8 + column_2 * 4 + column_3 * 2 + column_4 * 1;
  // Set off_row to 4 to indicate that the row 4 is the only one with LOW value (it is off)
  int off_row_4 = 4;
  // Prints the pressed key.
  printPressedKey(off_row_4, pressed_key);
  // --- end ROW_4 off ---
  
  // Wait for 100 millisecond(s)
  delay(miliseconds); 
}