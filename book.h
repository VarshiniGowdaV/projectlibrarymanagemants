#ifndef BOOK_H
#define BOOK_H

// Define the 'book' structure
struct book {
    int book_id;
    char name[100];
    char author[100];
    int total_copies;
    int available_copies;
    struct book* next;
};

extern struct book* head;
extern struct book* book_head;

// Function declarations
void add_book();
void update_books();
void display_books(void);
void remove_book(int book_id);
struct book* search_book(const char* book_name);
struct book* search_book_by_id(int book_id);
void remove_book(int book_id);


#endif
