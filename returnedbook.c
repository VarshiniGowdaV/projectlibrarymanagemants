#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "returnedbook.h"

struct returnedbook* returned_books_head = NULL;

struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id) {
    struct returnedbook* new_returned = (struct returnedbook*)malloc(sizeof(struct returnedbook));
    if (!new_returned) {
        printf("Memory allocation failed.\n");
        return head;
    }

    new_returned->student_id = student_id;
    new_returned->book_id = book_id;
    new_returned->next = NULL;

    if (head == NULL) {
        return new_returned;
    }

    struct returnedbook* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_returned;

    return head;
}

void record_returned_book() {
    struct returnedbook* new_returned = (struct returnedbook*)malloc(sizeof(struct returnedbook));
    if (!new_returned) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter book name: ");
    scanf(" %[s\n]", new_returned->book_name);

    printf("Enter student name: ");
    scanf(" %[s\n]", new_returned->student_name);

    printf("Enter student USN: ");
    scanf(" %[s\n]", new_returned->usn);

    printf("Enter department: ");
    scanf(" %[s\n]", new_returned->dept);

    printf("Enter book ID: ");
    scanf("%d", &new_returned->book_id);

    printf("Enter student ID: ");
    scanf("%d", &new_returned->student_id);

    new_returned->next = NULL;

    if (returned_books_head == NULL) {
        returned_books_head = new_returned;
    } else {
        struct returnedbook* temp = returned_books_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_returned;
    }

    printf("Returned book recorded successfully!\n");
}

void view_returned_books() {
    struct returnedbook* current = returned_books_head;
    if (current == NULL) {
        printf("No returned books available.\n");
        return;
    }

    printf("Returned Books:\n");
    while (current != NULL) {
        printf("Book ID: %d,"
               " Name: %s, Student ID: %d, Student Name: %s, USN: %s, Department: %s\n",
               current->book_id, current->book_name, current->student_id, current->student_name, current->usn, current->dept);
        current = current->next;
    }
}

void print_returned_books() {
    struct returnedbook* temp = returned_books_head;

    if (temp == NULL) {
        printf("No returned books to display.\n");
        return;
    }

    printf("Detailed Returned Books Information:\n");
    while (temp != NULL) {
        printf("Book Name: %s\n", temp->book_name);
        printf("Student Name: %s\n", temp->student_name);
        printf("USN: %s\n", temp->usn);
        printf("Department: %s\n", temp->dept);
        printf("Book ID: %d\n", temp->book_id);
        printf("Student ID: %d\n", temp->student_id);
        printf("-------------------------------\n");
        temp = temp->next;
    }
}
