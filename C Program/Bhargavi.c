#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure
typedef struct Student {
    int id;                // Student ID
    char name[50];         // Student name
    char department[50];   // Student department
    int maths, science, english; // Student marks
    struct Student *next;  // Pointer to the next student in the linked list
} Student;

Student *head = NULL; // Head of the linked list, initially empty

// Function to insert a new student record
void insertStudent() {
    // Allocate memory for the new student
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Memory allocation failed!\n"); // Check for memory allocation failure
        return;
    }

    // Input student details
    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id); // Read the student ID
    getchar(); // Consume the newline character left by scanf

    printf("Enter Name: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin); // Read the student's name
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0'; // Remove the newline character at the end of the string

    printf("Enter Department: ");
    fgets(newStudent->department, sizeof(newStudent->department), stdin); // Read the student's department
    newStudent->department[strcspn(newStudent->department, "\n")] = '\0'; // Remove the newline character at the end of the string

    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english); // Read the student's marks

    // Insert the new student at the beginning of the linked list
    newStudent->next = head;
    head = newStudent; // Update the head to point to the new student

    printf("Student record added successfully!\n"); // Confirm successful addition
}

// Function to display all student records
void displayStudents() {
    if (!head) {
        printf("No student records found!\n"); // Check if the list is empty
        return;
    }

    // Traverse the linked list and print each student's details
    Student *temp = head;
    printf("\n--- Student Records ---\n");
    while (temp) {
        printf("\nID: %d\nName: %s\nDepartment: %s\nMarks - Maths: %d, Science: %d, English: %d\n",
               temp->id, temp->name, temp->department, temp->maths, temp->science, temp->english);
        temp = temp->next; // Move to the next student
    }
}

// Function to delete a student record by ID
void deleteStudent() {
    if (!head) {
        printf("No student records to delete!\n"); // Check if the list is empty
        return;
    }

    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id); // Read the student ID to delete

    Student *temp = head, *prev = NULL; // Temp pointer to traverse the list, prev to keep track of the previous node
    // Traverse the list to find the student with the given ID
    while (temp) {
        if (temp->id == id) {
            // Remove the student from the linked list
            if (prev) prev->next = temp->next;
            else head = temp->next; // If deleting the head, update the head pointer
            free(temp); // Free the memory allocated to the student
            printf("Student record deleted successfully!\n");
            return;
        }
        prev = temp; // Update prev to the current node
        temp = temp->next; // Move to the next node
    }

    printf("Student with ID %d not found!\n", id); // Student ID not found in the list
}

int main() {
    int choice;
    // Menu-driven program to manage student records
    while (1) {
        printf("\n1. Insert Student Record\n2. Display Student Records\n3. Delete Student Record\n4. Exit\nEnter choice: ");
        scanf("%d", &choice); // Read the user's choice

        // Call the appropriate function based on the user's choice
        switch (choice) {
            case 1: insertStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: return 0; // Exit the program
            default: printf("Invalid choice! Try again.\n");
        }
    }
}
