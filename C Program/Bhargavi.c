#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student structure with doubly linked list
typedef struct Student {
    int id;
    char name[50];
    char department[50];
    int maths, science, english;
    struct Student *prev, *next;
} Student;

Student *head = NULL, *tail = NULL;

// Function to insert a new student at the end
void insertStudent() {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);
    getchar();

    printf("Enter Name: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(newStudent->department, sizeof(newStudent->department), stdin);
    newStudent->department[strcspn(newStudent->department, "\n")] = '\0';

    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english);

    newStudent->prev = tail;
    newStudent->next = NULL;

    if (tail) tail->next = newStudent;
    tail = newStudent;
    if (!head) head = newStudent;

    printf("Student record added successfully!\n");
}

// Function to display all students
void displayStudents() {
    if (!head) {
        printf("No student records found!\n");
        return;
    }

    Student *temp = head;
    printf("\n--- Student Records ---\n");
    while (temp) {
        printf("\nID: %d\nName: %s\nDepartment: %s\nMarks - Maths: %d, Science: %d, English: %d\n",
               temp->id, temp->name, temp->department, temp->maths, temp->science, temp->english);
        temp = temp->next;
    }
}

// Function to delete a student by ID
void deleteStudent() {
    if (!head) {
        printf("No student records to delete!\n");
        return;
    }

    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    Student *temp = head;
    while (temp) {
        if (temp->id == id) {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            if (temp == tail) tail = temp->prev;
            free(temp);
            printf("Student record deleted successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Student with ID %d not found!\n", id);
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Insert Student Record\n2. Display Student Records\n3. Delete Student Record\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}