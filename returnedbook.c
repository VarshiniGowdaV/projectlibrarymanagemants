#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "returnedbook.h"

struct returnedbook* head = NULL;

struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id) {
    struct returnedbook* new_node = (struct returnedbook*)malloc(sizeof(struct returnedbook));
    if (!new_node) {
        printf("Memory allocation failed for returned book.\n");
        return head;
    }

    new_node->student_id = student_id;
    new_node->book_id = book_id;
    new_node->next = head;
    head = new_node;
    return head;
}
int record_returned_book()
{
    struct returnedbook* new_book = (struct returnedbook*)malloc(sizeof(struct returnedbook));
    if (new_book == NULL)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }

    printf("Enter student name: ");
    fgets(new_book->student_name, 50, stdin);
    new_book->student_name[strcspn(new_book->student_name, "\n")] = '\0';

    printf("Enter USN: ");
    fgets(new_book->usn, 50, stdin);
    new_book->usn[strcspn(new_book->usn, "\n")] = '\0';

    printf("Enter department: ");
    fgets(new_book->dept, 50, stdin);
    new_book->dept[strcspn(new_book->dept, "\n")] = '\0';

    printf("Enter date:");
    fgets(new_book->date,20,stdin);
    new_book->date[strcspn(new_book->date, "\n")] = '\0';

    new_book->next = head;
    head = new_book;

    printf("Book returned successfully!\n");

    return 0;
}

void print_returned_books()
{
    struct returnedbook* current = head;

    if (current == NULL)
    {
        printf("No returned books recorded.\n");
        return;
    }

    printf("List of returned books:\n");
    while (current != NULL)
    {
        printf("Student Name: %s\n", current->student_name);
        printf("USN: %s\n", current->usn);
        printf("Department: %s\n\n", current->dept);
        printf("Date:%s\n",current->date);
        current = current->next;
    }
}
