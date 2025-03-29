#include<stdio.h>

void change(int* a)
{
    int b;
    printf("Enter the number of times to be increased\n");
    scanf("%d", &b);
    *a=*a*b;
    printf("The value of a is %d\n", *a);
}

int main()
{
    int c;
    printf("Enter the value of a number that needs to be increased\n");
    scanf("%d", &c);
    change(&c);
    return 0;
}