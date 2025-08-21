#include <stdio.h>
#include "manager.h"
#include "patients/patients.h"
#include "appointments/appointments.h"
#include "treatments/treatments.h"

void managePatients() {
    int choice;
    do {
        printf("\n--- Patients Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Update Patient\n");
        printf("4. Delete Patient\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: updatePatient(); break;
            case 4: deletePatient(); break;
        }
    } while (choice != 0);
}

void manageAppointments() {
    int choice;
    do {
        printf("\n--- Appointments Menu ---\n");
        printf("1. Add Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Update Appointment\n");
        printf("4. Delete Appointment\n");
        printf("5. Search Appointments by Patient ID\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: updateAppointment(); break;
            case 4: deleteAppointment(); break;
            case 5: searchAppointmentsByPatientId(); break;
        }
    } while (choice != 0);
}

void manageTreatments() {
    int choice;
    do {
        printf("\n--- Treatments Menu ---\n");
        printf("1. Add Treatment\n");
        printf("2. View Treatments\n");
        printf("3. Update Treatment\n");
        printf("4. Delete Treatment\n");
        printf("5. Search Treatments by Patient ID\n"); 
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTreatment(); break;
            case 2: viewTreatments(); break;
            case 3: updateTreatment(); break;
            case 4: deleteTreatment(); break;
            case 5: searchTreatmentsByPatientId(); break;
        }
    } while (choice != 0);
}



// ==========================
// File Management
// ==========================


