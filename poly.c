#include <stdio.h>
#include <stdlib.h> // For malloc
#include <math.h>   // For fmax (or write your own max function)

// Helper function to get the max of two ints
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Define the polynomial structure based on your description
typedef struct {
    int degree;       // n
    float *coeff;     // Array of size n+1
} polynomial;

// Function to add two polynomials: d = a + b
polynomial padd(polynomial a, polynomial b) {
    polynomial d; // The result polynomial

    // 1. Find the max degree and set up the result 'd'
    int max_degree = max(a.degree, b.degree);
    d.degree = max_degree;
    
    // 2. Allocate memory for the coefficients (from x^max_degree down to x^0)
    d.coeff = (float *)calloc(max_degree + 1, sizeof(float));
    if (d.coeff == NULL) {
        // Handle memory allocation failure
        d.degree = -1; // Indicate an error
        return d;
    }

    // 3. Iterate through exponents k from max_degree down to 0
    for (int k = max_degree; k >= 0; k--) {
        float a_coef = 0.0;
        float b_coef = 0.0;

        // 4. Find the coefficient from 'a' for exponent k
        if (k <= a.degree) {
            // Index in 'a' is a.degree - k
            a_coef = a.coeff[a.degree - k];
        }

        // 4. Find the coefficient from 'b' for exponent k
        if (k <= b.degree) {
            // Index in 'b' is b.degree - k
            b_coef = b.coeff[b.degree - k];
        }

        // 5. Add and store in 'd'
        // Index in 'd' is max_degree - k
        d.coeff[max_degree - k] = a_coef + b_coef;
    }

    // 6. Find the *true* degree in case of cancellation
    int new_degree = -1; // Assume zero polynomial
    for (int i = 0; i <= max_degree; i++) {
        if (d.coeff[i] != 0.0) {
            new_degree = max_degree - i; // Found the leading term
            break;
        }
    }
    
    d.degree = new_degree;
    
    // Optional: If the new degree is much smaller, you could reallocate
    // d.coeff to save space, but that's a more advanced optimization.

    return d;
}

// Helper function to print a polynomial for testing
void print_poly(polynomial p) {
    if (p.degree == -1) {
        printf("0\n");
        return;
    }
    for (int i = 0; i <= p.degree; i++) {
        int exponent = p.degree - i;
        printf("(%.1f)x^%d", p.coeff[i], exponent);
        if (exponent > 0) {
            printf(" + ");
        }
    }
    printf("\n");
}

// --- Example Usage ---
int main() {
    // a = 3x^2 + 2x + 1
    polynomial a;
    a.degree = 2;
    a.coeff = (float *)malloc(sizeof(float) * (a.degree + 1));
    a.coeff[0] = 3.0; // coeff for x^2
    a.coeff[1] = 2.0; // coeff for x^1
    a.coeff[2] = 1.0; // coeff for x^0

    // b = 5x^3 + 4x - 6
    polynomial b;
    b.degree = 3;
    b.coeff = (float *)malloc(sizeof(float) * (b.degree + 1));
    b.coeff[0] = 5.0; // coeff for x^3
    b.coeff[1] = 0.0; // coeff for x^2
    b.coeff[2] = 4.0; // coeff for x^1
    b.coeff[3] = -6.0; // coeff for x^0

    printf("A(x) = ");
    print_poly(a);
    printf("B(x) = ");
    print_poly(b);

    // d = a + b
    polynomial d = padd(a, b);
    
    // Result should be: 5x^3 + 3x^2 + 6x - 5
    printf("\nD(x) = ");
    print_poly(d);

    // --- Example with cancellation ---
    // a = 2x + 1
    // b = -2x + 5
    // d = 6
    a.degree = 1;
    a.coeff[0] = 2.0;
    a.coeff[1] = 1.0;
    
    b.degree = 1;
    b.coeff[0] = -2.0;
    b.coeff[1] = 5.0;
    
    polynomial d2 = padd(a, b);
    printf("\nCancellation Example:\n");
    printf("A(x) = ");
    print_poly(a);
    printf("B(x) = ");
    print_poly(b);
    printf("D2(x) = ");
    print_poly(d2); // Should print (6.0)x^0

    // Free memory
    free(a.coeff);
    free(b.coeff);
    free(d.coeff);
    free(d2.coeff);

    return 0;
}