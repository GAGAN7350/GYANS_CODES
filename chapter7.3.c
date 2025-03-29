#include<stdio.h>

int main()
{
    int a[2][3][4];
    int i,j,k;
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
        {
            for(k=0;k<4;k++)
            {
                printf("The address of a[%d][%d][%d] is %p\n", i,j,k, &a[i][j][k]);
            }
        }
    }
    return 0;
    
}