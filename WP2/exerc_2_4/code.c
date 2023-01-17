// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, group: 13 (2022)
// Work package 2
// Exercise 4.1: BIT PACKING, code
// Submission code:  aJGQb-5


#include <stdio.h>
#include <stdlib.h>


// Main function of the program with two arguments supported.
void main (int argument_count, char *argument_vector[])
{
    // Checks the number of arguments, if they are different from six the program ends.
    if (argument_count != 6)
    {
        // Prints error when the number of arguments provided are different from 6.
        printf("ERROR: Wrong number of arguments.\n");
        // Prints the usage of the program.
        printf("Usage: code <engine_on> <gear_pos> <key_pos> <brake1> <brake2> \n");
        // Exits the program
        return;
    }

    // Declare the variable input_value type int long.
    int long input_value;
    // Declare the pointer left_character of type char.
    char *left_characters;
    // Initialize the variable input_is_not_a_number of type int.
    int input_is_not_a_number = 0;
    // Loops over the input arguments
    for (int i = 1; i < 6; ++i)
    {
        // Converts input to long int.
        input_value = strtol (argument_vector[i], &left_characters, 10); // Base 10 is decimal

        // Check characters that were left after the conversion to long int,
        // if such characters match the input at least one character was introduced.
        // It also checks if an empty input was given.
        if ((left_characters == argument_vector[i]) || (*left_characters != '\0')) // '\0' is empty
        {
            // Prints the non valid input argument.
            printf ("'%s' is not valid\n", argument_vector[i]);
            // Sets input is not a number to one to indicate we have not received a number.
            input_is_not_a_number = 1;
        }
    }

    // If we have not received a number, prints an error message and exits the program.
    if (input_is_not_a_number == 1)
    {
        // Prints an error where an invalid argument is provided.
        printf("ERROR: Non valid argument(s).\n");
        // Exits the program.
        return;
    }

    // We order the different bits and its values under one single byte.
    // Assign the position of the variables in the arguments, starting in the second position of the array.
    // unsigned char contains tha data within exactly one byte.
    unsigned char engine_on = atoi(argument_vector[1]); // 1 bit (MSB), second position in the array.
    unsigned char gear_position = atoi(argument_vector[2]);  // 3 bits, third position in the array.
    unsigned char key_position = atoi(argument_vector[3]);   // 2 bits, fourth position in the array.
    unsigned char brake_1 = atoi(argument_vector[4]);    // 1 bit, fifth position in the array.
    unsigned char brake_2 = atoi(argument_vector[5]);    // 1 bit (LSB), sixth position in the array.
    unsigned char packed_eight_bits = 0; // Initialized variable, here will contain the values of the final eighth bits.

    // Checks if the input value for engine_on is within 0 and 1.
    if (engine_on > 1)
    {
        // Prints when engine on is out of the range.
        printf("ERROR: engine_on is outside the range\n");
        // Exits the program.
        return;
    }
    // Checks if the input value for gear_position is within 0 and 4
    if (gear_position > 4)
    {
        // Prints when gear position is out of the range.
        printf("ERROR: gear_position is outside the range\n");
        // Exits the program.
        return;
    }
    // Checks if the input value for key_position is within 0 and 2.
    if (key_position > 2)
    {
        // Prints when key position is out of the range.
        printf("ERROR: key_position is outside the range\n");
        // Exits the program.
        return;
    }
    // Checks if the input value for brake_1 is within 0 and 1.
    if (brake_1 > 1)
    {
        // Prints when brake 1 is out of the range.
        printf("ERROR: brake_1 is outside the range\n");
        // Exits program.
        return;
    }
    // Checks if the input value for brake_2 is within 0 and 1.
    if (brake_2 > 1)
    {
        // Prints when brake 2 is out of the range.
        printf("ERROR: brake_2 is outside the range\n");
        // Exits the program.
        return;
    }

    // "<<" is the bitwise left-shift that moves the bits seven positions to the left,
    // and engine_on should be the MSB in the packed_eight_bits, i.e., the byte.
    // "engine_on <<= 7" is another way to write "engine_on = engine_on << 7".
    engine_on <<= 7;
    packed_eight_bits += engine_on; // Another way to write "packed_eight_bits = packed_eight_bits + engine_on"

    // "<<" means shift the bits four positions to the left.
    gear_position <<= 4;
    // Add the shifted gear position to the packed bits.
    packed_eight_bits += gear_position;

    // "<<" means shift the bits two positions to the left.
    key_position <<= 2;
    // Add the shifted key position to the packed bits.
    packed_eight_bits += key_position;

    // "<<" means shift the bits one positions to the left within the byte.
    brake_1 <<= 1;
    // Add the shifted brake 1 position to the packed bits.
    packed_eight_bits += brake_1;

    // This does not need to be shifted since it is already in its correct position within the byte, as it is the LSB.
    // Adds brake 2 to the packed bits.
    // Now after the sum packed bits contains all the values in their correct place within the byte.
    packed_eight_bits += brake_2;

    // This is the result, converted to hexadecimal.
    printf("The packet bits are (hexadecimal): %X\n", packed_eight_bits);

    // Program exits.
    return;
}

