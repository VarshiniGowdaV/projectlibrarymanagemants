#ifndef STAFF_H
#define STAFF_H

struct staff {
    int id;
    char name[100];
    char department[100];
    char position[100]; // Add position field
    struct staff* next;
};

// Function prototypes
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position);
void view_staff(struct staff* head);

#endif
