#include<stdio.h>

void swap(int* a, int* b)
{
    int c;
    c=*a;
    *a=*b;
    *b=c;
}

int main()
{
    int a,b;
    printf("Enter the value of a\n");
    scanf("%d", &a);
    printf("Enter the value of b\n");
    scanf("%d", &b);
    swap(&a,&b);
    printf("The value of a and b after swapping is %d and %d\n", a, b);
    return 0;
}
//my way of doing it
//printf("The value of a and b after swapping is %d and %d\n", b, a);
//return 0;