#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "returnedbook.h"

struct returnedbook* head = NULL;

struct returnedbook* create_returned_book(const char* student_name, const char* usn, const char* dept, const char* date) {
    struct returnedbook* new_returned_book = (struct returnedbook*)malloc(sizeof(struct returnedbook));
    if (!new_returned_book)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(new_returned_book->student_name, student_name, sizeof(new_returned_book->student_name) - 1);
    new_returned_book->student_name[sizeof(new_returned_book->student_name) - 1] = '\0';
    strncpy(new_returned_book->usn, usn, sizeof(new_returned_book->usn) - 1);
    new_returned_book->usn[sizeof(new_returned_book->usn) - 1] = '\0';
    strncpy(new_returned_book->dept, dept, sizeof(new_returned_book->dept) - 1);
    new_returned_book->dept[sizeof(new_returned_book->dept) - 1] = '\0';
    strncpy(new_returned_book->date, date, sizeof(new_returned_book->date) - 1);
    new_returned_book->date[sizeof(new_returned_book->date) - 1] = '\0';
    new_returned_book->next = NULL;
    return new_returned_book;
}

int record_returned_book() {
    char student_name[50], usn[50], dept[50], date[20];

    printf("Enter student name: ");
    scanf(" %[^\n]", student_name);
    printf("Enter USN: ");
    scanf(" %[^\n]", usn);
    printf("Enter department: ");
    scanf(" %[^\n]", dept);
    printf("Enter return date (DD/MM/YYYY): ");
    scanf(" %[^\n]", date);

    struct returnedbook* new_returned_book = create_returned_book(student_name, usn, dept, date);
    if (!new_returned_book) {
        return 0;
    }

    new_returned_book->next = head;
    head = new_returned_book;

    printf("Returned book record added successfully!\n");
    return 1;
}

void print_returned_books() {
    struct returnedbook* current = head;

    if (!current) {
        printf("No returned books recorded.\n");
        return;
    }

    printf("\nReturned Books List:\n");
    while (current) {
        printf("Student Name: %s, USN: %s, Department: %s, Return Date: %s\n",
               current->student_name, current->usn, current->dept, current->date);
        current = current->next;
    }
}
void display_returned_books_menu() {
    printf("Returned Books Menu:\n");
    printf("1. View Returned Books\n");
    printf("2. Add Returned Book\n");
    printf("3. Remove Returned Book\n");
    printf("4. Return to Main Menu\n");
}
void manage_returned_books() {
    printf("Managing Returned Books...\n");
}


void save_returned_books_to_file() {
    FILE* file = fopen("returned_books_data.txt", "wb");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }

    struct returnedbook* current = head;
    while (current) {
        fwrite(current, sizeof(struct returnedbook), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Returned books saved successfully.\n");
}

void load_returned_books_from_file() {
    FILE* file = fopen("returned_books_data.txt", "rb");
    if (!file) {
        fprintf(stderr, "Error opening file for reading\n");
        return;
    }

    struct returnedbook temp;
    struct returnedbook* last = NULL;

    while (fread(&temp, sizeof(struct returnedbook), 1, file) == 1) {
        struct returnedbook* new_returned_book = create_returned_book(
            temp.student_name, temp.usn, temp.dept, temp.date);

        if (!head) {
            head = new_returned_book;
        } else {
            last->next = new_returned_book;
        }
        last = new_returned_book;
    }

    fclose(file);
    printf("Returned books loaded successfully.\n");
}
