#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

struct student* student_head = NULL;

// Function to create a new student node
struct student* create_student_node(const char* name, int id, const char* dept) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    strncpy(new_student->name, name, MAX_NAME_LENGTH);
    new_student->name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
    new_student->id = id;
    strncpy(new_student->department, dept, MAX_DEPT_LENGTH);
    new_student->department[MAX_DEPT_LENGTH - 1] = '\0'; // Ensure null-termination
    new_student->next = NULL;

    return new_student;
}

// Function to add a new student to the list
struct student* add_student(struct student* head, const char* name, int id, const char* department) {
    struct student* new_student = create_student_node(name, id, department);
    if (new_student == NULL) {
        return head; // Return head if memory allocation failed
    }

    if (head == NULL) {
        head = new_student;
    } else {
        struct student* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_student;
    }
    return head;
}

// Function to delete a student from the list
void delete_student() {
    int id;
    printf("Enter the student ID to delete: ");
    scanf("%d", &id);

    struct student* temp = student_head;
    struct student* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    if (prev == NULL) {
        student_head = temp->next; // Remove from the beginning
    } else {
        prev->next = temp->next; // Remove from the middle or end
    }

    free(temp);
    printf("Student with ID %d deleted.\n", id);
}

// Function to update student information
void update_student() {
    int id;
    printf("Enter the student ID to update: ");
    scanf("%d", &id);

    struct student* temp = student_head;

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    printf("Enter new name: ");
    scanf("%s", temp->name);

    printf("Enter new department: ");
    scanf("%s", temp->department);

    printf("Student with ID %d updated.\n", id);
}

// Function to search for a student by ID
void search_student() {
    int id;
    printf("Enter the student ID to search: ");
    scanf("%d", &id);

    struct student* temp = student_head;

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
    } else {
        printf("Student ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Department: %s\n", temp->department);
    }
}

// Function to display all students
void view_students(struct student* head) {
    if (head == NULL) {
        printf("No students available.\n");
        return;
    }

    struct student* temp = head;
    while (temp != NULL) {
        printf("Student ID: %d\n", temp->id);
        printf("Name: %s\n", temp->name);
        printf("Department: %s\n", temp->department);
        printf("---------------\n");
        temp = temp->next;
    }
}
