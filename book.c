#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

// Define global variables
// struct book* head = NULL;
// struct book* book_head = NULL;

// File to store book data
#define BOOKS_FILE "books.txt"



// Function to add a book
void add_book() {
    struct book* new_book = (struct book*)malloc(sizeof(struct book));
    printf("Enter Book ID: ");
    scanf("%d", &new_book->book_id);
    getchar(); // Clear the newline character
    printf("Enter Book Name: ");
    fgets(new_book->name, sizeof(new_book->name), stdin);
    new_book->name[strcspn(new_book->name, "\n")] = '\0'; // Remove newline character
    printf("Enter Author Name: ");
    fgets(new_book->author, sizeof(new_book->author), stdin);
    new_book->author[strcspn(new_book->author, "\n")] = '\0'; // Remove newline character
    printf("Enter Total Copies: ");
    scanf("%d", &new_book->total_copies);
    new_book->available_copies = new_book->total_copies;

    new_book->next = head;
    head = new_book;

    save_books_to_file();
}

// Function to update a book's details
void update_books() {
    int book_id;
    printf("Enter the Book ID to update: ");
    scanf("%d", &book_id);
    getchar(); // Clear the newline character

    struct book* current = head;
    while (current) {
        if (current->book_id == book_id) {
            printf("Updating Book: %s by %s\n", current->name, current->author);
            printf("Enter New Total Copies: ");
            scanf("%d", &current->total_copies);
            getchar();
            printf("Enter New Available Copies: ");
            scanf("%d", &current->available_copies);
            getchar();

            save_books_to_file();
            printf("Book updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Book with ID %d not found.\n", book_id);
}

// Function to display all books
void display_books() {
    struct book* current = head;
    printf("\nBooks List:\n");
    printf("ID\tName\t\tAuthor\t\tTotal Copies\tAvailable Copies\n");
    printf("---------------------------------------------------------------\n");
    while (current) {
        printf("%d\t%s\t%s\t%d\t\t%d\n", current->book_id, current->name, current->author, current->total_copies, current->available_copies);
        current = current->next;
    }
}

// Function to remove a book
void remove_book(int book_id) {
    struct book* current = head;
    struct book* prev = NULL;

    while (current) {
        if (current->book_id == book_id) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            free(current);
            save_books_to_file();
            printf("Book with ID %d removed successfully.\n", book_id);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Book with ID %d not found.\n", book_id);
}

// Function to search for a book by name
struct book* search_book(const char* book_name) {
    struct book* current = head;
    while (current) {
        if (strcmp(current->name, book_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to search for a book by ID
struct book* search_book_by_id(int book_id) {
    struct book* current = head;
    while (current) {
        if (current->book_id == book_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
