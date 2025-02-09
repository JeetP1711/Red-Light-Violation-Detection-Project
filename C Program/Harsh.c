#include <stdio.h>  // Standard I/O operations
#include <stdlib.h> // Memory allocation, process control
#include <string.h> // String handling functions

// Define a structure for storing student details
typedef struct Student {
    int id; // Student ID
    char name[50]; // Student Name
    char department[50]; // Department Name
    int maths, science, english; // Marks in three subjects
    struct Student *next; // Pointer to the next student in the list
} Student;

Student *head = NULL; // Initialize the head pointer to NULL

// Function to insert a new student record
void insertStudent() {
    Student *newStudent = (Student *)malloc(sizeof(Student)); // Allocate memory for a new student
    if (!newStudent) { // Check if memory allocation was successful
        printf("Memory allocation failed!\n");
        return;
    }

    // Get student details
    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);
    getchar(); // Consume newline character left by scanf

    printf("Enter Name: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin); // Read full name with spaces
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Department: ");
    fgets(newStudent->department, sizeof(newStudent->department), stdin);
    newStudent->department[strcspn(newStudent->department, "\n")] = '\0';

    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english); // Read marks

    newStudent->next = head; // Insert the new student at the beginning of the list
    head = newStudent; // Update head to point to the new student

    printf("Student record added successfully!\n");
}

// Function to display all student records
void displayStudents() {
    Student *temp = head; // Start from the head of the list
    if (!temp) { // Check if the list is empty
        printf("No student records found!\n");
        return;
    }

    // Traverse the list and display each student's details
    while (temp) {
        printf("\nID: %d\nName: %s\nDepartment: %s\nMarks - Maths: %d, Science: %d, English: %d\n",
               temp->id, temp->name, temp->department, temp->maths, temp->science, temp->english);
        temp = temp->next; // Move to the next student in the list
    }
}

// Main function to display menu and handle user choices
int main() {
    int choice; // Variable to store user choice
    while (1) { // Infinite loop to keep the program running until exit
        printf("\n1. Insert Student Record\n2. Display Student Records\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) { // Handle user choice
            case 1: insertStudent(); break; // Insert a new student
            case 2: displayStudents(); break; // Display all students
            case 3: return 0; // Exit the program
            default: printf("Invalid choice! Try again.\n"); // Handle invalid input
        }
    }
}
