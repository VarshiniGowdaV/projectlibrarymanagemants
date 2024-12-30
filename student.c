#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Create a new student node
struct student* create_student_node(const char* name, int id, const char* dept) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_student->name, name);
    new_student->id = id;
    strcpy(new_student->department, dept);
    new_student->next = NULL;
    return new_student;
}

// Add a new student to the linked list
struct student* add_student(struct student* head, const char* name, int id, const char* dept) {
    struct student* new_student = create_student_node(name, id, dept);
    new_student->next = head;
    return new_student;
}

// View all students in the linked list
void view_students(struct student* head) {
    if (head == NULL) {
        printf("No students available.\n");
        return;
    }

    struct student* current = head;
    while (current != NULL) {
        printf("Name: %s, ID: %d, Department: %s\n", current->name, current->id, current->department);
        current = current->next;
    }
}
