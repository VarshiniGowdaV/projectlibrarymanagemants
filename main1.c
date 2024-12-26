#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ADMIN_LOGIN = 1,
    STAFF_LOGIN,
    STUDENT_LOGIN,
    ADD_ADMIN_USER,
    ADD_STAFF_USER,
    ADD_STUDENT_USER,
    MANAGE_BOOKS,
    MANAGE_BORROWED_BOOKS,
    MANAGE_RETURNED_BOOKS,
    MANAGE_AUTHORS,
    MANAGE_BOOKS_BY_NAME,
    MANAGE_STAFF,
    MANAGE_STUDENTS,
    EXIT_PROGRAM
} MainMenuOption;

struct user {
    char username[100];
    char password[100];
    struct user* next;
};


struct user* add_user(struct user* list, const char* username, const char* password);
int admin_Login(struct user* admin_list);
int staff_Login(struct user* staff_list);
int student_Login(struct user* student_list);
void manage_books();
void manage_borrowed_books();
void manage_returned_books();
void manage_authors();
void manage_books_by_name();
void manage_staff();
void manage_students();

void display_main_menu() {
    printf("\nMain Menu\n");
    printf("1. Admin Login\n");
    printf("2. Staff Login\n");
    printf("3. Student Login\n");
    printf("4. Add Admin User\n");
    printf("5. Add Staff User\n");
    printf("6. Add Student User\n");
    printf("7. Manage Books\n");
    printf("8. Manage Borrowed Books\n");
    printf("9. Manage Returned Books\n");
    printf("10. Manage Authors\n");
    printf("11. Manage Books by Name\n");
    printf("12. Manage Staff\n");
    printf("13. Manage Students\n");
    printf("14. Exit\n");
}

int main_menu() {
    struct user* admin_list = NULL;
    struct user* staff_list = NULL;
    struct user* student_list = NULL;
    int choice;
    int login_status;

    admin_list = add_user(admin_list, "admin", "admin123");
    staff_list = add_user(staff_list, "staff", "staff123");
    student_list = add_user(student_list, "student", "student123");

    while (1) {
        display_main_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case ADMIN_LOGIN:
            login_status = admin_Login(admin_list);
            if (login_status) {
                printf("You are logged in as Admin.\n");
            }
            break;

        case STAFF_LOGIN:
            login_status = staff_Login(staff_list);
            if (login_status) {
                printf("You are logged in as Staff.\n");
            }
            break;

        case STUDENT_LOGIN:
            login_status = student_Login(student_list);
            if (login_status) {
                printf("You are logged in as Student.\n");
            }
            break;

        case ADD_ADMIN_USER:
        {
            char username[100], password[100];
            printf("Enter new Admin username: ");
            scanf("%s", username);
            printf("Enter new Admin password: ");
            scanf("%s", password);
            admin_list = add_user(admin_list, username, password);
            printf("Admin user added successfully.\n");
        }
        break;

        case ADD_STAFF_USER:
        {
            char username[100], password[100];
            printf("Enter new Staff username: ");
            scanf("%s", username);
            printf("Enter new Staff password: ");
            scanf("%s", password);
            staff_list = add_user(staff_list, username, password);
            printf("Staff user added successfully.\n");
        }
        break;

        case ADD_STUDENT_USER:
        {
            char username[100], password[100];
            printf("Enter new Student username: ");
            scanf("%s", username);
            printf("Enter new Student password: ");
            scanf("%s", password);
            student_list = add_user(student_list, username, password);
            printf("Student user added successfully.\n");
        }
        break;

        case MANAGE_BOOKS:
            manage_books();
            break;

        case MANAGE_BORROWED_BOOKS:
            manage_borrowed_books();
            break;

        case MANAGE_RETURNED_BOOKS:
            manage_returned_books();
            break;

        case MANAGE_AUTHORS:
            manage_authors();
            break;

        case MANAGE_BOOKS_BY_NAME:
            manage_books_by_name();
            break;

        case MANAGE_STAFF:
            manage_staff();
            break;

        case MANAGE_STUDENTS:
            manage_students();
            break;

        case EXIT_PROGRAM:
            printf("Exiting the program...\n");
            free(admin_list);
            free(staff_list);
            free(student_list);
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
