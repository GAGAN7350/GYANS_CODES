#include<stdio.h>

int positive(int a[],int n)
{
    int b=0,i;
    for(i=0;i<n;i++)
    {
        if(a[i]>0)
        {
            b++;
        }
    
    }
    return b;

} 

int main()
{
    int a[10]={1,-2,3,-4,5,6,-7,8,9,-10};
    printf("The number of positive numbers in the array is %d\n", positive(a,10));
    return 0;
}