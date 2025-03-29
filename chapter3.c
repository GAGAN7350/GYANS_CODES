#include<stdio.h>

int main()
{
    char c;
    printf("Enter a character\n");
    scanf("%c", &c);

    if(c>='a' && c<='z')
    {
        printf("The entered character is a lowercase alphabet\n");
    }
    else if(c>='A' && c<='Z')
    {
        printf("The entered character is a uppercase alphabet\n");
    }
    else if(c>='0' && c<='9')
    {
        printf("The entered character is a digit\n");
    }
    else
    {
        printf("The entered character is a special character\n");
    }
}