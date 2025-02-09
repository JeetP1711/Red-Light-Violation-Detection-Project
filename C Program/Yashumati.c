#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure to hold student details and a pointer to the next student
typedef struct Student {
    int id;                 // Student ID
    char name[50];          // Student name
    int maths, science, english;  // Marks in three subjects
    char department[50];    // Department of the student
    struct Student* next;   // Pointer to the next student in the linked list
} Student;

// Initialize the head of the linked list (start of student list)
Student* head = NULL;

// Function to add a new student to the linked list
void addStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student)); // Allocate memory for the new student

    // Get the student's details from the user
    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);
    printf("Enter Name: ");
    scanf("%s", newStudent->name);
    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english);
    printf("Enter Department: ");
    scanf("%s", newStudent->department);

    newStudent->next = NULL;  // The new student will be the last one in the list
    
    // Add the new student to the linked list
    if (!head) 
        head = newStudent;  // If the list is empty, set the new student as the head
    else {
        Student* temp = head;
        while (temp->next) 
            temp = temp->next;  // Traverse to the last student
        temp->next = newStudent;  // Add the new student to the end of the list
    }
}

// Function to display all students' details
void displayStudents() {
    Student* temp = head;
    while (temp) {
        printf("ID: %d, Name: %s, Marks: Maths: %d, Science: %d, English: %d, Department: %s\n", 
               temp->id, temp->name, temp->maths, temp->science, temp->english, temp->department);
        temp = temp->next;  // Move to the next student
    }
}

// Function to search for a student by ID
Student* searchStudent(int id) {
    Student* temp = head;
    while (temp) {
        if (temp->id == id) 
            return temp;  // Return the student if found
        temp = temp->next;
    }
    return NULL;  // Return NULL if the student is not found
}

// Function to delete a student by ID
void deleteStudent(int id) {
    Student* temp = head, *prev = NULL;

    // Traverse the list to find the student
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If student not found, return
    if (!temp) return;

    // Remove the student from the list
    if (!prev) 
        head = temp->next;  // If deleting the first student (head), update the head
    else 
        prev->next = temp->next;  // Link previous student to the next student

    free(temp);  // Free the memory of the deleted student
}

// Function to update a student's marks and department based on ID
void updateStudent(int id) {
    Student* temp = searchStudent(id);  // Find the student by ID
    if (temp) {
        // Update student's marks and department
        printf("Enter Updated Marks (Maths, Science, English): ");
        scanf("%d %d %d", &temp->maths, &temp->science, &temp->english);
        printf("Enter Updated Department: ");
        scanf("%s", temp->department);
    }
}

// Function to display the student with the highest total marks
void highestMarksStudent() {
    Student* temp = head, *topper = head;
    int maxMarks = 0;

    while (temp) {
        int total = temp->maths + temp->science + temp->english;
        if (total > maxMarks) {  // Update if a student has higher total marks
            maxMarks = total;
            topper = temp;
        }
        temp = temp->next;
    }

    // Display the top scorer's details
    if (topper)
        printf("Top Scorer: ID: %d, Name: %s, Total Marks: %d\n", topper->id, topper->name, maxMarks);
}

// Function to count the total number of students in the list
void countStudents() {
    int count = 0;
    Student* temp = head;

    // Traverse the list to count students
    while (temp) {
        count++;
        temp = temp->next;
    }

    // Display the total count
    printf("Total Students: %d\n", count);
}

// Function to sort students by total marks (either ascending or descending)
void sortStudents(int ascending) {
    // Nested loops to compare each pair of students
    for (Student* i = head; i && i->next; i = i->next) {
        for (Student* j = i->next; j; j = j->next) {
            int totalI = i->maths + i->science + i->english;
            int totalJ = j->maths + j->science + j->english;

            // Sort based on ascending or descending order
            if ((ascending && totalI > totalJ) || (!ascending && totalI < totalJ)) {
                // Swap the entire data of two students (this may break the linked list structure)
                Student temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}

// Function to calculate and display the average marks of all students
void averageMarks() {
    int sum = 0, count = 0;
    Student* temp = head;

    // Traverse the list to sum up all marks
    while (temp) {
        sum += temp->maths + temp->science + temp->english;
        count++;
        temp = temp->next;
    }

    // Calculate and display the average marks per subject
    if (count) 
        printf("Average Marks: %.2f\n", (float)sum / (count * 3));
}

// Main function to provide the menu-driven interface to the user
int main() {
    int choice, id;
    while (1) {
        // Display menu options
        printf("\n1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Update Student\n");
        printf("6. Highest Marks\n7. Count Students\n8. Sort Students\n9. Average Marks\n10. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        // Handle user's choice
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: 
                printf("Enter ID: "); 
                scanf("%d", &id); 
                searchStudent(id) ? printf("Student Found\n") : printf("Not Found\n"); 
                break;
            case 4: 
                printf("Enter ID: "); 
                scanf("%d", &id); 
                deleteStudent(id); 
                break;
            case 5: 
                printf("Enter ID: "); 
                scanf("%d", &id); 
                updateStudent(id); 
                break;
            case 6: highestMarksStudent(); break;
            case 7: countStudents(); break;
            case 8: 
                printf("1. Ascending 2. Descending: "); 
                scanf("%d", &id); 
                sortStudents(id == 1); 
                break;
            case 9: averageMarks(); break;
            case 10: exit(0);  // Exit the program
            default: printf("Invalid Choice\n");  // Invalid choice error message
        }
    }
    return 0;
}
