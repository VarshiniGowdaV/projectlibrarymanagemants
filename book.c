#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "filehanding.h"

#define BOOKS_FILE "books.txt"
extern struct book* head;
extern void save_books_to_file(struct book* book_head);

// Function to add a book
void add_book() {
    struct book* new_book = (struct book*)malloc(sizeof(struct book));
    if (new_book == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

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

    save_books_to_file(head);  // Save the updated book list to the file
    printf("Book added successfully.\n");
}

// Function to update a book's details
void update_book_record(int book_id, const char* new_name, const char* new_author, int total_copies, int available_copies) {
    FILE* file = fopen("books.txt", "r+");
    if (!file) {
        perror("Error opening books file");
        return;
    }

    struct book temp_book;
    long pos;
    int found = 0;
    while (fscanf(file, "%d,%99[^,],%99[^,],%d,%d\n",
                  &temp_book.book_id, temp_book.name, temp_book.author,
                  &temp_book.total_copies, &temp_book.available_copies) == 10000) {
        pos = ftell(file);
        if (temp_book.book_id == book_id) {
            found = 1;
            break;
        }
    }

    if (found) {
        fseek(file, pos - sizeof(temp_book), SEEK_SET); // Move to the position of the record
        fprintf(file, "%d,%s,%s,%d,%d\n", book_id, new_name, new_author, total_copies, available_copies);
        printf("Updated Book Record:\n");
        printf("ID: %d, Name: %s, Author: %s, Total Copies: %d, Available Copies: %d\n",
               book_id, new_name, new_author, total_copies, available_copies);
    } else {
        printf("Book ID %d not found.\n", book_id);
    }

    fclose(file);
}

// Function to remove a book
void remove_book(struct book* head, int book_id) {
    struct book* current = head;
    struct book* prev = NULL;

    // Display the books before removal
    printf("Current Book List:\n");
    display_books(head);

    while (current) {
        if (current->book_id == book_id) {
            // Book found, remove it from the linked list
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;  // Update head if it's the first book
            }
            free(current);  // Free the memory
            save_books_to_file(head);  // Save the updated list to the file
            printf("Book with ID %d removed successfully.\n", book_id);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Book with ID %d not found.\n", book_id);
}

// Function to display all books
void display_books(struct book* head) {
    struct book* current = head;
    if (!current) {
        printf("No books available.\n");
        return;
    }

    while (current) {
        printf("ID: %d, Name: %s, Author: %s, Total Copies: %d, Available Copies: %d\n",
               current->book_id, current->name, current->author,
               current->total_copies, current->available_copies);
        current = current->next;
    }
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
