#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student details
typedef struct Student {
    int id;
    char name[50];
    char department[50];
    int maths, science, english;
    struct Student* next;
} Student;

Student* head = NULL; // Head of the linked list

// Function to insert a new student record at the end
void insertStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);
    getchar(); // Consume newline character
    
    printf("Enter Name: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0'; // Remove newline character
    
    printf("Enter Department: ");
    fgets(newStudent->department, sizeof(newStudent->department), stdin);
    newStudent->department[strcspn(newStudent->department, "\n")] = '\0';
    
    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english);
    
    newStudent->next = NULL;
    
    if (head == NULL) {
        head = newStudent;
    } else {
        Student* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
    printf("Student record added successfully!\n");
}

// Function to display all student records
void displayStudents() {
    if (head == NULL) {
        printf("No student records found!\n");
        return;
    }
    Student* temp = head;
    while (temp != NULL) {
        printf("\nStudent ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Department: %s\n", temp->department);
        printf("Marks - Maths: %d, Science: %d, English: %d\n", temp->maths, temp->science, temp->english);
        temp = temp->next;
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Insert Student Record\n");
        printf("2. Display Student Records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                insertStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}