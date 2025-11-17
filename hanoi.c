#include <stdio.h>
void h(int n,char a,char b,char c)
{
    if(n>0)
           { 
             h(n-1,a,c,b);
             printf("Move disk %d from %c to %c\n",n,a,c);h(n-1,b,a,c);
            }
}
int main()
{
    h(3,'A','B','C');return 0;
}