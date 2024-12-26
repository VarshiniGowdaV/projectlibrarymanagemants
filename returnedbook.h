#ifndef RETURNEDBOOK_H
#define RETURNEDBOOK_H

struct returnedbook {
    char student_name[50];
    char usn[50];
    char dept[50];
    char date[20];
    struct returnedbook* next;
};

extern struct returnedbook* head;

int record_returned_book(void);
void print_returned_books(void);
void display_returned_books_menu();
void save_returned_books_to_file(void);
void load_returned_books_from_file(void);

#endif // RETURNEDBOOK_H
