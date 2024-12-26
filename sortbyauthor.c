#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortbyauthor.h"


struct sortbyauthor* create_author_node(const char* author_name) {
    struct sortbyauthor* new_node = (struct sortbyauthor*)malloc(sizeof(struct sortbyauthor));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(new_node->author_name, author_name, MAX_AUTHOR_NAME_LENGTH - 1);
    new_node->author_name[MAX_AUTHOR_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;
    return new_node;
}


void add_author(struct sortbyauthor** head, const char* author_name) {
    struct sortbyauthor* new_node = create_author_node(author_name);
    if (!new_node) return;

    if (!*head) {
        *head = new_node;
    } else {
        struct sortbyauthor* current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void view_authors(struct sortbyauthor* head) {
    if (!head) {
        printf("No authors in the list.\n");
        return;
    }

    printf("List of Authors:\n");
    struct sortbyauthor* current = head;
    while (current) {
        printf("%s\n", current->author_name);
        current = current->next;
    }
}
void display_author_menu() {
    printf("Author Management Menu:\n");
    printf("1. Add Author\n");
    printf("2. View Authors\n");
    printf("3. Sort Authors\n");
    printf("4. Return to Main Menu\n");
}
void manage_authors() {
    printf("Managing Authors...\n");
}
void split_list(struct sortbyauthor* head, struct sortbyauthor** first_half, struct sortbyauthor** second_half) {
    struct sortbyauthor* slow = head;
    struct sortbyauthor* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *first_half = head;
    *second_half = slow->next;
    slow->next = NULL;
}

struct sortbyauthor* merge_sorted_lists(struct sortbyauthor* left, struct sortbyauthor* right) {
    if (!left) return right;
    if (!right) return left;

    struct sortbyauthor* result = NULL;

    if (strcmp(left->author_name, right->author_name) <= 0) {
        result = left;
        result->next = merge_sorted_lists(left->next, right);
    } else {
        result = right;
        result->next = merge_sorted_lists(left, right->next);
    }

    return result;
}

void merge_sort(struct sortbyauthor** head) {
    if (!*head || !(*head)->next) return;

    struct sortbyauthor* first_half = NULL;
    struct sortbyauthor* second_half = NULL;

    split_list(*head, &first_half, &second_half);

    merge_sort(&first_half);
    merge_sort(&second_half);

    *head = merge_sorted_lists(first_half, second_half);
}
