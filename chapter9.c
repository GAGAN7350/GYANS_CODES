#include <stdio.h>
typedef struct 
{
    float x, y, z;
} Vector3D;

//addition two vectors
Vector3D add(Vector3D a, Vector3D b) 
{
    Vector3D result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

//subtraction two vectors
Vector3D subtract(Vector3D a, Vector3D b) 
{
    Vector3D result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

//dot product of two vectors
float dot_product(Vector3D a, Vector3D b) 
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

//cross product of two vectors
Vector3D cross_product(Vector3D a, Vector3D b) 
{
    Vector3D result =
    {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return result;
}

// Function to display a vector
void display_vector(Vector3D v) 
{
    printf("Vector: (%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

// Main function
int main() 
{
    Vector3D v1, v2, result;
    float dot;

    // Input vectors from the user
    printf("Enter first vector (x y z): ");
    scanf("%f %f %f", &v1.x, &v1.y, &v1.z);

    printf("Enter second vector (x y z): ");
    scanf("%f %f %f", &v2.x, &v2.y, &v2.z);

    // Perform operations
    result = add(v1, v2);
    printf("\nVector Addition: ");
    display_vector(result);

    result = subtract(v1, v2);
    printf("Vector Subtraction: ");
    display_vector(result);

    dot = dot_product(v1, v2);
    printf("Dot Product: %.2f\n", dot);

    result = cross_product(v1, v2);
    printf("Cross Product: ");
    display_vector(result);

    return 0;
}
