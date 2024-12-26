#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

struct user* create_user(const char* username, const char* password) {
    struct user* new_user = (struct user*)malloc(sizeof(struct user));
    if (!new_user) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strncpy(new_user->username, username, sizeof(new_user->username) - 1);
    new_user->username[sizeof(new_user->username) - 1] = '\0';
    strncpy(new_user->password, password, sizeof(new_user->password) - 1);
    new_user->password[sizeof(new_user->password) - 1] = '\0';
    new_user->next = NULL;
    return new_user;
}

struct user* add_user(struct user* head, const char* username, const char* password) {
    struct user* new_user = create_user(username, password);
    if (!new_user) {
        return head;
    }
    new_user->next = head;
    return new_user;
}

int validate_login(struct user* head, const char* username, const char* password) {
    struct user* current = head;
    while (current) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int admin_Login(struct user* admin_list) {
    char username[100];
    char password[100];

    printf("Admin Login:\n");
    printf("Username: ");
    scanf("%99s", username);
    printf("Password: ");
    scanf("%99s", password);

    if (validate_login(admin_list, username, password)) {
        printf("Admin login successful!\n");
        return 1;
    } else {
        printf("Invalid admin credentials.\n");
        return 0;
    }
}

int staff_Login(struct user* staff_list) {
    char username[100];
    char password[100];

    printf("Staff Login:\n");
    printf("Username: ");
    scanf("%99s", username);
    printf("Password: ");
    scanf("%99s", password);

    if (validate_login(staff_list, username, password)) {
        printf("Staff login successful!\n");
        return 1;
    } else {
        printf("Invalid staff credentials.\n");
        return 0;
    }
}

int student_Login(struct user* student_list) {
    char username[100];
    char password[100];

    printf("Student Login:\n");
    printf("Username: ");
    scanf("%99s", username);
    printf("Password: ");
    scanf("%99s", password);

    if (validate_login(student_list, username, password)) {
        printf("Student login successful!\n");
        return 1;
    } else {
        printf("Invalid student credentials.\n");
        return 0;
    }
}
