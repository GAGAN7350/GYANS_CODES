#include <stdio.h>
#include <stdlib.h> // Required for malloc, realloc, and free

int main() {
    // 1. Initialization
    int *arr;          // Pointer to hold the base address of our dynamic array
    int size = 0;      // Current number of elements stored in the array
    int capacity = 2;  // Current allocated capacity of the array
    int input;         // Variable to hold the user's input

    // 2. Initial Memory Allocation
    // Allocate initial memory for 'capacity' integers on the heap.
    arr = (int *)malloc(capacity * sizeof(int));
    
    // Always check if malloc was successful
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit with an error code
    }

    printf("Enter numbers one by one. Enter -1 to stop.\n");

    // 3. The Loop for Dynamic Growth
    while (1) {
        printf("Enter a number: ");
        scanf("%d", &input);

        if (input == -1) {
            break; // Exit the loop if user enters -1
        }

        // Check if the array is full
        if (size == capacity) {
            // Double the capacity
            capacity *= 2;
            printf("--- Array is full. Resizing to capacity: %d ---\n", capacity);

            // Reallocate memory to the new, larger size
            // It's best practice to use a temporary pointer in case realloc fails
            int *temp = realloc(arr, capacity * sizeof(int));
            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                free(arr); // Free the original memory before exiting
                return 1;
            }
            // If realloc was successful, update our main pointer
            arr = temp;
        }

        // Add the user's number to the array and increment the size
        arr[size] = input;
        size++;
    }

    // 4. Printing the final array
    printf("\n--- The numbers you entered are: ---\n");
    for (int i = 0; i < size; i++) {
        // We can access the elements just like a regular array
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 5. Freeing the Memory
    // This is crucial to prevent memory leaks.
    free(arr);
    arr = NULL; // Good practice to set pointer to NULL after freeing

    return 0;
}