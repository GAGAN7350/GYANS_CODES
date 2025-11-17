#include<stdio.h>
#include<stdlib.h>
#define NO_DAYS 7
#define CHUNK 2
typedef struct
{
    char * NameD; /* Name of the Day */
    int DateD; /* Date of the day */
    char * ActivityD; /* Description of the activity of the day */
} Day;
Day * Calender, * tmp;
void create(void);
void read(int);
void Display(void);

int main()
{
    int i;
    create();
    printf("Enter the data for Caleder\n");
    for(i = 1; i<=7; i++)
    {
        read(i);
        ++Calender;
    }
    Calender = tmp;
    Display();
    // In a larger application, you would free the memory here.
}
void create(void)
{
    Calender = (Day *) calloc(NO_DAYS, sizeof(Day));
    tmp = Calender;
}
void read(int D)
{
    printf(" Enter the name of the Day- %d\n", D);
    Calender -> NameD = NULL;
    int size = 1, index = 0;
    int ch;
    Calender -> NameD = (char *) malloc(sizeof(char));
    ch = getc(stdin);
    if (ch == EOF || ch == '\n')
    {
        // FIX: Instead of returning, just create an empty string.
        Calender->NameD[0] = '\0';
    }
    else // FIX: Added else block to contain original logic
    {
        Calender -> NameD[index] = ch;
        while(ch) {
            ch = getc(stdin);
            // check if we need to stop
            if(ch == EOF || ch == '\n')
                ch = '\0';
            // check we need to expand
            if(size < (index+2))
            {
                size = size + CHUNK;
                Calender -> NameD = realloc(Calender -> NameD, size);
                if(!Calender -> NameD)
                {
                    printf(" Insuffcient Memory\n");
                    exit(0);
                }
            }
            index = index + 1;
            Calender -> NameD[index] = ch;
        }
    }

    printf(" Enter the date ofthe day %d - %s\n", D, Calender -> NameD);
    scanf("%d", &Calender -> DateD);
    ch =getc(stdin); // This correctly consumes the newline from scanf

    printf("Enter the description of the activity of %s \n", Calender -> NameD);
    Calender -> ActivityD = NULL;
    size = 1, index = 0;
    Calender -> ActivityD = (char *) malloc(sizeof(char));
    ch = getc(stdin);
    if (ch == EOF || ch == '\n')
    {
        // FIX: Same fix as above for the activity field.
        Calender->ActivityD[0] = '\0';
    }
    else // FIX: Added else block to contain original logic
    {
        Calender -> ActivityD[index] = ch;
        while(ch) {
            ch = getc(stdin);
            // check if we need to stop
            if(ch == EOF || ch == '\n')
                ch = '\0';
            // check we need to expand
            if(size < (index+2))
            {
                size = size + CHUNK;
                Calender -> ActivityD = realloc(Calender -> ActivityD, size);
                if(!Calender -> ActivityD)
                {
                    printf(" Insuffcient Memory\n");
                    exit(0);
                }
            }
            index = index + 1;
            Calender -> ActivityD[index] = ch;
        }
    }
}

void Display(void)
{
    int i;
    for(i=1; i<=7; i++)
    {
        printf(" --------%s %d --------\n", Calender -> NameD, Calender -> DateD);
        printf(" Activity : %s \n", Calender -> ActivityD);
        Calender++;
    }
}