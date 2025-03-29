#include<stdio.h>

int main()
{
    int a,i,j;
    printf("Enter a number\n");
    scanf("%d", &a);
    for(i=0;i<a;i++)
    {
        for(j=0;j<i*2+1;j++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}