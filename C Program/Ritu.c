#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[50];
    char department[50];
    int maths, science, english;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void insertStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full!\n");
        return;
    }
    
    printf("Enter Student ID: ");
    scanf("%d", &students[studentCount].id);
    getchar();

    printf("Enter Name: ");
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(students[studentCount].department, sizeof(students[studentCount].department), stdin);
    students[studentCount].department[strcspn(students[studentCount].department, "\n")] = '\0';

    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &students[studentCount].maths, &students[studentCount].science, &students[studentCount].english);

    studentCount++;
    printf("Student record added successfully!\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No student records found!\n");
        return;
    }
    
    for (int i = 0; i < studentCount; i++) {
        printf("\nStudent ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Department: %s\n", students[i].department);
        printf("Marks - Maths: %d, Science: %d, English: %d\n", students[i].maths, students[i].science, students[i].english);
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