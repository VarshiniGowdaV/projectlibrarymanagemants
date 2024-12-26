#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

// Function to add a new staff member
struct staff* add_staff(struct staff* head, const char* name, int id, const char* dept, const char* position) {
    struct staff* new_staff = (struct staff*)malloc(sizeof(struct staff));
    if (!new_staff) {
        fprintf(stderr, "Memory allocation failed\n");
        return head;
    }
    strncpy(new_staff->name, name, sizeof(new_staff->name) - 1);
    new_staff->name[sizeof(new_staff->name) - 1] = '\0';
    new_staff->id = id;
    strncpy(new_staff->department, dept, sizeof(new_staff->department) - 1);
    new_staff->department[sizeof(new_staff->department) - 1] = '\0';
    strncpy(new_staff->position, position, sizeof(new_staff->position) - 1);
    new_staff->position[sizeof(new_staff->position) - 1] = '\0';
    new_staff->next = head;
    return new_staff;
}

// Function to view all staff members
void view_staff(struct staff* head) {
    struct staff* current = head;
    while (current) {
        printf("Name: %s, ID: %d, Department: %s, Position: %s\n",
               current->name, current->id, current->department, current->position);
        current = current->next;
    }
}

// Function to manage staff (dummy function)
void manage_staff() {
    printf("Managing Staff...\n");
}

// Function to display the staff menu
void display_staff_menu() {
    printf("Staff Management Menu:\n");
    printf("1. Add Staff\n");
    printf("2. View All Staff\n");
    printf("3. Save Staff to File\n");
    printf("4. Load Staff from File\n");
    printf("5. Return to Main Menu\n");
}

// Function to save staff data to a file
void save_staff_to_file(struct staff* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }

    struct staff* current = head;
    while (current) {
        fwrite(current, sizeof(struct staff), 1, file);
        current = current->next;
    }

    fclose(file);
}

// Function to load staff data from a file
struct staff* load_staff_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file for reading\n");
        return NULL;
    }

    struct staff* head = NULL;
    struct staff* current = NULL;
    struct staff temp;

    while (fread(&temp, sizeof(struct staff), 1, file) == 1) {
        struct staff* new_staff = (struct staff*)malloc(sizeof(struct staff));
        if (!new_staff) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            return head;
        }
        *new_staff = temp;
        new_staff->next = NULL;

        if (!head) {
            head = new_staff;
        } else {
            current->next = new_staff;
        }
        current = new_staff;
    }

    fclose(file);
    return head;
}
