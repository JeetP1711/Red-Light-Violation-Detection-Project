#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[50];
    char department[50];
    int maths, science, english;
    struct Student *next;
} Student;

Student *head = NULL;

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

    newStudent->next = head;
    head = newStudent;

    printf("Student record added successfully!\n");
}

void displayStudents() {
    Student *temp = head;
    if (!temp) {
        printf("No student records found!\n");
        return;
    }

    while (temp) {
        printf("\nID: %d\nName: %s\nDepartment: %s\nMarks - Maths: %d, Science: %d, English: %d\n",
               temp->id, temp->name, temp->department, temp->maths, temp->science, temp->english);
        temp = temp->next;
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Insert Student Record\n2. Display Student Records\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertStudent(); break;
            case 2: displayStudents(); break;
            case 3: return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}