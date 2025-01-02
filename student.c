#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

struct student* create_student_node(const char* name, int id, const char* dept) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(new_student->name, name, MAX_NAME_LENGTH);
    new_student->name[MAX_NAME_LENGTH - 1] = '\0';
    new_student->id = id;
    strncpy(new_student->department, dept, MAX_DEPT_LENGTH);
    new_student->department[MAX_DEPT_LENGTH - 1] = '\0';
    new_student->next = NULL;
    return new_student;
}

struct student* add_student(struct student* head, const char* name, int id, const char* dept) {
    struct student* new_student = create_student_node(name, id, dept);
    new_student->next = head;
    return new_student;
    printf("Enter student name:");
    scanf("%d",new_student->name);
    getchar();
    printf("Enter student id:");
    scanf("%d",new_student->id);
    getchar();
    printf("Enter student department:");
    scanf("%d",new_student->department);
    getchar();
}
void remove_student_from_file(int student_id) {
    FILE* file = fopen("students.txt", "r");
    if (!file) {
        printf("Failed to open students file.\n");
        return;
    }
    struct student* temp_head = NULL;
    char name[MAX_NAME_LENGTH];
    int id;
    char dept[MAX_DEPT_LENGTH];

    while (fscanf(file, "%s %d %s", name, &id, dept) == 3) {
        if (id != student_id) {  // Skip the student to remove
            temp_head = add_student(temp_head, name, id, dept);
        }
    }

    fclose(file);
    file = fopen("students.txt", "w");
    if (!file) {
        printf("Failed to open students file for writing.\n");
        return;
    }

    struct student* temp = temp_head;
    while (temp != NULL) {
        fprintf(file, "%s %d %s\n", temp->name, temp->id, temp->department);
        temp = temp->next;
    }

    fclose(file);
    printf("Student removed successfully!\n");
}
void update_student_in_file(int student_id, const char* new_name, const char* new_dept) {
    FILE* file = fopen("students.txt", "r");
    if (!file) {
        printf("Failed to open students file.\n");
        return;
    }
    struct student* temp_head = NULL;
    char name[MAX_NAME_LENGTH];
    int id;
    char dept[MAX_DEPT_LENGTH];

    while (fscanf(file, "%s %d %s", name, &id, dept) == 3) {
        if (id == student_id) {
            temp_head = add_student(temp_head, new_name, student_id, new_dept);
        } else {
            temp_head = add_student(temp_head, name, id, dept);
        }
    }

    fclose(file);
    file = fopen("students.txt", "w");
    if (!file) {
        printf("Failed to open students file for writing.\n");
        return;
    }

    struct student* temp = temp_head;
    while (temp != NULL) {
        fprintf(file, "%s %d %s\n", temp->name, temp->id, temp->department);
        temp = temp->next;
    }

    fclose(file);
    printf("Student updated successfully!\n");
}

void view_students(struct student* head) {
    if (head == NULL) {
        printf("No students available.\n");
        return;
    }

    struct student* current = head;
    while (current != NULL) {
        printf("Name: %s, ID: %d, Department: %s\n", current->name, current->id, current->department);
        current = current->next;
        printf("-------------------\n");
    }
}
