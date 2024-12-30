#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
struct book* books_head = NULL;
void add_book()
{
    struct book* new_book = (struct book*)malloc(sizeof(struct book));

    printf("Enter book name: ");
    scanf("%s", new_book->name);

    printf("Enter author name: ");
    scanf("%s", new_book->author);

    printf("Enter total copies: ");
    scanf("%d", &new_book->total_copies);

    new_book->available_copies = new_book->total_copies;
    new_book->next = NULL;
    if (books_head == NULL)
    {
        books_head = new_book;
    }
    else
    {
        struct book* temp = books_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_book;
    }

    printf("Book added successfully!\n");
}
void remove_book()
{
    if (books_head == NULL)
    {
        printf("No books to remove.\n");
        return;
    }

    char book_name[50];
    printf("Enter book name to remove: ");
    scanf("%s", book_name);

    struct book* temp = books_head;
    struct book* prev = NULL;
    if (strcmp(temp->name, book_name) == 0)
    {
        books_head = temp->next;
        free(temp);
        printf("Book removed successfully!\n");
        return;
    }
    while (temp != NULL && strcmp(temp->name, book_name) != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Book not found.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Book removed successfully!\n");
}
void update_book()
{
    char book_name[50];
    printf("Enter book name to update: ");
    scanf("%s", book_name);

    struct book* temp = books_head;

    while (temp != NULL && strcmp(temp->name, book_name) != 0)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Book not found.\n");
        return;
    }

    printf("Enter new book name: ");
    scanf("%s", temp->name);

    printf("Enter new author name: ");
    scanf("%s", temp->author);

    printf("Enter new total copies: ");
    scanf("%d", &temp->total_copies);

    temp->available_copies = temp->total_copies;

    printf("Book details updated successfully!\n");
}
int search_book()
{
    char book_name[50];
    printf("Enter book name to search: ");
    scanf("%s", book_name);

    struct book* temp = books_head;
    int position = 1;

    while (temp != NULL)
    {
        if (strcmp(temp->name, book_name) == 0)
        {
            printf("Book found at position %d.\n", position);
            return position;
        }
        temp = temp->next;
        position++;
    }

    printf("Book not found.\n");
    return -1;
}
void view_book_details()
{
    if (books_head == NULL)
    {
        printf("No books available.\n");
        return;
    }

    struct book* temp = books_head;
    while (temp != NULL)
    {
        printf("Book Name: %s\n", temp->name);
        printf("Author: %s\n", temp->author);
        printf("Total Copies: %d\n", temp->total_copies);
        printf("Available Copies: %d\n\n", temp->available_copies);
        temp = temp->next;
    }
}
