#include<stdio.h>

int main()
{
    int a;
    int* b=&a;
    int** c=&b;
    printf("Enter the value of a\n");
    scanf("%d", &a);
   
    printf("The address of a is %p\n", &a);
    printf("The address of a is %p\n", b);
    printf("the value of b is %d\n", *b);
    printf("The address of c is %p\n", &b);
    printf("The value of c is %d\n", **c);
    return 0;
}