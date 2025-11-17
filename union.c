#include <stdio.h>
#include <string.h> // Needed for strcpy

// 1. Define the 'date' type, as it was missing
typedef struct {
    int day;
    int month;
    int year;
} date;

// 2. Define the 'sex_type' struct (using underscores)
// This is a "tagged union"
typedef struct sex_type {
    // The 'tag_field' tells us which union member is active
    enum tag_field { female, male } sex;
    
    // The 'union' shares memory
    // It can ONLY hold 'children' OR 'beard', not both.
    union {
        int children; // Active if sex is female
        int beard;    // Active if sex is male
    } u;
} sex_type;

// 3. Define the 'human_being' struct
typedef struct human_being {
    char name[10];
    int age;
    float salary;
    date dob;
    sex_type sex_info; // Nested struct
} human_being;

// --- How to Use The Code ---
int main() {
    // 4. Declare variables (using 'person1')
    human_being person1, person2;

    // --- Initialize person1 (Female) ---
    strcpy(person1.name, "Alice"); // Use strcpy for char arrays
    person1.age = 30;
    person1.salary = 70000.50;
    person1.dob.day = 10;
    person1.dob.month = 5;
    person1.dob.year = 1994;
    
    // Set the 'tag' for the union
    person1.sex_info.sex = female; 
    // Now, we can safely use the 'children' member
    person1.sex_info.u.children = 2;

    // --- Initialize person2 (Male) ---
    strcpy(person2.name, "Bob");
    person2.age = 45;
    person2.salary = 85000.00;
    person2.dob.day = 20;
    person2.dob.month = 8;
    person2.dob.year = 1979;

    // Set the 'tag' for the union
    person2.sex_info.sex = male;
    // Now, we can safely use the 'beard' member
    person2.sex_info.u.beard = 1; // 1 for 'true' (has a beard)

    // --- How to Access the Data Safely ---
    printf("Person 1 Name: %s\n", person1.name);
    
    // We MUST check the tag before accessing the union
    if (person1.sex_info.sex == female) {
        printf("Sex: Female\n");
        printf("Number of children: %d\n", person1.sex_info.u.children);
    } else {
        printf("Sex: Male\n");
    }

    printf("\nPerson 2 Name: %s\n", person2.name);
    if (person2.sex_info.sex == male) {
        printf("Sex: Male\n");
        printf("Has beard (1=yes, 0=no): %d\n", person2.sex_info.u.beard);
    } else {
        printf("Sex: Female\n");
    }

    return 0;
}