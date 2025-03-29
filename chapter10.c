#include<stdio.h>

int main()
{
  FILE *a;
  int n;
  a=fopen("zoro.txt", "r");
  fscanf(a, "%d", &n);
  printf("The value of n is %d\n", n);
  fclose(a);

  a=fopen("zoro.txt", "w");
  fprintf(a, "%d", n);
  printf("The value of n is %d\n",2*n);
  fclose(a);
  return 0;
}