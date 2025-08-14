#include <stdio.h>
#include "../manager.h"
#include "../patients/patients.h"
#include "../appointments/appointments.h"
#include "../treatments/treatments.h"

int main() {
    printf("=== HPMS Full Module Test ===\n");

    printf("\n-- Patients --\n");
    loadPatientsFromCSV("patients.csv");
    viewPatients();

    printf("\n-- Appointments --\n");
    loadAppointmentsFromCSV("appointments.csv");
    viewAppointments();

    printf("\n-- Treatments --\n");
    loadTreatmentsFromCSV("treatments.csv"); 
    viewTreatments();

    printf("\nAll modules loaded successfully!\n");
    return 0;
}
