#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

struct book* books_head = NULL;

struct book* create_book(const char* name, const char* author, int total_copies) {
    struct book* new_book = (struct book*)malloc(sizeof(struct book));
    if (!new_book) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(new_book->name, name, sizeof(new_book->name) - 1);
    new_book->name[sizeof(new_book->name) - 1] = '\0';
    strncpy(new_book->author, author, sizeof(new_book->author) - 1);
    new_book->author[sizeof(new_book->author) - 1] = '\0';
    new_book->total_copies = total_copies;
    new_book->available_copies = total_copies;
    new_book->next = NULL;
    return new_book;
}

void add_book() {
    char name[50], author[50];
    int total_copies;

    printf("Enter book name: ");
    scanf(" %[^\n]", name);
    printf("Enter author name: ");
    scanf(" %[^\n]", author);
    printf("Enter total copies: ");
    scanf("%d", &total_copies);

    struct book* new_book = create_book(name, author, total_copies);
    if (!new_book) {
        return;
    }

    new_book->next = books_head;
    books_head = new_book;
    printf("Book added successfully!\n");
}

void remove_book() {
    char name[50];
    printf("Enter the name of the book to remove: ");
    scanf(" %[^\n]", name);

    struct book* current = books_head;
    struct book* previous = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                books_head = current->next;
            }
            free(current);
            printf("Book removed successfully!\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Book not found.\n");
}

void update_book() {
    char name[50];
    printf("Enter the name of the book to update: ");
    scanf(" %[^\n]", name);

    struct book* current = books_head;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Enter new total copies: ");
            scanf("%d", &current->total_copies);
            current->available_copies = current->total_copies; // Reset available copies
            printf("Book updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Book not found.\n");
}


int search_book() {
    char name[50];
    printf("Enter the name of the book to search: ");
    scanf(" %[^\n]", name);

    struct book* current = books_head;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Book found: %s by %s\n", current->name, current->author);
            return 1;
        }
        current = current->next;
    }
    printf("Book not found.\n");
    return 0;
}

void view_book_details() {
    struct book* current = books_head;

    if (!current) {
        printf("No books in the library.\n");
        return;
    }

    while (current) {
        printf("Name: %s, Author: %s, Total Copies: %d, Available Copies: %d\n",
               current->name, current->author, current->total_copies, current->available_copies);
        current = current->next;
    }
}
void display_book_menu() {
    printf("Book Management Menu:\n");
    printf("1. Add Book\n");
    printf("2. Remove Book\n");
    printf("3. Update Book\n");
    printf("4. Search Book\n");
    printf("5. View All Books\n");
    printf("6. Save Books to File\n");
    printf("7. Load Books from File\n");
    printf("8. Return to Main Menu\n");
}
void manage_books() {
    printf("Managing Books...\n");
}

void save_books_to_file() {
    FILE* file = fopen("books_data.txt", "wb");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }

    struct book* current = books_head;
    while (current) {
        fwrite(current, sizeof(struct book), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Books saved successfully.\n");
}

void load_books_from_file() {
    FILE* file = fopen("books_data.txt", "rb");
    if (!file) {
        fprintf(stderr, "Error opening file for reading\n");
        return;
    }

    struct book temp;
    struct book* last = NULL;

    while (fread(&temp, sizeof(struct book), 1, file) == 1) {
        struct book* new_book = create_book(temp.name, temp.author, temp.total_copies);
        new_book->available_copies = temp.available_copies;

        if (!books_head) {
            books_head = new_book;
        } else {
            last->next = new_book;
        }
        last = new_book;
    }

    fclose(file);
    printf("Books loaded successfully.\n");
}
