#ifndef STUDENT_H
#define STUDENT_H

struct student {
    char name[100];
    int id;
    char dept[100];
    char major[50];
    struct student* next;
};

// Function prototypes
struct student* create_student_node(const char* name, int id, const char* dept, const char* major);
struct student* add_student(struct student* head, const char* name, int id, const char* dept, const char* major);
void view_students(struct student* head);
void save_students_to_file(struct student* head, const char* filename);
struct student* load_students_from_file(const char* filename);

#endif
