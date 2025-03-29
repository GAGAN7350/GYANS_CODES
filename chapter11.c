#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int *arr;
    int n, i;

    // Allocating memory using malloc
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    arr = (int*) malloc(n * sizeof(int));
    
    if (arr == NULL) 
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Memory allocated using malloc. Enter elements:\n");
    for (i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }

    // Allocating memory using calloc
    int *arr2 = (int*) calloc(n, sizeof(int));
    if (arr2 == NULL) 
    {
        printf("Memory allocation failed\n");
        free(arr);
        return 1;
    }
    printf("Memory allocated using calloc (initialized to 0):\n");
    for (i = 0; i < n; i++) 
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    // Reallocating memory using realloc
    printf("Enter new size for the array: ");
    int newSize;
    scanf("%d", &newSize);
    arr = (int*) realloc(arr, newSize * sizeof(int));
    if (arr == NULL) 
    {
        printf("Memory reallocation failed\n");
        free(arr2);
        return 1;
    }
    
    printf("Memory reallocated using realloc.\n");
    for (i = n; i < newSize; i++) 
    {
        scanf("%d", &arr[i]);
    }

    printf("Final array: ");
    for (i = 0; i < newSize; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Freeing allocated memory
    free(arr);
    free(arr2);
    printf("Memory freed successfully\n");

    return 0;
}
