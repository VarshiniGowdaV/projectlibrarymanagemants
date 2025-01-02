#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

// Function to add a staff member
struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position) {
    struct staff* new_staff = (struct staff*)malloc(sizeof(struct staff));
    if (!new_staff) {
        printf("Memory allocation failed\n");
        return head;
    }

    new_staff->id = id;
    strncpy(new_staff->name, name, MAX_NAME_LENGTH);
    strncpy(new_staff->department, department, MAX_DEPT_LENGTH);
    strncpy(new_staff->position, position, MAX_POSITION_LENGTH);
    new_staff->next = head;
    head = new_staff;

    return head;
}

// Function to delete a staff member by ID
void delete_staff(struct staff** head, int id) {
    struct staff* current = *head;
    struct staff* prev = NULL;

    while (current) {
        if (current->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
            printf("Staff with ID %d deleted successfully.\n", id);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", id);
}

// Function to update a staff member's details
void update_staff(struct staff* head, int id) {
    struct staff* current = head;
    while (current) {
        if (current->id == id) {
            printf("Updating staff member: %s\n", current->name);

            // Update staff name
            printf("Enter new name: ");
            fgets(current->name, MAX_NAME_LENGTH, stdin);
            current->name[strcspn(current->name, "\n")] = '\0';  // Remove newline character

            // Update staff ID (use scanf for integer input)
            printf("Enter new ID: ");
            scanf("%d", &current->id);
            getchar();  // Clear the newline character left by scanf

            // Update staff department
            printf("Enter new department: ");
            fgets(current->department, MAX_DEPT_LENGTH, stdin);
            current->department[strcspn(current->department, "\n")] = '\0';  // Remove newline character

            // Update staff position
            printf("Enter new position: ");
            fgets(current->position, MAX_POSITION_LENGTH, stdin);
            current->position[strcspn(current->position, "\n")] = '\0';  // Remove newline character

            printf("Staff details updated successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", id);
}
// Function to search for a staff member by ID
struct staff* search_staff(struct staff* head, int id) {
    struct staff* current = head;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to view all staff members
void view_staff(struct staff* head) {
    struct staff* current = head;
    printf("\nStaff List:\n");
    printf("ID\tName\t\tDepartment\tPosition\n");
    printf("----------------------------------------------\n");

    while (current) {
        printf("%d\t%s\t%s\t%s\n", current->id, current->name, current->department, current->position);
        current = current->next;
    }
}
