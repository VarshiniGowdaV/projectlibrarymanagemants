#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "borrowedbook.h"

// Global head pointer for the borrowed books linked list
struct borrowedbook* borrowed_books_head = NULL;

// Create a new borrowed book node
struct borrowedbook* create_borrowed_book(const char* student_name, const char* usn, const char* book_name, const char* borrowed_date) {
    struct borrowedbook* new_borrowed_book = (struct borrowedbook*)malloc(sizeof(struct borrowedbook));
    if (!new_borrowed_book) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(new_borrowed_book->student_name, student_name, sizeof(new_borrowed_book->student_name) - 1);
    new_borrowed_book->student_name[sizeof(new_borrowed_book->student_name) - 1] = '\0';
    strncpy(new_borrowed_book->usn, usn, sizeof(new_borrowed_book->usn) - 1);
    new_borrowed_book->usn[sizeof(new_borrowed_book->usn) - 1] = '\0';
    strncpy(new_borrowed_book->book_name, book_name, sizeof(new_borrowed_book->book_name) - 1);
    new_borrowed_book->book_name[sizeof(new_borrowed_book->book_name) - 1] = '\0';
    strncpy(new_borrowed_book->borrowed_date, borrowed_date, sizeof(new_borrowed_book->borrowed_date) - 1);
    new_borrowed_book->borrowed_date[sizeof(new_borrowed_book->borrowed_date) - 1] = '\0';
    new_borrowed_book->next = NULL;
    return new_borrowed_book;
}
void display_borrowed_books_menu() {
    printf("Borrowed Books Menu:\n");
    printf("1. View Borrowed Books\n");
    printf("2. Add Borrowed Book\n");
    printf("3. Remove Borrowed Book\n");
    printf("4. Return to Main Menu\n");
}
void manage_borrowed_books() {
    printf("Managing Borrowed Books...\n");

}


int record_borrowed_book() {
    char student_name[50], usn[50], book_name[50], borrowed_date[20];

    printf("Enter student name: ");
    scanf(" %[^\n]", student_name);
    printf("Enter student USN: ");
    scanf(" %[^\n]", usn);
    printf("Enter book name: ");
    scanf(" %[^\n]", book_name);
    printf("Enter borrowed date (DD/MM/YYYY): ");
    scanf(" %[^\n]", borrowed_date);

    struct borrowedbook* new_borrowed_book = create_borrowed_book(student_name, usn, book_name, borrowed_date);
    if (!new_borrowed_book) {
        return 0;
    }

    new_borrowed_book->next = borrowed_books_head;
    borrowed_books_head = new_borrowed_book;

    printf("Borrowed book record added successfully!\n");
    return 1;
}

void save_borrowed_books_to_file() {
    FILE* file = fopen("borrowed_books_data.txt", "wb");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }

    struct borrowedbook* current = borrowed_books_head;
    while (current) {
        fwrite(current, sizeof(struct borrowedbook), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Borrowed books saved successfully.\n");
}

void load_borrowed_books_from_file() {
    FILE* file = fopen("borrowed_books_data.txt", "rb");
    if (!file) {
        fprintf(stderr, "Error opening file for reading\n");
        return;
    }

    struct borrowedbook temp;
    struct borrowedbook* last = NULL;

    while (fread(&temp, sizeof(struct borrowedbook), 1, file) == 1) {
        struct borrowedbook* new_borrowed_book = create_borrowed_book(
            temp.student_name, temp.usn, temp.book_name, temp.borrowed_date);

        if (!borrowed_books_head) {
            borrowed_books_head = new_borrowed_book;
        } else {
            last->next = new_borrowed_book;
        }
        last = new_borrowed_book;
    }

    fclose(file);
    printf("Borrowed books loaded successfully.\n");
}
