#ifndef STAFF_H
#define STAFF_H

#define MAX_NAME_LENGTH 100
#define MAX_DEPT_LENGTH 50
#define MAX_POSITION_LENGTH 50

// Structure for staff members
struct staff {
    int id;
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPT_LENGTH];
    char position[MAX_POSITION_LENGTH];  // Added position field
    struct staff* next;
};

// Function prototypes
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position);
void delete_staff(struct staff** head, int id);
void update_staff(struct staff* head, int id);
struct staff* search_staff(struct staff* head, int id); // Corrected the return type
void view_staff(struct staff* head);

#endif // STAFF_H
