#include<stdio.h>
int main()
{
    int a,b=0,i;
    printf("Enter a number\n");
    scanf("%d", &a);
    
    for(i=2; i<a;i++)
    {
        if(a%i==0)
        {
            b=1;
            break;
        }
    }    
        if(b)
          //This line checks whether the variable b has a non-zero value, specifically if b is true (i.e., not equal to 0).
          //Initially, b is set to 0 (false), which indicates that the number hasn't been identified as non-prime.
          //During the loop (line 10), if a divisor is found (i.e., a % i == 0), the variable b is set to 1 (true).
          // This signals that the number is not prime because it has at least one divisor other than 1 and itself.
          //Thus, line 16 (if (b)) is checking whether the flag b has been set to 1, which means the number is not prime.
          // If b is 1, it prints that the number is not prime.
        {
            printf("%d is not prime\n",a);
        }
        else
        {
            printf("%d is prime\n", a);
        }
    return 0;
    
}    