#ifndef SORTBYBOOKNAME_H
#define SORTBYBOOKNAME_H

#define MAX_BOOK_NAME_LENGTH 100

struct sortbybookname {
    char book_name[MAX_BOOK_NAME_LENGTH];
     char bookname[100];
    struct sortbybookname* next;
};
struct sortbybookname* create_book_node(const char* book_name);
struct sortbybookname* add_book_name(struct sortbybookname* head, const char* book_name);
void view_books(const struct sortbybookname* head);
void merge_sort_books(struct sortbybookname** head);

#endif // SORTBYBOOKNAME_H
