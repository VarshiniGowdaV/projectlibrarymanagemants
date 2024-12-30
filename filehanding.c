#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "borrowedbook.h"
#include "returnedbook.h"
#include "staff.h"
#include "student.h"
#include "sortbyauthor.h"
#include "sortbybookname.h"
#include "filehanding.h"

// Global variable declarations (These should be initialized elsewhere in your project)
extern struct borrowedbook* borrowed_books_head;
extern struct returnedbook* returned_books_head;
extern struct staff* staff_head;
extern struct student* student_head;
extern struct sortbyauthor* author_head;
extern struct sortbybookname* book_name_head;

// External variables for counts
extern int books_count;
extern int students_count;
extern int staff_count;
extern int borrowed_count;
extern int returned_count;

// Function to load books from file
void load_books_from_file(int* books_count) {
    FILE* file = fopen("books.txt", "r");
    if (!file) {
        printf("Failed to open books file.\n");
        return;
    }

    fscanf(file, "%d", books_count); // Read book count
    struct sortbybookname* temp = NULL;

    for (int i = 0; i < *books_count; i++) {
        char book_name[100];
        fscanf(file, "%s", book_name);
        temp = add_book_name(temp, book_name);
    }

    fclose(file);
}

// Function to save books to file
void save_books_to_file(struct sortbybookname* head) {
    FILE* file = fopen("books.txt", "w");
    if (!file) {
        printf("Failed to open books file for writing.\n");
        return;
    }

    struct sortbybookname* current = head;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    fprintf(file, "%d\n", count);
    current = head;
    while (current != NULL) {
        fprintf(file, "%s\n", current->book_name);
        current = current->next;
    }

    fclose(file);
}

// Function to load students from file
void load_students_from_file() {
    FILE* file = fopen("students.txt", "r");
    if (!file) {
        printf("Failed to open students file.\n");
        return;
    }

    while (!feof(file)) {
        char name[100];
        int id;
        char dept[50];
        if (fscanf(file, "%s %d %s", name, &id, dept) == 3) {
            student_head = add_student(student_head, name, id, dept);
        }
    }

    fclose(file);
}

// Function to save students to file
void save_students_to_file(struct student* head) {
    FILE* file = fopen("students.txt", "w");
    if (!file) {
        printf("Failed to open students file for writing.\n");
        return;
    }

    struct student* current = head;
    while (current != NULL) {
        fprintf(file, "%s %d %s\n", current->name, current->id, current->department);
        current = current->next;
    }

    fclose(file);
}

// Function to load staff from file
void load_staff_from_file() {
    FILE* file = fopen("staff.txt", "r");
    if (!file) {
        printf("Failed to open staff file.\n");
        return;
    }

    while (!feof(file)) {
        char name[100];
        int id;
        char dept[50];
        char position[50];
        if (fscanf(file, "%s %d %s %s", name, &id, dept, position) == 4) {
            staff_head = add_staff(staff_head, name, id, dept, position);
        }
    }

    fclose(file);
}

// Function to save staff to file
void save_staff_to_file(struct staff* head) {
    FILE* file = fopen("staff.txt", "w");
    if (!file) {
        printf("Failed to open staff file for writing.\n");
        return;
    }

    struct staff* current = head;
    while (current != NULL) {
        fprintf(file, "%s %d %s %s\n", current->name, current->id, current->department, current->position);
        current = current->next;
    }

    fclose(file);
}

// Function to load borrowed books from file
void load_borrowed_books_from_file() {
    FILE* file = fopen("borrowed_books.txt", "r");
    if (!file) {
        printf("Failed to open borrowed books file.\n");
        return;
    }

    while (!feof(file)) {
        int student_id;
        int book_id;
        if (fscanf(file, "%d %d", &student_id, &book_id) == 2) {
            borrowed_books_head = add_borrowed_book(borrowed_books_head, student_id, book_id);
        }
    }

    fclose(file);
}

// Function to save borrowed books to file
void save_borrowed_books_to_file(struct borrowedbook* head) {
    FILE* file = fopen("borrowed_books.txt", "w");
    if (!file) {
        printf("Failed to open borrowed books file for writing.\n");
        return;
    }

    struct borrowedbook* current = head;
    while (current != NULL) {
        fprintf(file, "%d %d\n", current->student_id, current->book_id);
        current = current->next;
    }

    fclose(file);
}

// Function to load returned books from file
void load_returned_books_from_file() {
    FILE* file = fopen("returned_books.txt", "r");
    if (!file) {
        printf("Failed to open returned books file.\n");
        return;
    }

    while (!feof(file)) {
        int student_id;
        int book_id;
        if (fscanf(file, "%d %d", &student_id, &book_id) == 2) {
            returned_books_head = add_returned_book(returned_books_head, student_id, book_id);
        }
    }

    fclose(file);
}

// Function to save returned books to file
void save_returned_books_to_file(struct returnedbook* head) {
    FILE* file = fopen("returned_books.txt", "w");
    if (!file) {
        printf("Failed to open returned books file for writing.\n");
        return;
    }

    struct returnedbook* current = head;
    while (current != NULL) {
        fprintf(file, "%d %d\n", current->student_id, current->book_id);
        current = current->next;
    }

    fclose(file);
}
