#ifndef STAFF_H
#define STAFF_H

struct staff {
    char name[100];
    int id;
    char department[100];
    char position[50];
    struct staff* next;
};

// Function prototypes
struct staff* add_staff(struct staff* head, const char* name, int id, const char* dept, const char* position);
void view_staff(struct staff* head);

void save_staff_to_file(struct staff* head, const char* filename);
struct staff* load_staff_from_file(const char* filename);

#endif
