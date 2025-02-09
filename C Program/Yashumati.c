#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[50];
    int maths, science, english;
    char department[50];
    struct Student* next;
} Student;

Student* head = NULL;

void addStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    printf("Enter Student ID: ");
    scanf("%d", &newStudent->id);
    printf("Enter Name: ");
    scanf("%s", newStudent->name);
    printf("Enter Marks (Maths, Science, English): ");
    scanf("%d %d %d", &newStudent->maths, &newStudent->science, &newStudent->english);
    printf("Enter Department: ");
    scanf("%s", newStudent->department);
    newStudent->next = NULL;
    
    if (!head) head = newStudent;
    else {
        Student* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newStudent;
    }
}

void displayStudents() {
    Student* temp = head;
    while (temp) {
        printf("ID: %d, Name: %s, Marks: Maths: %d, Science: %d, English: %d, Department: %s\n", 
               temp->id, temp->name, temp->maths, temp->science, temp->english, temp->department);
        temp = temp->next;
    }
}

Student* searchStudent(int id) {
    Student* temp = head;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

void deleteStudent(int id) {
    Student* temp = head, *prev = NULL;
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return;
    if (!prev) head = temp->next;
    else prev->next = temp->next;
    free(temp);
}

void updateStudent(int id) {
    Student* temp = searchStudent(id);
    if (temp) {
        printf("Enter Updated Marks (Maths, Science, English): ");
        scanf("%d %d %d", &temp->maths, &temp->science, &temp->english);
        printf("Enter Updated Department: ");
        scanf("%s", temp->department);
    }
}

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

void countStudents() {
    int count = 0;
    Student* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    printf("Total Students: %d\n", count);
}

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
