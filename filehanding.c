#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filehanding.h"
#include "book.h"
#include "student.h"
#include "staff.h"
#include "borrowedbook.h"
#include "returnedbook.h"

// Global variables
extern struct book* book_head;
extern struct student* student_head;
extern struct staff* staff_head;
extern struct borrowedbook* borrowed_books_head;
extern struct returnedbook* returned_books_head;

// Load books from file
void load_books_from_file(int* books_count) {
    FILE* file = fopen("books.txt", "r");
    if (!file) {
        perror("Error opening books file");
        return;
    }

    *books_count = 0;
    struct book* new_book;
    while (1) {
        new_book = malloc(sizeof(struct book));
        if (!new_book) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        if (fscanf(file, "%d,%99[^,],%99[^,],%d,%d\n",
                   &new_book->book_id, new_book->name, new_book->author,
                   &new_book->total_copies, &new_book->available_copies) != 5) {
            free(new_book);
            break;
        }

        new_book->next = book_head;
        book_head = new_book;
        (*books_count)++;
    }

    fclose(file);
}

// Save books to file
void save_books_to_file(struct book* head) {
    FILE* file = fopen("books.txt", "w");
    if (!file) {
        perror("Error opening books file for writing");
        return;
    }

    for (struct book* temp = head; temp; temp = temp->next) {
        fprintf(file, "%d,%s,%s,%d,%d\n",
                temp->book_id, temp->name, temp->author,
                temp->total_copies, temp->available_copies);
    }

    fclose(file);
}

// Load students from file
void load_students_from_file() {
    FILE* file = fopen("students.txt", "r");
    if (!file) {
        perror("Error opening students file");
        return;
    }

    while (1) {
        char name[100], department[50];
        int student_id;
        if (fscanf(file, "%99s %d %49s", name, &student_id, department) != 3) {
            break;
        }
        student_head = add_student(student_head, name, student_id, department);
    }

    fclose(file);
}

// Save students to file
void save_students_to_file(struct student* head) {
    FILE* file = fopen("students.txt", "w");
    if (!file) {
        perror("Error opening students file for writing");
        return;
    }

    for (struct student* current = head; current; current = current->next) {
        fprintf(file, "%s %d %s\n", current->name, current->student_id, current->department);
    }

    fclose(file);
}

// Load staff from file
void load_staff_from_file() {
    FILE* file = fopen("staff.txt", "r");
    if (!file) {
        perror("Error opening staff file");
        return;
    }

    while (1) {
        char staff_name[100], department[50], position[50];
        int staff_id;
        if (fscanf(file, "%99s %d %49s %49s", staff_name, &staff_id, department, position) != 4) {
            break;
        }
        staff_head = add_staff(staff_head, staff_name, staff_id, department, position);
    }

    fclose(file);
}

// Save staff to file
void save_staff_to_file(struct staff* head) {
    FILE* file = fopen("staff.txt", "w");
    if (!file) {
        perror("Error opening staff file for writing");
        return;
    }

    for (struct staff* current = head; current; current = current->next) {
        fprintf(file, "%s %d %s %s\n", current->staff_name, current->staff_id, current->department, current->position);
    }

    fclose(file);
}

// Load borrowed books from file
void load_borrowed_books_from_file() {
    FILE* file = fopen("borrowed_books.txt", "r");
    if (!file) {
        perror("Error opening borrowed books file");
        return;
    }

    while (1) {
        int student_id, book_id;
        if (fscanf(file, "%d %d", &student_id, &book_id) != 2) {
            break;
        }
        borrowed_books_head = add_borrowed_book(borrowed_books_head, student_id, book_id);
    }

    fclose(file);
}

// Save borrowed books to file
void save_borrowed_books_to_file(struct borrowedbook* head) {
    FILE* file = fopen("borrowed_books.txt", "w");
    if (!file) {
        perror("Error opening borrowed books file for writing");
        return;
    }

    for (struct borrowedbook* current = head; current; current = current->next) {
        fprintf(file, "%d %d\n", current->student_id, current->book_id);
    }

    fclose(file);
}

// Load returned books from file
void load_returned_books_from_file() {
    FILE* file = fopen("returned_books.txt", "r");
    if (!file) {
        perror("Error opening returned books file");
        return;
    }

    while (1) {
        int student_id, book_id;
        char returned_date[20];
        if (fscanf(file, "%d %d %19s", &student_id, &book_id, returned_date) != 3) {
            break;
        }
        returned_books_head = add_returned_book(returned_books_head, student_id, book_id, returned_date);
    }

    fclose(file);
}

// Save returned books to file
void save_returned_books_to_file(struct returnedbook* head) {
    FILE* file = fopen("returned_books.txt", "w");
    if (!file) {
        perror("Error opening returned books file for writing");
        return;
    }

    for (struct returnedbook* current = head; current; current = current->next) {
        fprintf(file, "%d %d %s\n", current->student_id, current->book_id, current->returned_date);
    }

    fclose(file);
}
