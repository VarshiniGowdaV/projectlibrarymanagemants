#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortbyauthor.h"

struct sortbyauthor* create_author_node(const char* author_name)
{
    struct sortbyauthor* new_node = (struct sortbyauthor*)malloc(sizeof(struct sortbyauthor));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(new_node->author_name, author_name, MAX_AUTHOR_NAME_LENGTH - 1);
    new_node->author_name[MAX_AUTHOR_NAME_LENGTH - 1] = '\0';
    new_node->next = NULL;
    return new_node;
}

void add_author(struct sortbyauthor** head, const char* author_name)
{
    struct sortbyauthor* new_node = create_author_node(author_name);
    new_node->next = *head;
    *head = new_node;
    printf("Author '%s' added successfully.\n", author_name);
}

void view_authors(struct sortbyauthor* head)
{
    if (!head)
    {
        printf("No authors available.\n");
        return;
    }
    printf("\nList of Authors:\n");
    while (head)
    {
        printf("- %s\n", head->author_name);
        head = head->next;
    }
}

void split_list_author(struct sortbyauthor* head, struct sortbyauthor** first_half, struct sortbyauthor** second_half)
{
    struct sortbyauthor* slow = head;
    struct sortbyauthor* fast = head->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    *first_half = head;
    *second_half = slow->next;
    slow->next = NULL;
}

struct sortbyauthor* merge_sorted_lists_author(struct sortbyauthor* left, struct sortbyauthor* right)
{
    if (!left) return right;
    if (!right) return left;

    struct sortbyauthor* result = NULL;
    if (strcmp(left->author_name, right->author_name) <= 0)
    {
        result = left;
        result->next = merge_sorted_lists_author(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge_sorted_lists_author(left, right->next);
    }
    return result;
}

void merge_sort_author(struct sortbyauthor** head)
{
    if (!*head || !(*head)->next)
    {
        return;
    }

    struct sortbyauthor *first_half, *second_half;
    split_list_author(*head, &first_half, &second_half);

    merge_sort_author(&first_half);
    merge_sort_author(&second_half);

    *head = merge_sorted_lists_author(first_half, second_half);
}
