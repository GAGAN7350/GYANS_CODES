#include<stdio.h>

int main()
{
    float a,b;
    printf("Enter the value of 1st Integer\n");
    scanf("%f", &a);

    printf("Enter the value of 2nd Integer\n");
    scanf("%f", &b);

    printf("The sum of a and b is %f\n", a+b);
    printf("The difference of a and b is %f\n", a-b);
    printf("The product of a and b is %f\n", a*b);
    printf("The division of a and b is %f\n", a/b);
    return 0;
}
