#include<stdio.h>

int main()
{
    float a;int i;
    printf("Enter a number\n");
    scanf("%f", &a);

    for (i = 0; i < 21; i++)
    {
        printf("%f x %d = %f\n", a, i, i * a);
    } 
    return 0;
}