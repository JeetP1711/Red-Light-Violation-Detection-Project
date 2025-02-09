#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for Student records
typedef struct Student {
    int id;  // Student ID
    char name[50];  // Student Name
    int maths, science, english;  // Marks in three subjects
    char department[50];  // Department Name
    struct Student* next;  // Pointer to next student in the list
} Student;

Student* head = NULL; // Initialize head pointer to NULL

// Function to add a new student record
void addStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student)); // Allocate memory for new student
    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);
    printf("Enter Name: ");
    scanf("%s", newStudent->name);
    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english);
    printf("Enter Department: ");
    scanf("%s", newStudent->department);
    newStudent->next = NULL;
    
    if (!head) head = newStudent; // If list is empty, set new student as head
    else {
        Student* temp = head;
        while (temp->next) temp = temp->next; // Traverse to the last node
        temp->next = newStudent; // Append new student at the end
    }
}

// Function to display all student records
void displayStudents() {
    Student* temp = head;
    while (temp) {
        printf("ID: %d, Name: %s, Marks: Maths: %d, Science: %d, English: %d, Department: %s\n", 
               temp->id, temp->name, temp->maths, temp->science, temp->english, temp->department);
        temp = temp->next;
    }
}

// Function to search for a student by ID
Student* searchStudent(int id) {
    Student* temp = head;
    while (temp) {
        if (temp->id == id) return temp; // Return student if ID matches
        temp = temp->next;
    }
    return NULL; // Return NULL if student not found
}

// Function to delete a student record by ID
void deleteStudent(int id) {
    Student* temp = head, *prev = NULL;
    while (temp && temp->id != id) { // Traverse the list to find student
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return; // If student not found, return
    if (!prev) head = temp->next; // If deleting head node, update head
    else prev->next = temp->next; // Else, unlink node
    free(temp); // Free memory
}

// Function to update student details
void updateStudent(int id) {
    Student* temp = searchStudent(id);
    if (temp) {
        printf("Enter Updated Marks (Maths, Science, English): ");
        scanf("%d %d %d", &temp->maths, &temp->science, &temp->english);
        printf("Enter Updated Department: ");
        scanf("%s", temp->department);
    }
}

// Function to find the student with highest marks
void highestMarksStudent() {
    Student* temp = head, *topper = head;
    int maxMarks = 0;
    while (temp) {
        int total = temp->maths + temp->science + temp->english;
        if (total > maxMarks) {
            maxMarks = total;
            topper = temp;
        }
        temp = temp->next;
    }
    if (topper)
        printf("Top Scorer: ID: %d, Name: %s, Total Marks: %d\n", topper->id, topper->name, maxMarks);
}

// Function to count total students
void countStudents() {
    int count = 0;
    Student* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    printf("Total Students: %d\n", count);
}

// Function to sort students by total marks (ascending or descending)
void sortStudents(int ascending) {
    for (Student* i = head; i && i->next; i = i->next) {
        for (Student* j = i->next; j; j = j->next) {
            int totalI = i->maths + i->science + i->english;
            int totalJ = j->maths + j->science + j->english;
            if ((ascending && totalI > totalJ) || (!ascending && totalI < totalJ)) {
                Student temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}

// Function to calculate average marks of all students
void averageMarks() {
    int sum = 0, count = 0;
    Student* temp = head;
    while (temp) {
        sum += temp->maths + temp->science + temp->english;
        count++;
        temp = temp->next;
    }
    if (count) printf("Average Marks: %.2f\n", (float)sum / (count * 3));
}

// Main function to display menu and handle user choices
int main() {
    int choice, id;
    while (1) {
        printf("\n1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Update Student\n");
        printf("6. Highest Marks\n7. Count Students\n8. Sort Students\n9. Average Marks\n10. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: printf("Enter ID: "); scanf("%d", &id); 
                    searchStudent(id) ? printf("Student Found\n") : printf("Not Found\n"); break;
            case 4: printf("Enter ID: "); scanf("%d", &id); deleteStudent(id); break;
            case 5: printf("Enter ID: "); scanf("%d", &id); updateStudent(id); break;
            case 6: highestMarksStudent(); break;
            case 7: countStudents(); break;
            case 8: printf("1. Ascending 2. Descending: "); scanf("%d", &id); sortStudents(id == 1); break;
            case 9: averageMarks(); break;
            case 10: exit(0);
            default: printf("Invalid Choice\n");
        }
    }
    return 0;
}
