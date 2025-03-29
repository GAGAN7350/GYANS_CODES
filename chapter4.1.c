#include<stdio.h>
 int main()
 {
    int a,i;int fact=1;
    printf("Enter a number\n"); 
    scanf("%d", &a);

    for(i=1; i<=a; i++)
    {
        fact=fact*i;
    }
    printf("The factorial of %d is %d\n", a, fact);
    return 0;
 }