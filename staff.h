#ifndef STAFF_H
#define STAFF_H

// Structure definition for staff
struct staff {
    int staff_id;
    char staff_name[100];
    char department[100];
    char position[100];
    struct staff* next;
};

// Declare the global head for the staff list (extern ensures this is only declared, not defined here)
extern struct staff* staff_head;

// Function declarations
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position);
void delete_staff(struct staff** head, int id);
void update_staff(struct staff* head, int id);
struct staff* search_staff(struct staff* head, int id);
void view_staff(struct staff* head);
void load_staff_from_file();
void save_staff_to_file(struct staff* staff_list_head);

#endif  // STAFF_H
