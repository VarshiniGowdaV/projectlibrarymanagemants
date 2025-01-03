#ifndef FILEHANDING_H
#define FILEHANDING_H
#include "book.h"
#include "staff.h"
#include "student.h"
#include "borrowedbook.h"
#include "returnedbook.h"

extern struct book* head;
extern int students_count;
extern int staff_count;
extern struct returnedbook* returned_books_head;
extern struct borrowedbook* borrowed_books_head;
extern struct staff* staff_head;
extern struct student* student_head;

void load_books_from_file(int* books_count);
void save_books_to_file(struct book* book_head);
void load_students_from_file();
void save_students_to_file(struct student* student_list_head);
void load_staff_from_file();
void save_staff_to_file(struct staff* staff_list_head);
void load_borrowed_books_from_file();
void save_borrowed_books_to_file(struct borrowedbook* borrowed_list_head);
void load_returned_books_from_file();
void save_returned_books_to_file(struct returnedbook* returned_list_head);

#endif
