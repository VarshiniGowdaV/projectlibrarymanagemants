#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 100
#define MAX_DEPT_LENGTH 50

// Structure for student
struct student {
    char name[MAX_NAME_LENGTH];
    int id;
    char department[MAX_DEPT_LENGTH];
    struct student* next;
};
extern struct student* student_head;
struct student* create_student_node(const char* name, int id, const char* dept);
struct student* add_student(struct student* head, const char* name, int id, const char* department);
void delete_student();
void update_student();
void search_student();
// void remove_student_from_file(int student_id);
// void update_student_in_file(int student_id, const char* new_name, const char* new_dept);
void view_students(struct student* head);

#endif // STUDENT_H
