#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

// Function to add a new staff member
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position) {
    struct staff* new_staff = (struct staff*)malloc(sizeof(struct staff));
    if (new_staff == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    new_staff->id = id;
    strcpy(new_staff->name, name);
    strcpy(new_staff->department, department);
    strcpy(new_staff->position, position); // Add position field
    new_staff->next = head;

    return new_staff;
}

// Function to view all staff members
void view_staff(struct staff* head) {
    struct staff* current = head;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Department: %s, Position: %s\n", current->id, current->name, current->department, current->position);
        current = current->next;
    }
}
