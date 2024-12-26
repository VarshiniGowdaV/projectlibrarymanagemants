#ifndef ADMIN_H
#define ADMIN_H

struct user {
    char username[100];
    char password[100];
    struct user* next;
};

struct user* create_user(const char* username, const char* password);
struct user* add_user(struct user* head, const char* username, const char* password);
int validate_login(struct user* head, const char* username, const char* password);
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

#endif
