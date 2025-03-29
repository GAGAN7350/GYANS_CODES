#include<stdio.h>
// This program demonstrates the use of printf with different data types.
int main()
{
    int a;
    printf("Enter a integer");
    scanf("%d", &a);

    float b;
    printf("Enter a decimal number");
    scanf("%f", &b);

    char c[1000];
    printf("Enter a word");
    scanf("%s", c);

    printf("Value of a is %d\n", a);
    printf("Value of b is %f\n", b);
    printf("Value of c is %s\n", c);
    printf("wassup\"%s\"\n", c);
    return 0;
}