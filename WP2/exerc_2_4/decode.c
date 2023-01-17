// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, group: 13 (2022)
// Work package 2
// Exercise 4.2: BIT PACKING, decode
// Submission code:  aJGQb-5

#include <stdio.h>
#include <stdlib.h>

// Main function with two program arguments supported.
// This program takes the input string and converts it to hexadecimal number, then converted to a decimal number.
// then the decimal number is assigned to an unsigned chart (so we are sure the number is in one byte).
// Having the 8 bits, we need to extract every single bit or bits corresponding to each variable.
// The mask help us to select the bits we are interested in and isolate the value for that variable.
// The bitwise AND (&) helps us to extract the value of those bits or bit, from the original byte provided.
// The shift to the right helps us to shift the places to the LSB side, so the variable now is totally isolated.
// Then we print the table with the values of each variable.
void main (int argument_count, char *argument_vector[])
{
    // Checks if the number of arguments are different
    if (argument_count != 2)
    {
        // Prints an error message when the number of arguments are wrong.
        printf("ERROR: Wrong number of arguments.\n");
        // Prints the usage of the program.
        printf("Usage: decode <Hexadecimal number> \n");
        return;
    }

    // strtol() allows to interpret the input string as a hexadecimal number,
    // which is converted into a decimal long integer.
    long int packed_bits_long_int = strtol(argument_vector[1], NULL, 16); // decimal

    if ((packed_bits_long_int < 0) || (packed_bits_long_int > 255)) // 1 byte can represent decimal numbers between 0 and 255.
    {
        // Prints an error message when the parameters are outside the range allowed for one byte.
        printf("ERROR: the input parameter is outside the range allowed for 1 byte.\n");
        return;
    }

    // Stores the value into one byte by definition of unsigned char
    unsigned char packed_eight_bits = (unsigned char)(packed_bits_long_int);

    // The mask "selects" the bits we are interested in and sets the rest to zero.
    // 0b (MSB) 0 0 0 0 0 0 0 0 (LSB). We start counting from LSB to MSB, where the first position is LSB and the last position is MSB
    // Example: we have an input number 0xAB, i.e., 0b 1 0 1 0 1 0 1 1,
    // We want to apply the mask 0b 1 1 1 0 0 0 0 0 (we choose to select only the last three bits, depends on the context. One means it is selected).
    // the result will be 0b 1 0 1 0 0 0 0 0, where the three last numbers closer to MSB (in this case "1 0 1") are the ones from the original number.
    // bit-wise AND (only one &) to apply the mask.

    // Mask to extract the bit corresponding to engine_on. MSB
    // Example for engine_on with packed_eight_bits = 0xAB, i.e., 0b 1 0 1 0 1 0 1 1,
    // for the engine_on_mask we selected only the last bit (according to the specifications of the bit positions in the assignment): 0b 1 0 0 0 0 0 0 0.
    // packed_eight_bits & engine_on_mask: "0b 1 0 1 0 1 0 1 1"  &  "0b 1 0 0 0 0 0 0 0"
    // packed_eight_bits & engine_on_mask = 0b 1 0 0 0 0 0 0 0
    // We selected only the last bit from packed_eight_bits and each of the rest of the bits are zero.
    unsigned char engine_on_mask = 0b10000000; // Also 0x80.
    unsigned char engine_on = packed_eight_bits & engine_on_mask; // Applying bit-wise AND
    engine_on >>= 7; // Shift the bits to the right seven positions.

    // Mask to extract the three bits corresponding to gear_position.
    // Example for gear_position with packed_eight_bits = 0xAB, i.e., 0b 1 0 1 0 1 0 1 1,
    // for the engine_on_mask we selected the three bits before last bit (according to the specifications of the bit positions in the assignment): 0b 0 1 1 1 0 0 0 0.
    // packed_eight_bits & engine_on_mask: "0b 1 0 1 0 1 0 1 1"  &  "0b 0 1 1 1 0 0 0 0"
    // packed_eight_bits & engine_on_mask = 0b 0 0 1 0 0 0 0 0.
    // We selected only the last three bits from the last bit, from packed_eight_bits and each of the rest of the bits are zero.
    unsigned char gear_position_mask = 0b01110000; // Also 0x70
    unsigned char gear_position = packed_eight_bits & gear_position_mask; // Applying bit-wise AND
    gear_position >>= 4; // Shift the bits to the right four positions

    // Mask to extract the two bits corresponding to key_position.
    unsigned char key_position_mask = 0b00001100; // Also 0x0C
    unsigned char key_position = packed_eight_bits & key_position_mask; // Applying bit-wise AND
    key_position >>= 2; // Shift the bits to the right two positions

    // Mask to extract the bit corresponding to brake_1.
    unsigned char brake_1_mask = 0b00000010; // Also 0x02
    unsigned char brake_1 = packed_eight_bits & brake_1_mask; // Applying bit-wise AND
    brake_1 >>= 1; // Shift the bits to the right one positions

    // Mask to extract the bit corresponding to brake_2.
    // Does not need a shift because it is already in its position, LSB.
    unsigned char brake_2_mask = 0b00000001; // Also 0x01
    unsigned char brake_2 = packed_eight_bits & brake_2_mask;//bit-wise AND

    // Checks if the input value for engine_on is within 0 and 1.
    if (engine_on > 1)
    {
        // Prints an error message when engine on is outside the range.
        printf("ERROR: engine_on is outside the range\n");
        // Exits the program.
        return;
    }
    // Checks if the input value for gear_position is within 0 and 4
    if (gear_position > 4)
    {
        // Prints an error message when gear position is outside the range.
        printf("ERROR: gear_position is outside the range\n");
        // Exits the program.
        return;
    }
    // Checks if the input value for key_position is within 0 and 2.
    if (key_position > 2)
    {
        // Prints an error message when key position is outside the range.
        printf("ERROR: key_position is outside the range\n");
        // Exits the program.
        return;
    }
    // Checks if the input value for brake_1 is within 0 and 1.
    if (brake_1 > 1)
    {
        // Prints an error message when brake 1 is outside the range.
        printf("ERROR: brake_1 is outside the range\n");
        // Exits the program.
        return;
    }
    // Checks if the input value for brake_2 is within 0 and 1.
    if (brake_2 > 1)
    {
        // Prints an error message when brake 2 is outside the range.
        printf("ERROR: brake_2 is outside the range\n");
        // Exits the program.
        return;
    }

    // Print the table with the names and their correspondent values.
    printf("\nName               Value\n");
    // Prints a sequence of dashes.
    printf("-----------------------------------\n");
    // Prints the value of engine on.
    printf("engine_on           %d\n", engine_on);
    // Prints the value of gear position.
    printf("gear_position       %d\n", gear_position);
    // Prints the value of key position.
    printf("key_position        %d\n", key_position);
    // Prints the value of brake 1.
    printf("brake_1             %d\n", brake_1);
    // Prints the value of brake 2.
    printf("brake_2             %d\n", brake_2);

    // Exits the program.
    return;
}
