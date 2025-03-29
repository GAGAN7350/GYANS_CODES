#include<stdio.h>
#include<string.h>

int main()
{
    char a;
    int b=0;
    char c[100]; 
    printf("Enter the  character to find:\n");
    scanf("%c", &a);
    printf("Enter a word:\n");
    scanf("%s", c);
    for(size_t i=0; i<strlen(c); i++)
    {
        if(c[i]==a)
        {
            b=1;
            break;
        }
    }
    if(b)
    {
        printf("The character %c is present in the word %s\n", a, c);
    }
    else
    {
        printf("The character %c is not present in the word %s\n", a, c);
    }

    return 0;
}