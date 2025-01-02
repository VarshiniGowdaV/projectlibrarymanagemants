#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position) {
    struct staff* new_staff = (struct staff*)malloc(sizeof(struct staff));
    if (new_staff == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }
    new_staff->id = id;
    strncpy(new_staff->name, name, MAX_NAME_LENGTH);
    new_staff->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(new_staff->department, department, MAX_DEPT_LENGTH);
    new_staff->department[MAX_DEPT_LENGTH - 1] = '\0';
    strncpy(new_staff->position, position, MAX_POSITION_LENGTH);
    new_staff->position[MAX_POSITION_LENGTH - 1] = '\0';
    new_staff->next = head;

    return new_staff;
}
void view_staff(struct staff* head) {
    if (head == NULL) {
        printf("No staff members available.\n");
        return;
    }
    printf("Staff List:\n");
    struct staff* current = head;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Department: %s, Position: %s\n",
               current->id, current->name, current->department, current->position);
        current = current->next;
        printf("--------------------\n");
    }
}
