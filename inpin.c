#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Required for isalnum()

#define MAX 100

// --- Globals for the Stack ---
char stack[MAX];
int top = -1;

// --- Stack Function Prototypes ---
void push(char item);
char pop(void);
int get_priority(char op);

int main() {
    char infix[100];
    char postfix[100];
    char *e; // Pointer to iterate through infix expression
    int pos = 0; // Position in the postfix string
    char ch;

    printf("Enter the Infix Expression: ");
    scanf("%s", infix);
    printf("\n");

    e = infix; // Point 'e' to the start of the string

    // 1. Iterate through the infix expression
    while (*e != '\0') {
        
        // 2. If it's an operand (alphanumeric), add to postfix
        if (isalnum(*e)) {
            postfix[pos++] = *e;
        }
        // 3. If it's an opening parenthesis, push to stack
        else if (*e == '(') {
            push(*e);
        }
        // 4. If it's a closing parenthesis...
        else if (*e == ')') {
            // Pop from stack and add to postfix until '(' is found
            while ((ch = pop()) != '(' && top != -2) { // -2 check for stack empty
                postfix[pos++] = ch;
            }
        }
        // 5. If it's an operator
        else {
            char op = *e; // The current operator

            // Handle Right-Associativity for ^
            if (op == '^') {
                while (top != -1 && stack[top] != '(' && get_priority(stack[top]) > get_priority(op)) {
                    postfix[pos++] = pop();
                }
            }
            // Handle Left-Associativity for all other operators
            else {
                while (top != -1 && stack[top] != '(' && get_priority(stack[top]) >= get_priority(op)) {
                    postfix[pos++] = pop();
                }
            }
            // Push the current operator onto the stack
            push(op);
        }
        
        e++; // Move to the next character in the infix string
    }

    // 6. After loop, pop any remaining operators from stack
    while (top != -1) {
        postfix[pos++] = pop();
    }

    // Add null terminator to postfix string
    postfix[pos] = '\0';

    printf("Postfix Expression is: %s\n", postfix);

    return 0;
}

// --- Stack Function Definitions ---

// Pushes a character onto the stack
void push(char item) {
    if (top >= MAX - 1) {
        printf("Stack Overflow.\n");
        return;
    }
    stack[++top] = item;
}

// Pops a character from the stack
char pop(void) {
    if (top == -1) {
        printf("Stack Underflow (mismatched parentheses?).\n");
        // Return a special value or handle error
        // Setting top to -2 as a flag for the ')' loop
        top = -2; 
        return '\0'; 
    }
    return stack[top--];
}

// Returns the precedence of an operator
int get_priority(char op) {
    switch (op) {
        case '(':
            return 0; // Lowest precedence
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3; // Highest precedence
        default:
            return 0;
    }
}