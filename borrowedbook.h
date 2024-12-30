#ifndef BORROWEDBOOK_H
#define BORROWEDBOOK_H

struct borrowedbook {
    char student_name[100];
    char book_name[100];
    char borrowed_date[11];
    int borrowed_by_student_id;
    int student_id;
    int book_id;
    struct borrowedbook* next;
};
extern struct borrowedbook* borrowed_books_head;
// Function prototypes
int record_borrowed_book(void);
void view_borrowed_books(void);
void load_borrowed_books_from_file(void);

#endif // BORROWEDBOOK_H
