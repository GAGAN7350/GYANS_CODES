#include<stdio.h>

struct date
{
    int day;
    int month;
    int year;
};

int compare(struct date d1, struct date d2)
{
    if(d1.year==d2.year && d1.month==d2.month && d1.day==d2.day)
    {
        return 0;
    }
    if(d1.year>d2.year)
    {
        return 1;
    }
    if(d1.year<d2.year)
    {
        return -1;
    }
    if(d1.month>d2.month)
    {
        return 1;
    }
    if(d1.month<d2.month)
    {
        return -1;
    }
    if(d1.day>d2.day)
    {
        return 1;
    }
    if(d1.day<d2.day)
    {
        return -1;
    }
    return 0;
}
int main()
{
    struct date d1, d2;

    scanf("%d  ", &d1.day);
    scanf("%d  ", &d1.month);
    scanf("%d  ", &d1.year);
    printf("The date is %d/%d/%d\n", d1.day, d1.month, d1.year);
    scanf("%d  ", &d2.day);
    scanf("%d  ", &d2.month);
    scanf("%d  ", &d2.year);
    printf("The date is %d/%d/%d\n", d2.day, d2.month, d2.year);
    printf("%d",compare(d1,d2));
    return 0;
}