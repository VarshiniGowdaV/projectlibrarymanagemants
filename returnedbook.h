#ifndef RETURNEDBOOK_H
#define RETURNEDBOOK_H

// Define the returned book structure
struct returnedbook {
    char book_name[100];
    char student_name[100];
    char usn[20];
    char dept[50];
    int book_id;
    int student_id;
    struct returnedbook* next;
};
extern struct returnedbook* returned_books_head;
// Function prototypes
struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id);
void record_returned_book();
void view_returned_books();
void print_returned_books();

#endif // RETURNEDBOOK_H
