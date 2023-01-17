// (C) Lina Boman, Graciela Coate Cano, Jina Dawood, group: 13 (2022)
// Work package 2
// Exercise 3: BINARY FILES
// Submission code:  aJGQb-5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// -----typedefs -------
typedef struct
{
    char firstname[20];
    char lastname[20];
    char pers_number[13]; // yyyymmddnnnc
} PERSON;

// Function declaration
PERSON input_record(void);             // Reads a person’s record.
void write_new_file(PERSON *inrecord); // Creates a file and writes the first record
void printfile(void);                  // Prints out all persons in the file
void search_by_firstname(char *name);  // Prints out the person if in list
void append_file(PERSON *inrecord);    // appends a new person to the file

int main(void)
{
    PERSON ppost; // declaring a person
    PERSON *ptr_person = &ppost; // initilazing person pointer 
    char fname[20]; // declaring first name variable

    while (1)  // Infinite loop with 1 representing true
    {
        int number = 0; // Reset option when typing a character instead of an integer

        printf("\nPlease make a choice 1-5\n"
               "1. Create a new and delete the old file.\n"
               "2. Add a new person to the file.\n"
               "3. Search for a person in the file.\n"
               "4. Print out all in the file. \n"
               "5. Exit the program.\n");

        scanf("%d", &number);
        fflush(stdin); // empty buffer 

        switch (number)
        {
        case 1:
            ppost = input_record(); // function to get a persons record 
            write_new_file(ptr_person);  // function to delete the old file and create a new one
            break;
        case 2:
            ppost = input_record(); // function to get a persons record 
            append_file(ptr_person); //function to add a new person to the file
            break;
        case 3:
            puts("\nEnter first name of the person you wish to search for: \n");
            fgets(fname, 20, stdin); // read input 
            search_by_firstname(fname);//function to print out records belonging to the requested name
            break;
        case 4:
            printfile();  // function to print out all records in a file
            break;
        case 5:
            exit(0);  // exit the program
            break;
        default:
            printf("Error! option not available");
        }
    }
    return (0);
}

PERSON input_record(void)
{
    PERSON ppost; // declaring a person
    fflush(stdin); // empty buffer
    char input[20]; // declare input ch array. 

    puts("Enter the first name: ");
    fgets(ppost.firstname, 20, stdin); // read input 
    strcpy(input, ppost.firstname); //copy and return copied string 
    int flength = strlen(input); // calculate lenght of the string 
    for (int i = 0; i < strlen(input); i++) 
    {
        if (isdigit(input[i]) != 0 || flength > 19 || input[0] == '\n')
        {
            // user will go back to main menu if they enter integer, 
            //characters than 19 or leave the field empty, 
            printf("invalid input");
            main(); // back to main menu 
        }
    }

    puts("Enter the last name: ");
    fgets(ppost.lastname, 20, stdin); // read input 
    strcpy(input, ppost.lastname); // cppy string 
    int llength = strlen(input); // calculate length 
    for (int i = 0; i < strlen(input); i++) {
        if (isdigit(input[i]) != 0 || llength > 19 || input[0] == '\n') {
             // user will go back to main menu if they enter integer, 
            //more characters than 19 or leave the field empty, 
            printf("invalid input");
            main(); // return to main if input is invalid
        }
    }

    puts("Enter the personal number(yyyymmddnnnn): ");
    fgets(ppost.pers_number, 13, stdin); //read input 
    strcpy(input, ppost.pers_number); // copy string 
    int plength = strlen(input); // get length of input string 
    for (int i = 0; i < strlen(input); i++) {
        if (isalpha(input[i]) != 0 || plength > 12 || input[0] == '\n'){
            // user will go back to main menu if they enter a character, 
            //number higher than 12 or leave the field empty, 
            printf("invalid input");
            main(); // return to main if input is invalid
        }
    }
    return ppost; // return created person
}

void write_new_file(PERSON *inrecord) // Creates a file and delete old one
{
    char newname[] = "personfile.bin"; // initiliasing new name for binary file
    char oldname[] = "personfile.bin"; // initiliasing old name for binary file

    FILE *f; // declaring a filepointer
    remove(oldname); //removes the the old file

    if ((f = fopen(newname, "wb")) == NULL) // wb = create and write in binary
    {
        // Program exits if the file pointer returns NULL.
        printf("\n Can not create the file");
        exit(1);
    }
    //If the file does not exist, it will be created.
    // creates and writes to a file with the new name and adds person
    fwrite(inrecord, sizeof(PERSON), 1, f);
    fclose(f); // closes the file
}

void append_file(PERSON *inrecord) // appends a new person to the file
{
    FILE *f;                         // declaring filepointer
    char fname[] = "personfile.bin"; // initiliazing filename

    if ((f = fopen(fname, "a+b")) == NULL) //Open for append in binary mode. 
    {
        // Program exits if the file pointer returns NULL.
        printf("\n Can not create file");
        exit(1);
    }
    fwrite(inrecord, sizeof(PERSON), 1, f);    //data is added to the end of the file.
    fclose(f); //Closing a file
}

void search_by_firstname(char *name) // Prints out the person with specific name if in list
{
    FILE *f;                                // declaring filepointer
    int found = 0;                          // variable to count records, initialiezed to zero
    PERSON *ppost = malloc(sizeof(PERSON)); // allocate memory
    char fname[] = "personfile.bin";

    if ((f = fopen(fname, "rb")) == NULL)   //Open for reading in binary mode.
    {
        // Program exits if the file pointer returns NULL.
        printf("\n Can not open file");
        exit(1);
    }
    // reads file until it returns 0, and prints every record.
    while ((fread(ppost, sizeof(PERSON), 1, f) == 1))
    { // if namepointer and name from user input are same it will count it and print
        if (strcmp(ppost->firstname, name) == 0)
        {
            printf("\nFound record of Person with name: %s\n", name);
            printf("\nFirst name: %s", ppost->firstname);
            printf("\nLast name: %s", ppost->lastname);
            printf("\nPersonalnumber: %s", ppost->pers_number);
            printf("\n=======================\n");
            found++;
        }
    }
    if (found == 0) // if the counter is 0, then no records are found
    {
        printf("\n Record Not found in this file!");
    }
    free(ppost); // Free the memory
    fclose(f);   //Closing a file
}

void printfile(){ // Prints out all persons in the file

    int count = 0;                          // variable to count records, initialiezed to zero
    FILE *f;                                // declaring a filepointer
    PERSON *ppost = malloc(sizeof(PERSON)); // allocate memory
    char fname[] = "personfile.bin";

    if ((f = fopen(fname, "rb")) == NULL)  //Open for reading in binary mode. 
    {
        // Program exits if the file pointer returns NULL.
        printf("\n Can not open file");
        exit(1);
    }
    // reads file until it returns 0, and prints every record.
    while ((fread(ppost, sizeof(PERSON), 1, f) == 1))
    {
        count++;
        printf("\nFirst name: %s", ppost->firstname);
        printf("\nLast name: %s", ppost->lastname);
        printf("\nPersonalnumber: %s", ppost->pers_number);
        printf("\n=======================\n");
    }
    if (count == 0) // if the counter is 0, then no records are found
    {
        printf("\n Records Not found in this file!");
    }
    free(ppost); // free memory
    fclose(f);   //Closing a file
}
