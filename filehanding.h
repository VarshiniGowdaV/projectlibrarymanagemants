#ifndef FILEHANDING_H
#define FILEHANDING_H

// Global variables for linked list heads
extern struct borrowedbook* borrowed_books_head;
extern struct returnedbook* returned_books_head;
extern struct staff* staff_head;
extern struct student* student_head;
extern struct sortbyauthor* author_head;
extern struct sortbybookname* book_name_head;

// External variables for counts
extern int books_count;
extern int students_count;
extern int staff_count;
extern int borrowed_count;
extern int returned_count;

// Function prototypes for file handling
void load_books_from_file(int* books_count);
void save_books_to_file(struct sortbybookname* head);
void load_students_from_file();
void save_students_to_file(struct student* head);
void load_staff_from_file();
void save_staff_to_file(struct staff* head);
void load_borrowed_books_from_file();
void save_borrowed_books_to_file(struct borrowedbook* head);
void load_returned_books_from_file();
void save_returned_books_to_file(struct returnedbook* head);

#endif
