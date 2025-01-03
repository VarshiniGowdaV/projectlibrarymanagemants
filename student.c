#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//int students_count = 0;

// Create a new student node
struct student* create_student_node(const char* name, int student_id, const char* dept) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    new_student->student_id = student_id;   // Use student_id here
    strncpy(new_student->name, name, MAX_NAME_LENGTH);
    strncpy(new_student->department, dept, MAX_DEPT_LENGTH);
    new_student->next = NULL;
    return new_student;
}

struct student* add_student(struct student* head, const char* name, int student_id, const char* department) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }

    new_student->student_id = student_id;  // Use student_id here
    strcpy(new_student->name, name);
    strcpy(new_student->department, department);
    new_student->next = head;

    return new_student;  // Return the new head of the list
}

// Delete a student by student_id using a single pointer
void delete_student(struct student* head, int student_id) {
    if (head == NULL) {
        printf("No students to delete.\n");
        return;
    }

    struct student* temp = head;
    struct student* prev = NULL;

    // If the student to be deleted is the head
    if (temp != NULL && temp->student_id == student_id) {
        head = temp->next;  // Move the head pointer to the next student
        free(temp);
        return;
    }

    // Search for the student to be deleted
    while (temp != NULL && temp->student_id != student_id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found.\n", student_id);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// Update the student information in both the linked list and the file
void update_student(struct student* head, int student_id, const char* new_name, const char* new_department) {
    struct student* temp = head;

    // Traverse the linked list to find the student by ID
    while (temp != NULL) {
        if (temp->student_id == student_id) {
            // Update the student in the linked list
            strncpy(temp->name, new_name, MAX_NAME_LENGTH);
            strncpy(temp->department, new_department, MAX_DEPT_LENGTH);
            printf("Student information updated in memory.\n");

            // Now update the information in the file
            FILE* file = fopen("students.txt", "r+");
            if (!file) {
                perror("Error opening students file");
                return;
            }

            struct student file_student;
            long pos;
            int found = 0;

            // Read through the file and update the student information
            while (fscanf(file, "%d,%99[^,],%49[^,]\n",
                          &file_student.student_id, file_student.name,
                          file_student.department) != EOF) {
                pos = ftell(file);  // Save the position to update the correct record later

                if (file_student.student_id == student_id) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                // Move the file pointer back to the correct position and update the record
                fseek(file, pos - sizeof(file_student), SEEK_SET);
                fprintf(file, "%d,%s,%s\n", student_id, new_name, new_department);
                printf("Student information updated in file.\n");
            } else {
                printf("Student ID %d not found in file.\n", student_id);
            }

            fclose(file);  // Close the file
            return;
        }
        temp = temp->next;
    }

    printf("Student with ID %d not found.\n", student_id);
}

// Define the function with the correct return type
struct student* search_student(struct student* head, int student_id) {
    struct student* temp = head;

    while (temp != NULL) {
        if (temp->student_id == student_id) {
            return temp;  // Return the student pointer if found
        }
        temp = temp->next;
    }

    return NULL;  // Return NULL if student not found
}

// View all students
void view_students(struct student* head) {
    if (head == NULL) {
        printf("No students available.\n");
        return;
    }

    struct student* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Department: %s\n", temp->student_id, temp->name, temp->department);
        temp = temp->next;
    }
}
