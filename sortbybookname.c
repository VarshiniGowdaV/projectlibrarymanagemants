#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortbybookname.h"


struct sortbybookname* create_book_node(const char* book_name) {
    struct sortbybookname* new_node = (struct sortbybookname*)malloc(sizeof(struct sortbybookname));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(new_node->book_name, book_name, MAX_BOOK_NAME_LENGTH - 1);
    new_node->book_name[MAX_BOOK_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;
    return new_node;
}

struct sortbybookname* add_book_name(struct sortbybookname* head, const char* book_name) {
    struct sortbybookname* new_node = create_book_node(book_name);
    if (!new_node) return head;

    if (!head) {
        return new_node;
    }

    struct sortbybookname* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;

    return head;
}

void view_books(const struct sortbybookname* head) {
    if (!head) {
        printf("No books in the list.\n");
        return;
    }

    printf("List of Books:\n");
    const struct sortbybookname* current = head;
    while (current) {
        printf("%s\n", current->book_name);
        current = current->next;
    }
}
void display_book_name_menu() {
    printf("Book Name Management Menu:\n");
    printf("1. Add Book Name\n");
    printf("2. View Books\n");
    printf("3. Sort Books by Name\n");
    printf("4. Return to Main Menu\n");
}
void manage_books_by_name() {
    printf("Managing Books by Name...\n");
}

void split_books(struct sortbybookname* head, struct sortbybookname** first_half, struct sortbybookname** second_half) {
    struct sortbybookname* slow = head;
    struct sortbybookname* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *first_half = head;
    *second_half = slow->next;
    slow->next = NULL;
}

struct sortbybookname* merge_sorted_books(struct sortbybookname* left, struct sortbybookname* right) {
    if (!left) return right;
    if (!right) return left;

    struct sortbybookname* result = NULL;

    if (strcmp(left->book_name, right->book_name) <= 0) {
        result = left;
        result->next = merge_sorted_books(left->next, right);
    } else {
        result = right;
        result->next = merge_sorted_books(left, right->next);
    }

    return result;
}

void merge_sort_books(struct sortbybookname** head) {
    if (!*head || !(*head)->next) return;

    struct sortbybookname* first_half = NULL;
    struct sortbybookname* second_half = NULL;

    split_books(*head, &first_half, &second_half);

    merge_sort_books(&first_half);
    merge_sort_books(&second_half);

    *head = merge_sorted_books(first_half, second_half);
}
