// borrowedbook.c (or any other .c file)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include necessary headers
#include "borrowedbook.h"
#include "returnedbook.h"
#include "staff.h"
#include "student.h"
#include "sortbyauthor.h"
#include "sortbybookname.h"
#include "filehanding.h"

// Declare global variables using extern
extern struct borrowedbook* borrowed_books_head;
extern struct returnedbook* returned_books_head;
extern struct staff* staff_head;
extern struct student* student_head;
extern struct sortbyauthor* author_head;
extern struct sortbybookname* book_name_head;

extern int books_count;
extern int students_count;
extern int staff_count;
extern int borrowed_count;
extern int returned_count;


struct borrowedbook* add_borrowed_book(struct borrowedbook* head, int student_id, int book_id) {
    struct borrowedbook* new_node = (struct borrowedbook*)malloc(sizeof(struct borrowedbook));
    if (!new_node) {
        printf("Memory allocation failed for borrowed book.\n");
        return head;
    }

    new_node->student_id = student_id;
    new_node->book_id = book_id;
    new_node->next = head;
    head = new_node;
    return head;
}
// Function to record a borrowed book
int record_borrowed_book(void) {
    // Allocate memory for the new borrowed book record
    struct borrowedbook* new_borrowed_book = (struct borrowedbook*)malloc(sizeof(struct borrowedbook));
    if (new_borrowed_book == NULL) {
        printf("Memory allocation failed.\n");
        return -1; // Return error code
    }

    // Prompt user for details about the borrowed book
    printf("Enter student name: ");
    scanf(" %[^\n]", new_borrowed_book->student_name);

    printf("Enter book name: ");
    scanf(" %[^\n]", new_borrowed_book->book_name);

    printf("Enter borrowed date (YYYY-MM-DD): ");
    scanf(" %[^\n]", new_borrowed_book->borrowed_date);

    printf("Enter student ID: ");
    scanf("%d", &new_borrowed_book->borrowed_by_student_id);

    // Initialize the next pointer
    new_borrowed_book->next = NULL;

    // Add the new record to the linked list
    if (borrowed_books_head == NULL) {
        borrowed_books_head = new_borrowed_book;
    } else {
        struct borrowedbook* current = borrowed_books_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_borrowed_book;
    }

    printf("Borrowed book recorded successfully.\n");
    return 0; // Return success code
}

// Optional: Function to view all borrowed books
void view_borrowed_books(void) {
    if (borrowed_books_head == NULL) {
        printf("No borrowed books recorded.\n");
        return;
    }

    printf("Borrowed Books:\n");
    struct borrowedbook* current = borrowed_books_head;
    while (current != NULL) {
        printf("Student Name: %s\n", current->student_name);
        printf("Book Name: %s\n", current->book_name);
        printf("Borrowed Date: %s\n", current->borrowed_date);
        printf("Student ID: %d\n", current->borrowed_by_student_id);
        printf("\n");
        current = current->next;
    }
}

