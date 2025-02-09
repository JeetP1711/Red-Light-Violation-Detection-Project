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
    newStudent->next = head;
    head = newStudent;
}

void displayStudents() {
    Student* temp = head;
    while (temp) {
        printf("ID: %d, Name: %s, Marks: %d %d %d, Department: %s\n", 
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
        printf("Enter New Marks (Maths, Science, English): ");
        scanf("%d %d %d", &temp->maths, &temp->science, &temp->english);
        printf("Enter New Department: ");
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
    printf("Topper: ID: %d, Name: %s, Total Marks: %d\n", topper->id, topper->name, maxMarks);
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

void sortStudents(int ascending) {
    for (Student* i = head; i; i = i->next) {
        for (Student* j = i->next; j; j = j->next) {
            int totalI = i->maths + i->science + i->english;
            int totalJ = j->maths + j->science + j->english;
            if ((ascending && totalI > totalJ) || (!ascending && totalI < totalJ)) {
                int tempId = i->id;
                char tempName[50], tempDept[50];
                int tempMaths = i->maths, tempScience = i->science, tempEnglish = i->english;
                strcpy(tempName, i->name);
                strcpy(tempDept, i->department);
                
                i->id = j->id;
                strcpy(i->name, j->name);
                strcpy(i->department, j->department);
                i->maths = j->maths;
                i->science = j->science;
                i->english = j->english;
                
                j->id = tempId;
                strcpy(j->name, tempName);
                strcpy(j->department, tempDept);
                j->maths = tempMaths;
                j->science = tempScience;
                j->english = tempEnglish;
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
