#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortbybookname.h"

struct sortbybookname* create_book_node(const char* book_name)
{
    struct sortbybookname* new_node = (struct sortbybookname*)malloc(sizeof(struct sortbybookname));
    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strncpy(new_node->book_name, book_name, MAX_BOOK_NAME_LENGTH - 1);
    new_node->book_name[MAX_BOOK_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;
    return new_node;
}

struct sortbybookname* add_book_name(struct sortbybookname* head, const char* book_name)
{
    struct sortbybookname* new_node = create_book_node(book_name);
    if (head == NULL)
    {
        printf("Book '%s' added successfully.\n", book_name);
        return new_node;
    }

    struct sortbybookname* temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    printf("Book '%s' added successfully.\n", book_name);
    return head;
}

void view_books(const struct sortbybookname* head)
{
    if (head == NULL)
    {
        printf("No books in the list.\n");
        return;
    }

    const struct sortbybookname* temp = head;
    printf("\nBooks in the list:\n");
    while (temp != NULL)
    {
        printf("- %s\n", temp->book_name);
        temp = temp->next;
    }
}

void split_list_book(struct sortbybookname* head, struct sortbybookname** first_half, struct sortbybookname** second_half) {
    struct sortbybookname* slow = head;
    struct sortbybookname* fast = head->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    *first_half = head;
    *second_half = slow->next;
    slow->next = NULL;
}

struct sortbybookname* merge_sorted_lists_book(struct sortbybookname* left, struct sortbybookname* right)
{
    if (!left) return right;
    if (!right) return left;

    struct sortbybookname* result = NULL;

    if (strcmp(left->book_name, right->book_name) <= 0)
    {
        result = left;
        result->next = merge_sorted_lists_book(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge_sorted_lists_book(left, right->next);
    }
    return result;
}

void merge_sort_books(struct sortbybookname** head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    struct sortbybookname *first_half, *second_half;
    split_list_book(*head, &first_half, &second_half);

    merge_sort_books(&first_half);
    merge_sort_books(&second_half);

    *head = merge_sorted_lists_book(first_half, second_half);
}
