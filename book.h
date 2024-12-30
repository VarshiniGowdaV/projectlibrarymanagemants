#ifndef BOOK_H
#define BOOK_H

struct book {
    char name[50];
    char author[50];
    int total_copies;
    int available_copies;
    struct book* next;
};

extern struct book* books_head;

void add_book();
void remove_book();
void update_book();
int search_book();
void view_book_details();


#endif // BOOK_H
