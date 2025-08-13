#include <stdio.h>
#include "appointments/appointments.h"

#define TEST_CSV_FILE "appointments.csv"

int main() {
    printf("=== Appointment Module Test ===\n");


    int choice;
    do {
        printf("\n--- Appointments Menu ---\n");
        printf("1. Add Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Update Appointment\n");
        printf("4. Delete Appointment\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: updateAppointment(); break;
            case 4: deleteAppointment(); break;
        }
    } while (choice != 0);
    // // Load existing appointments from CSV
    // printf("Loading appointments from CSV...\n");
    // loadAppointmentsFromCSV(TEST_CSV_FILE);

    // // Add a new appointment
    // printf("Adding appointment...\n");
    // addAppointment();  // no arguments

    // // Display all appointments
    // printf("\nCurrent appointments:\n");
    // loadAppointmentsFromCSV(TEST_CSV_FILE);  // prints all
}
