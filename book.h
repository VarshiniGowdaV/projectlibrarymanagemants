#ifndef BOOK_H
#define BOOK_H

// Define the 'book' structure
struct book {
    int book_id;
    char name[100];
    char author[100];
     char title[100];
    int total_copies;
    int available_copies;
    struct book* next;
};

extern int books_count;
extern struct book* book_head;  // Use only one variable for the linked list head

// Function declarations
void add_book();
void update_books(struct book* head, int book_id, int new_available_copies);
void display_books(struct book* head);
void remove_book(struct book* head, int book_id);
struct book* search_book(const char* book_name);
struct book* search_book_by_id(int book_id);
void load_books_from_file(int* books_count);
//void save_books_to_file(void);
void save_books_to_file(struct book* book_head);

#endif
