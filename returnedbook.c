#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "returnedbook.h"

// Define the global variable for the list of returned books (Only define it here)
//struct returnedbook* returned_books_head = NULL;

// Function to add a returned book to the list
struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id, const char* date) {
    struct returnedbook* new_returned_book = (struct returnedbook*)malloc(sizeof(struct returnedbook));
    if (!new_returned_book) {
        printf("Memory allocation failed.\n");
        return head;
    }
    new_returned_book->student_id = student_id;
    new_returned_book->book_id = book_id;
    strcpy(new_returned_book->returned_date, date);
    new_returned_book->next = head;
    return new_returned_book;
}

// Function to record a returned book (adds to the list)
void record_returned_book() {
    int student_id, book_id;
    char returned_date[MAX_DATE_LENGTH];

    // Collect input data
    printf("Enter student ID: ");
    scanf("%d", &student_id);
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    printf("Enter return date (YYYY-MM-DD): ");
    scanf("%s", returned_date);

    // Add the returned book to the list
    returned_books_head = add_returned_book(returned_books_head, student_id, book_id, returned_date);
    printf("Returned book recorded successfully.\n");
}

// Function to view all returned books
void view_returned_books() {
    struct returnedbook* temp = returned_books_head;

    if (!temp) {
        printf("No returned books available.\n");
        return;
    }

    printf("Returned Books Records:\n");
    while (temp) {
        printf("Returned ID: %d, Student ID: %d, Book ID: %d, Return Date: %s\n", temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        temp = temp->next;
    }
}

// Function to print all returned books in a nice format
void print_returned_books() {
    struct returnedbook* temp = returned_books_head;

    if (!temp) {
        printf("No returned books to print.\n");
        return;
    }

    printf("Returned Books:\n");
    while (temp) {
        printf("Returned ID: %d, Student ID: %d, Book ID: %d, Return Date: %s\n", temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        temp = temp->next;
    }
}
