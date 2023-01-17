// (C) Lina Boman, Graciela Coate Cano, Jina Dawood. Group: 13 (2022)
// Work Package 2
// Exercise 2: LINKED LIST
// Submission code:  aJGQb-5


#include <stdio.h>
#include <stdlib.h>
#include <time.h> // To use srand() and rand()
// Constants
#define MAX 5

// typedef (type definition) creates additional name (alias) for another data type.
typedef struct q
{
    int number;
    struct q *next;
    struct q *previous;
} REGTYPE;

// *** Function Declarations ***
REGTYPE* createNewRecord(void);
REGTYPE* randomList(void);
REGTYPE* addFirst(REGTYPE* old_head, int data);
void printList( REGTYPE* record);
// === End of Function Declarations ===

// ****** Main program ******
int main(int argument_count, char *argument_vector[])
{
    REGTYPE *actual_position;
    REGTYPE *head = NULL;

    srand(time(0));  // Randomize the seed

    head = randomList();
    printList(head);

    head = addFirst(head, 10 ); // For data, we choose the value ten.

    printf("\nList after adding a new element to the head\n");
    printList(head);

    // Free the allocated memory to avoid memory leaks
    while((actual_position = head) != NULL)
    {
        head = actual_position->next;
        printf("\nTrying to free memory\n");
        free(actual_position);
        printf("Memory freed\n");
    }

    return 0;
}
// ====== End of Main Program ======

// ****** Function Definitions ******

// *** Function createNewRecord() ***
REGTYPE* createNewRecord(void) // Auxiliary function to create a new record
{
    // malloc() memory allocation on the heap and
    // returns a pointer to that memory
    REGTYPE *new_record = malloc(sizeof (REGTYPE));
    new_record->number = 0; // -> to access to the field of the structure the new_record is pointing to.
    new_record->next = NULL;
    new_record->previous = NULL;

    return new_record; // Returns a pointer of type REGTYPE
}
// === End of createNewRecord function ===

// *** Function randomList() ***
// Random list of MAX number of elements, filled with numbers from zero to one-hundred.
REGTYPE* randomList(void)
{
    REGTYPE *old_record = createNewRecord(); // Pointer to the tail.
    REGTYPE *new_record = old_record; // Pointer to the tail
    new_record->number = rand() % 101; // 101 because we want to include all random values from zero to one-hundred.

    for (int i = 1; i < MAX; ++i) // Starts with i = 1 because we created above the first element of the list.
    {
        new_record = createNewRecord();
        new_record->number = rand() % 101; // Creates a random number between zero and one-hundred.
        new_record->next = old_record;

        old_record->previous = new_record;
        old_record = new_record; // This is for the next iteration, so the old_record will be the current new_record.
    }

    return new_record; // Returns a pointer to the head
}
// === End of randomList() function ===

// *** Function addFirst() ***
REGTYPE* addFirst(REGTYPE* old_head, int data)
{
    REGTYPE  *new_head = createNewRecord();
    new_head->number = data;
    new_head->next = old_head; // The new head has a "next", pointing to the old_head
    old_head->previous = new_head; // old_head now has a "previous" pointing to the new_head

    return new_head;
}
// === End of addFirst() function ===

// Print the list
void printList(REGTYPE *record) //
{
    int number = 0;
    // Prints from head to tail
    while( record != NULL)
    {
        printf("\n Position number %d : %d\n" , number++, record->number); // -> Access to that element of the pointer
        record = record->next;
    }
}

// ====== End of Function Definitions ======
