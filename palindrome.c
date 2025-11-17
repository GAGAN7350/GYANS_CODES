#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 100
#define ERROR_CODE 999

int STACK[STACK_MAX_SIZE];
int top = -1;

void push(int);
int pop(void);
void STACKFull(void);
int STACKEmpty(void);
void display(void);
void palindrome(void);

int main()
{
    int ch;
    int ele;

    while (1)
    {
        printf("\n--- STACK MENU ---\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. DISPLAY\n");
        printf("4. CHECK PALINDROME\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter the element to be inserted: ");
            scanf("%d", &ele);
            push(ele);
            break;
        case 2:
            ele = pop();
            if (ele != ERROR_CODE)
                printf("Popped out element is %d\n", ele);
            break;
        case 3:
            display();
            break;
        case 4:
            palindrome();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}

void push(int ele)
{
    if (top >= STACK_MAX_SIZE - 1)
    {
        STACKFull();
    }
    else
    {
        STACK[++top] = ele;
    }
}

int pop()
{
    if (top == -1)
    {
        return STACKEmpty();
    }
    else
    {
        return STACK[top--];
    }
}

void STACKFull(void)
{
    printf("STACK OVERFLOW\n");
}

int STACKEmpty(void)
{
    printf("STACK UNDERFLOW\n");
    return ERROR_CODE;
}

void display(void)
{
    int i;
    if (top == -1)
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("Stack elements are:\n");
        for (i = top; i >= 0; i--)
        {
            printf("%d\n", STACK[i]);
        }
    }
}

void palindrome(void)
{
    if (top == -1)
    {
        printf("Stack is empty, cannot check for palindrome.\n");
        return;
    }

    int i = 0;
    int j = top;
    int flag = 1;

    while (i < j)
    {
        if (STACK[i] != STACK[j])
        {
            flag = 0;
            break;
        }
        i++;
        j--;
    }

    if (flag == 1)
        printf("The sequence in the stack is a Palindrome.\n");
    else
        printf("The sequence in the stack is Not a Palindrome.\n");
}