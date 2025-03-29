#include<stdio.h>

void array(int a[], int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("The value of arr[%d] is %d\n", i, a[i]);
    }
}

void reverse(int arr[],int n)
{
    int temp,i;
    for(i=0;i<n/2;i++)
    {
        temp=arr[i];
        arr[i]=arr[n-1-i];
        arr[n-1-i]=temp;
        printf("The value of a[%d] is %d\n", i, arr[i]);
        printf("The value of a[%d] is %d\n", n-1-i, arr[n-1-i]);
    }
}

int main()
{
    
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    reverse(a,10);
    return 0;
}