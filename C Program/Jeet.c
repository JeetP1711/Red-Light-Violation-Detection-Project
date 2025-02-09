#include <stdio.h>  // Standard input-output operations
#include <stdlib.h> // Memory allocation and process control
#include <string.h> // String handling functions

// Define a structure to store student details
typedef struct Student {
    int id; // Student ID
    char name[50]; // Student name
    int maths, science, english; // Marks in three subjects
    char department[50]; // Department name
    struct Student* next; // Pointer to the next student in the list
} Student;

Student* head = NULL; // Initialize the head of the linked list

// Function to add a student record
void addStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student)); // Allocate memory for a new student
    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);
    printf("Enter Name: ");
    scanf("%s", newStudent->name);
    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english);
    printf("Enter Department: ");
    scanf("%s", newStudent->department);
    newStudent->next = head; // Insert student at the beginning of the list
    head = newStudent; // Update head pointer
}

// Function to display all student records
void displayStudents() {
    Student* temp = head;
    while (temp) { // Traverse the linked list
        printf("ID: %d, Name: %s, Marks: Maths: %d, Science: %d, English: %d, Department: %s\n", 
               temp->id, temp->name, temp->maths, temp->science, temp->english, temp->department);
        temp = temp->next; // Move to next student
    }
}

// Function to search for a student by ID
Student* searchStudent(int id) {
    Student* temp = head;
    while (temp) {
        if (temp->id == id) return temp; // Return student if found
        temp = temp->next;
    }
    return NULL; // Return NULL if not found
}

// Function to delete a student record by ID
void deleteStudent(int id) {
    Student* temp = head, *prev = NULL;
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return; // If student not found, exit
    if (!prev) head = temp->next; // If deleting head, update head
    else prev->next = temp->next; // Unlink the node
    free(temp); // Free memory
}

// Function to update a student's details
void updateStudent(int id) {
    Student* temp = searchStudent(id);
    if (temp) {
        printf("Enter New Marks (Maths, Science, English): ");
        scanf("%d %d %d", &temp->maths, &temp->science, &temp->english);
        printf("Enter New Department: ");
        scanf("%s", temp->department);
    }
}

// Function to find the student with the highest marks
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
    printf("Topper: ID: %d, Name: %s, Total Marks: %d\n", topper->id, topper->name, maxMarks);
}

// Function to count the total number of students
void countStudents() {
    int count = 0;
    Student* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    printf("Total Students: %d\n", count);
}

// Function to reverse the student list
void reverseList() {
    Student *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

// Function to sort students by total marks
void sortStudents(int ascending) {
    for (Student* i = head; i; i = i->next) {
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

// Function to calculate the average marks of all students
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

// Main function to handle user interactions
int main() {
    int choice, id;
    while (1) {
        printf("\n1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Update Student\n");
        printf("6. Highest Marks\n7. Count Students\n8. Reverse List\n9. Sort Students\n10. Average Marks\n11. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: printf("Enter ID: "); scanf("%d", &id); 
                    searchStudent(id) ? printf("Found Student\n") : printf("Not Found\n"); break;
            case 4: printf("Enter ID: "); scanf("%d", &id); deleteStudent(id); break;
            case 5: printf("Enter ID: "); scanf("%d", &id); updateStudent(id); break;
            case 6: highestMarksStudent(); break;
            case 7: countStudents(); break;
            case 8: reverseList(); break;
            case 9: printf("1. Ascending 2. Descending: "); scanf("%d", &id); sortStudents(id == 1); break;
            case 10: averageMarks(); break;
            case 11: exit(0);
            default: printf("Invalid Choice\n");
        }
    }
    return 0;
}
