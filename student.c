#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


struct student* create_student_node(const char* name, int id, const char* dept, const char* major) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (!new_student) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(new_student->name, name, sizeof(new_student->name) - 1);
    new_student->name[sizeof(new_student->name) - 1] = '\0';
    new_student->id = id;
    strncpy(new_student->dept, dept, sizeof(new_student->dept) - 1);
    new_student->dept[sizeof(new_student->dept) - 1] = '\0';
    strncpy(new_student->major, major, sizeof(new_student->major) - 1);
    new_student->major[sizeof(new_student->major) - 1] = '\0';
    new_student->next = NULL;
    return new_student;
}

struct student* add_student(struct student* head, const char* name, int id, const char* dept, const char* major) {
    struct student* new_student = create_student_node(name, id, dept, major);
    if (!new_student) {
        return head;
    }
    new_student->next = head;
    return new_student;
}

void view_students(struct student* head) {
    struct student* current = head;
    while (current) {
        printf("Name: %s, ID: %d, Department: %s, Major: %s\n",
               current->name, current->id, current->dept, current->major);
        current = current->next;
    }
}
void manage_students() {
    printf("Managing Students...\n");
}
void save_students_to_file(struct student* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }

    struct student* current = head;
    while (current) {
        fwrite(current, sizeof(struct student), 1, file);
        current = current->next;
    }

    fclose(file);
}

// Load the student list from a file
struct student* load_students_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file for reading\n");
        return NULL;
    }

    struct student* head = NULL;
    struct student* current = NULL;
    struct student temp;

    while (fread(&temp, sizeof(struct student), 1, file) == 1) {
        struct student* new_student = (struct student*)malloc(sizeof(struct student));
        if (!new_student) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            return head;
        }
        *new_student = temp;
        new_student->next = NULL;

        if (!head) {
            head = new_student;
        } else {
            current->next = new_student;
        }
        current = new_student;
    }

    fclose(file);
    return head;
}
