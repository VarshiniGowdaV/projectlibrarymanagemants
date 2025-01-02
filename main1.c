#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "borrowedbook.h"
#include "returnedbook.h"
#include "staff.h"
#include "student.h"
#include "sortbyauthor.h"
#include "sortbybookname.h"
#include "filehanding.h"
struct book* book_head = NULL;
struct book* head = NULL;  // Head of the book list
struct borrowedbook* borrowed_books_head = NULL;
//struct returnedbook* returned_books_head = NULL;
 struct staff* staff_head = NULL;
 //struct student* student_head = NULL;
struct sortbyauthor* author_head = NULL;
struct sortbybookname* book_name_head = NULL;

int books_count = 0;
int students_count = 0;
int staff_count = 0;
int borrowed_count = 0;
int returned_count = 0;

typedef enum {
    // Book Management
    ADD_BOOK = 1,
    REMOVE_BOOK,
    UPDATE_BOOK,
    SEARCH_BOOK,
    VIEW_BOOKS,

    // Borrowed/Returned Book Management
    RECORD_BORROWED_BOOK,
    RECORD_RETURNED_BOOK,
    VIEW_RETURNED_BOOKS,

    // Author Management
    ADD_AUTHOR,
    VIEW_AUTHORS,
    SORT_AUTHORS,

    // Sorting Operations
    ADD_BOOK_NAME_SORTING,
    VIEW_BOOKS_BY_NAME,

    // User Management
    ADD_STUDENT,
    DELETE_STUDENT,
    UPDATE_STUDENT,
    SEARCH_STUDENT,
    VIEW_STUDENTS,
    ADD_STAFF,
    DELETE_STAFF,
    UPDATE_STAFF,
    SEARCH_STAFF,
    VIEW_STAFF,


    // Exit System
    EXIT
} MenuOption;

void display_menu() {
    printf("\nLibrary Management System\n");
    printf("1. Book Management:\n");
    printf("   1. Add Book\n");
    printf("   2. Remove Book\n");
    printf("   3. Update Book\n");
    printf("   4. Search Book\n");
    printf("   5. View Books\n");

    printf("2. Borrowed/Returned Book Management:\n");
    printf("   6. Record Borrowed Book\n");
    printf("   7. Record Returned Book\n");
    printf("   8. View Returned Books\n");

    printf("3. Author Management:\n");
    printf("   9. Add Author\n");
    printf("   10. View Authors\n");
    printf("   11. Sort Authors Alphabetically\n");

    printf("4. Sorting Operations:\n");
    printf("   12. Add Book Name for Sorting\n");
    printf("   13. View Books by Name\n");

    printf("5. User Management:\n");
    printf("   14. Add Student\n");
    printf("   15. delete student\n");
    printf("   16. update student\n");
    printf("   17. search student\n");
    printf("   18. View Students\n");
    printf("   19. Add Staff\n");
    printf("   20. delete staff\n");
    printf("   21. update staff\n");
    printf("   22. search staff\n");
    printf("   23. View Staff\n");

    printf("24. Exit\n");
    printf("Enter your choice: ");
}

int main_menu() {
    int choice;
    int login_status;
    int user_role;

    // Load data from files
    load_books_from_file(&books_count);
    load_students_from_file();
    load_staff_from_file();
    load_borrowed_books_from_file();
    load_returned_books_from_file();

    printf("Data loaded successfully!\n");
    printf("Books count: %d\n", books_count);
    printf("Students count: %d\n", students_count);
    printf("Staff count: %d\n", staff_count);
    printf("Borrowed books count: %d\n", borrowed_count);
    printf("Returned books count: %d\n", returned_count);

    // User login
    printf("Select your role to login:\n");
    printf("1. Admin\n2. Staff\n3. Student \n");
    printf("Enter your choice: ");
    scanf("%d", &user_role);

    if (user_role == 1) {
        login_status = authenticate_admin();
        if (!login_status) {
            printf("Authentication failed. Exiting...\n");
            return 0;
        }
    } else if (user_role == 2) {
        login_status = authenticate_staff();
        if (!login_status) {
            printf("Authentication failed. Exiting...\n");
            return 0;
        }
    } else if (user_role == 3) {
        login_status = authenticate_student();
        if (!login_status) {
            printf("Authentication failed. Exiting...\n");
            return 0;
        }
    } else {
        printf("Invalid choice. Exiting...\n");
        return 0;
    }

    do {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        getchar();

        switch ((MenuOption)choice) {
        case ADD_BOOK: {
            char book_name[100], author_name[100];
            int total_copies, available_copies;
            printf("Enter book name: ");
            scanf(" %[^\n]", book_name);
            printf("Enter author name: ");
            scanf(" %[^\n]", author_name);
            printf("Enter total copies: ");
            scanf("%d", &total_copies);
            printf("Enter available copies: ");
            scanf("%d", &available_copies);

            struct book* new_book = malloc(sizeof(struct book));
            if (new_book == NULL) {
                printf("Memory allocation failed!\n");
                break;
            }

            new_book->book_id = ++books_count;
            strcpy(new_book->name, book_name);
            strcpy(new_book->author, author_name);
            new_book->total_copies = total_copies;
            new_book->available_copies = available_copies;

            new_book->next = head;
            head = new_book;

            save_books_to_file(head);
            printf("Book added successfully.\n");
            break;
        }
        case UPDATE_BOOK:
            update_books();
            break;

        case REMOVE_BOOK: {
            int book_id;
            printf("Enter book ID to remove: ");
            scanf("%d", &book_id);
            remove_book(book_id);
            break;
        }
        case SEARCH_BOOK: {
            char book_name[100];
            printf("Enter the book name to search: ");
            scanf(" %[s]", book_name);
            struct book* found_book = search_book(book_name);
            if (found_book != NULL) {
                printf("Book found: %s by %s\n", found_book->name, found_book->author);
            } else {
                printf("Book not found.\n");
            }
            break;
        }
        case VIEW_BOOKS:
            display_books();
            break;
        case RECORD_BORROWED_BOOK:
            record_borrowed_book();
            break;
        case RECORD_RETURNED_BOOK:
            record_returned_book();
            break;
        case VIEW_RETURNED_BOOKS:
            view_returned_books();
            break;

        case ADD_AUTHOR: {
            char author_name[100];
            printf("Enter the author's name: ");
            scanf(" %[s]", author_name);
            add_author(&author_head, author_name);
            break;
        }

        case VIEW_AUTHORS:
            view_authors(author_head);
            break;

        case SORT_AUTHORS:
            sort_authors();
            break;

        case ADD_BOOK_NAME_SORTING:
            int sort_order = 1;
            add_book_name_sorting(book_name_head, sort_order);
            break;

        case VIEW_BOOKS_BY_NAME:
            view_books_by_name(book_name_head);
            break;

        case ADD_STUDENT: {
            char student_name[100], student_department[100];
            int student_id;
            printf("Enter student name: ");
            scanf(" %[s]", student_name);
            printf("Enter student ID: ");
            scanf("%d", &student_id);
            printf("Enter student department: ");
            scanf(" %[s]", student_department);
            student_head = add_student(student_head, student_name, student_id, student_department);
            break;
        }
        case DELETE_STUDENT:
            delete_student();
            break;

        case UPDATE_STUDENT:
            update_student();
            break;
        case SEARCH_STUDENT:
            search_student();
            break;

        case VIEW_STUDENTS:
            view_students(student_head);
            break;

        case ADD_STAFF: {
            char staff_name[100], staff_department[100], staff_position[100];
            int staff_id;

            printf("Enter staff name: ");
            scanf(" %99[^\n]", staff_name);  // Capture name with spaces

            printf("Enter staff ID: ");
            scanf("%d", &staff_id);

            printf("Enter staff department: ");
            scanf(" %99[^\n]", staff_department);  // Capture department with spaces

            printf("Enter staff position: ");
            scanf(" %99[^\n]", staff_position);  // Capture position with spaces

            staff_head = add_staff(staff_head, staff_name, staff_id, staff_department, staff_position);
            break;
        }

        case DELETE_STAFF: {
            int staff_id;
            printf("Enter staff ID to delete: ");
            scanf("%d", &staff_id);
            delete_staff(&staff_head, staff_id);
            break;
        }

        case UPDATE_STAFF: {
            int staff_id;
            printf("Enter staff ID to update: ");
            scanf("%d", &staff_id);
            update_staff(staff_head, staff_id);
            break;
        }

        case SEARCH_STAFF:
        {
            int staff_id;
            printf("Enter staff ID to search: ");
            scanf("%d", &staff_id);
            struct staff* found_staff = search_staff(staff_head, staff_id);
            if (found_staff != NULL) {
                printf("Staff found: %s, %s\n", found_staff->name, found_staff->position);
            } else {
                printf("Staff not found.\n");
            }
            break;
        }
        case VIEW_STAFF:
            view_staff(staff_head);
            break;

        case EXIT:
            // Save data before exiting
            save_books_to_file(head);
            save_students_to_file(student_head);
            save_staff_to_file(staff_head);
            save_borrowed_books_to_file(borrowed_books_head);
            save_returned_books_to_file(returned_books_head);
            printf("Exiting the system...\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (1);

    return 0;
}
