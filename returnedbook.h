#ifndef RETURNEDBOOK_H
#define RETURNEDBOOK_H

struct returnedbook {
    char book_name[100];
    char student_name[50];
    char usn[50];
    char dept[50];
    int date[20];
    int returned_by_student_id;
    int student_id;
    int book_id;
    struct returnedbook* next;
};

extern struct returnedbook* head;

int record_returned_book();
void print_returned_books();

#endif // RETURNEDBOOK_H
