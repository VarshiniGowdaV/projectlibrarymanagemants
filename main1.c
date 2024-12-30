// main1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include headers for other files
#include "borrowedbook.h"
#include "returnedbook.h"
#include "staff.h"
#include "student.h"
#include "sortbyauthor.h"
#include "sortbybookname.h"
#include "filehanding.h"

// Define global variables here (only in this file)
struct borrowedbook* borrowed_books_head = NULL;
struct returnedbook* returned_books_head = NULL;
struct staff* staff_head = NULL;
struct student* student_head = NULL;
struct sortbyauthor* author_head = NULL;
struct sortbybookname* book_name_head = NULL;

int books_count = 0;
int students_count = 0;
int staff_count = 0;
int borrowed_count = 0;
int returned_count = 0;

// The rest of your code...


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
    VIEW_STUDENTS,
    ADD_STAFF,
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
    printf("   15. View Students\n");
    printf("   16. Add Staff\n");
    printf("   17. View Staff\n");

    printf("18. Exit\n");
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

    if (book_name_head == NULL) {
        printf(" Data loaded.\n");
    } else {
        printf("Data loaded successfully!\n");
        printf("Books count: %d\n", books_count);
        printf("Students count: %d\n", students_count);
        printf("Staff count: %d\n", staff_count);
        printf("Borrowed books count: %d\n", borrowed_count);
        printf("Returned books count: %d\n", returned_count);
    }

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
        case ADD_BOOK:
            add_book();
            break;
        case REMOVE_BOOK:
            remove_book();
            break;
        case UPDATE_BOOK:
            update_book();
            break;
        case SEARCH_BOOK:
            search_book();
            break;
        case VIEW_BOOKS:
            view_book_details();
            break;

        case RECORD_BORROWED_BOOK:
            record_borrowed_book();
            break;
        case RECORD_RETURNED_BOOK:
            record_returned_book();
            break;
        case VIEW_RETURNED_BOOKS:
            print_returned_books();
            break;

        case ADD_AUTHOR: {
            char author_name[100];
            printf("Enter author name: ");
            fgets(author_name, sizeof(author_name), stdin);
            author_name[strcspn(author_name, "\n")] = '\0';
            add_author(&author_head, author_name);
            break;
        }
        case VIEW_AUTHORS:
            view_authors(author_head);
            break;
        case SORT_AUTHORS:
            merge_sort_author(&author_head);
            printf("Authors sorted alphabetically.\n");
            break;

        case ADD_BOOK_NAME_SORTING: {
            char book_name[100];
            printf("Enter book name for sorting: ");
            fgets(book_name, sizeof(book_name), stdin);
            book_name[strcspn(book_name, "\n")] = '\0';
            book_name_head = add_book_name(book_name_head, book_name);
            break;
        }
        case VIEW_BOOKS_BY_NAME:
            merge_sort_books(&book_name_head);
            view_books(book_name_head);
            break;

        case ADD_STUDENT: {
            char student_name[100], student_dept[100];
            int student_id;
            printf("Enter student name: ");
            fgets(student_name, sizeof(student_name), stdin);
            student_name[strcspn(student_name, "\n")] = '\0';

            printf("Enter student ID: ");
            scanf("%d", &student_id);
            getchar();

            printf("Enter student department: ");
            fgets(student_dept, sizeof(student_dept), stdin);
            student_dept[strcspn(student_dept, "\n")] = '\0';

            student_head = add_student(student_head, student_name, student_id, student_dept);
            break;
        }
        case VIEW_STUDENTS:
            view_students(student_head);
            break;

        case ADD_STAFF: {
            char staff_name[100], staff_dept[100], staff_position[100];
            int staff_id;
            printf("Enter staff name: ");
            fgets(staff_name, sizeof(staff_name), stdin);
            staff_name[strcspn(staff_name, "\n")] = '\0';

            printf("Enter staff ID: ");
            scanf("%d", &staff_id);
            getchar();

            printf("Enter staff department: ");
            fgets(staff_dept, sizeof(staff_dept), stdin);
            staff_dept[strcspn(staff_dept, "\n")] = '\0';

            printf("Enter staff position: ");
            fgets(staff_position, sizeof(staff_position), stdin);
            staff_position[strcspn(staff_position, "\n")] = '\0';

            staff_head = add_staff(staff_head, staff_name, staff_id, staff_dept, staff_position);
            break;
        }
        case VIEW_STAFF:
            view_staff(staff_head);
            break;

        case EXIT:
            printf("Saving data and exiting the system...\n");
            save_books_to_file(book_name_head);
            save_students_to_file(student_head);
            save_staff_to_file(staff_head);
            save_borrowed_books_to_file(borrowed_books_head);
            save_returned_books_to_file(returned_books_head);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != EXIT);

    return 0;
}
