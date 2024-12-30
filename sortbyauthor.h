#ifndef SORTBYAUTHOR_H
#define SORTBYAUTHOR_H

#define MAX_AUTHOR_NAME_LENGTH 100
struct sortbyauthor {
    char author_name[MAX_AUTHOR_NAME_LENGTH];
    struct sortbyauthor* next;
};


struct sortbyauthor* create_author_node(const char* author_name);
void add_author(struct sortbyauthor** head, const char* author_name);
void view_authors(struct sortbyauthor* head);
void merge_sort(struct sortbyauthor** head);
void merge_sort_author(struct sortbyauthor **head);
struct sortbyauthor* merge_sorted_lists(struct sortbyauthor* left, struct sortbyauthor* right);
void split_list(struct sortbyauthor* head, struct sortbyauthor** first_half, struct sortbyauthor** second_half);

#endif // SORTBYAUTHOR_H
