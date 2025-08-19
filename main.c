#include <stdio.h>
#include <stdlib.h>
#include "manager.h"

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int main() {
    int choice;

    do {
        printf("\n=== Hospital Management System ===\n");
        printf("1. Manage Patients\n");
        printf("2. Manage Appointments\n");
        printf("3. Manage Treatments\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                managePatients();
                break;
            case 2:
                manageAppointments();
                break;
            case 3:
                manageTreatments();
                break;
            case 0:
                printf("Exiting... Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
