// Lina Boman, Graciela Coate Cano, Jina Dawood, group: 13 (2022)
// Work package 2
// Exercise 1: ROBOT
// Submission code: aJGQb-5

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100
enum DIRECTION {N, E, S, W};

typedef struct {
    int x_position;
    int y_position;
    enum DIRECTION direction;
} ROBOT;

int checkIfItIsNumber(const char *str)
{
    int long input_value = -1; // -1 if the input is not a number.
    char *left_characters;
    // Convert input to long int.
    input_value = strtol (str, &left_characters, 10); // Base 10 is decimal

    // Check characters that were left after the conversion to long int,
    // if such characters match the input at least one character was introduced.
    // It also checks if an empty input was given.
    if ((left_characters == str) || (*left_characters != '\0')) // '\0' is empty
    {
        printf ("'%s' is not valid\n", str);
        input_value = -1; // input is not alpha numeric
    }
    return input_value;
}

void askCoordinates(int *x, int *y)
{
    do
    {
        char input[30]; //declare string input
        printf("\nEnter longitude position between 0 and 99\n"); //ask user for input
        fflush(stdin); //flush keyboard
        scanf("%s", input); //store users input in string 
        *x = checkIfItIsNumber(input); //check if input value is a number and assign input value to pointer depending in return value
        if (*x > 99 ||  *x < 0) //check if user input is in range
        {
            printf("\nError: That's either a number out of range or a letter.\n"); //let user know if input is out of range 
        }
        fflush(stdin); //flush keyboard
        printf("x value: %d", *x); //show the user the input value
    } while (*x > 99 || *x < 0); //will repeat if input is out of range or a letter
    do
    {
        char input[30]; //declare string input
        printf("\nEnter latitude position between 0 and 99\n"); //ask user for input
        fflush(stdin); //flush keyboard
        scanf("%s", input); //store users input in string 
        *y = checkIfItIsNumber(input); //check if input value is a number and assign input value to pointer depending in return value
        if (*y > 99 || *y < 0)
        {
            printf("\nError: That's either a number out of range or a letter."); //let user know if input is out of range 
        }
        fflush(stdin); //flush keyboard
        printf("y value: %d", *y); //show the user the input value
    } while (*y > 99 || *y < 0); //will repeat if input is out of range or a letter
}


void turn(enum DIRECTION* d)
        {
    //turn:  means that the robot turns 90 degrees clockwise.

    if (*d == N) // *d access to the content of the memory location pointed by "d".
    {//get current direction
        *d = E;//set new direction
    }
    else if (*d == E)
    {
        *d = S;
    }
    else if(*d == S)
    {
        *d = W;
    } else if (*d == W)
    {
        *d = N;
    }
}

void move (enum DIRECTION* d, int* x, int* y)
        {

    // Move:  means that the robot takes one step in the current direction.

    if (*d == N)
    {    // get current direction
        *y = *y + 1;    // get x or y and -- or ++ depending on direction
    }
    else if (*d == E)
    {
        *x = *x + 1;
    }
    else if(*d == S)
    {
        *y = *y - 1;
    }
    else if (*d == W)
    {
        *x = *x - 1;
    }
}

char enumToChar(int d) // Also, enumChar(enum DIRECTION d)
{
    // Converts int value at robots direction attribute to char
    if (d == 0){ // Also (d == N)
        return 'N';
    }
    else if (d == 1) // ALso (d == E)
    {
        return 'E';
    }
    else if (d == 2) // Also (d == S)
    {
        return 'S';
    } else
    {
        return 'W';
    }
}

// Main function
int main(int argc, char* argv[])
{
    
    ROBOT robot; // Declare variable robot of type ROBOT.

    int boo = 1; // Will be 1 until user exits program.

    int* x = &robot.x_position; // Declare pointer to the robot's x_position field. & gives the address of the variable.
    int* y = &robot.y_position; // Declare pointer to the robot's y_position field.
    enum DIRECTION* d = &robot.direction; // Declare pointer to the robot's direction field.
    *d = N; // The start direction is always north for the robot. * means dereferencing (Access to the content of that memory location).

    char instructions[MAX]; // Declare an array of chars (String).
    do {
        askCoordinates(x, y); // Ask the user for coordinates
        printf("\nEnter 'm' or 't'. 'm' to move the robot one step in the current direction, 't' to to turn 90 degrees "
               "clockwise\nTo exit enter 'q', other characters will be ignored\n");

        // When "instructions" is passed to scanf(), it is converted to the address of the first element of the array, i.e.,  &instructions[0]
        scanf("%s", instructions);
        printf("Instructions: %s", instructions);


        for (int i = 0; i < 20; i++)
        {
            // Loop through array to follow given instructions. Why 20?
            if (instructions[i] == 't') {
                turn(d);
            } else if (instructions[i] == 'm') {
                move(d, x, y);
            } else if(instructions[i] == 'q'){
                boo = 0;
            }
        }
        printf("\nCurrent position: %i, %i, Direction: %c", robot.x_position, robot.y_position, enumToChar(robot.direction)); // Final position

        for (int i=0; i<MAX; i++){ // Clean the array for the next iteration.
            instructions[i] = '\0';
        }

    }while(boo == 1); // Changes to 0 when user quits
}
