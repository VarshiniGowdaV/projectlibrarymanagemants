#ifndef STUDENT_H
#define STUDENT_H

struct student {
        char name[100];
        int id;
        char department[50];
        struct student* next;
};

// Function prototypes
struct student* create_student_node(const char* name, int id, const char* dept);
struct student* add_student(struct student* head, const char* name, int id, const char* dept);

void view_students(struct student* head);

#endif
