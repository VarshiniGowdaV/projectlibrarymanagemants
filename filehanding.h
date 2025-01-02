// filehanding.h
#ifndef FILEHANDING_H
#define FILEHANDING_H

#include "book.h"
#include "student.h"
#include "staff.h"
#include "borrowedbook.h"
#include "returnedbook.h"

void load_books_from_file(int* books_count);
void save_books_to_file(struct book* head);
void load_students_from_file();
void save_students_to_file(struct student* head);
void load_staff_from_file();
void save_staff_to_file(struct staff* head);
void load_borrowed_books_from_file();
void save_borrowed_books_to_file(struct borrowedbook* head);
void load_returned_books_from_file();
void save_returned_books_to_file(struct returnedbook* head);

#endif
