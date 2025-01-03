#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

//int staff_count = 0;
//struct staff* staff_head = NULL;

struct staff* add_staff(struct staff* head, const char* name, int id, const char* department, const char* position) {
    struct staff* new_staff = malloc(sizeof(struct staff));
    if (!new_staff) {
        printf("Memory allocation failed.\n");
        return head;
    }
    strcpy(new_staff->staff_name, name);
    strcpy(new_staff->department, department);
    strcpy(new_staff->position, position);
    new_staff->staff_id = id;
    new_staff->next = head;
    return new_staff;
}

void delete_staff(struct staff** head, int id) {
    struct staff *temp = *head, *prev = NULL;
    while (temp && temp->staff_id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Staff with ID %d not found.\n", id);
        return;
    }
    if (prev)
        prev->next = temp->next;
    else
        *head = temp->next;
    free(temp);
    printf("Staff deleted successfully.\n");
}
void update_staff(struct staff* head, int id) {
    struct staff* temp = head;

    // Traverse the linked list to find the staff by ID
    while (temp && temp->staff_id != id) {
        temp = temp->next;
    }
    if (!temp) {
        printf("Staff with ID %d not found.\n", id);
        return;
    }
    printf("Enter new name: ");
    scanf(" %[^\n]", temp->staff_name);
    printf("Enter new department: ");
    scanf(" %[^\n]", temp->department);
    printf("Enter new position: ");
    scanf(" %[^\n]", temp->position);

    printf("Staff updated successfully in memory.\n");

    // Open the file to update the staff data
    FILE* file = fopen("staff.txt", "r+");
    if (!file) {
        perror("Error opening staff file");
        return;
    }

    struct staff file_staff;
    long pos;
    int found = 0;

    // Read through the file to find the record and update it
    while (fscanf(file, "%d,%99[^,],%99[^,],%99[^,]\n",
                  &file_staff.staff_id, file_staff.staff_name,
                  file_staff.department, file_staff.position) != EOF) {
        pos = ftell(file);  // Save the position to update the correct record later

        if (file_staff.staff_id == id) {
            found = 1;
            break;
        }
    }

    if (found) {
        // Move file pointer to the position of the staff record and update it
        fseek(file, pos - sizeof(file_staff), SEEK_SET);
        fprintf(file, "%d,%s,%s,%s\n", temp->staff_id, temp->staff_name, temp->department, temp->position);
        printf("Staff updated successfully in file.\n");
    } else {
        printf("Staff ID %d not found in file.\n", id);
    }

    fclose(file);  // Close the file
}

struct staff* search_staff(struct staff* head, int id) {
    struct staff* temp = head;
    while (temp && temp->staff_id != id) {
        temp = temp->next;
    }
    return temp;
}

void view_staff(struct staff* head) {
    struct staff* temp = head;
    if (!temp) {
        printf("No staff records available.\n");
        return;
    }
    printf("Staff Records:\n");
    while (temp) {
        printf("ID: %d, Name: %s, Department: %s, Position: %s\n", temp->staff_id, temp->staff_name, temp->department, temp->position);
        temp = temp->next;
    }
}

