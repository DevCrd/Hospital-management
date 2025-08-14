#include "appointments.h"

#define APPOINTMENTS_FILE "appointments.csv"

// Data storage
Appointment appointments[100];
int appointmentCount = 0;

void addAppointment(void) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    int lastId = 0;

    if (fp) {
        Appointment temp;
        while (fscanf(fp, "%d,%d,%19[^,],%9[^,],%99[^,],%199[^\n]\n",
                      &temp.id, &temp.patientId, temp.date,
                      temp.time, temp.doctor, temp.description) == 6) {
            if (temp.id > lastId) {
                lastId = temp.id;
            }
        }
        fclose(fp);
    }

    Appointment appt;
    appt.id = lastId + 1; // ID is based on the appointment index

    printf("Enter Patient ID: ");
    scanf("%d", &appt.patientId);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", appt.date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", appt.time);
    printf("Enter Doctor: ");
    scanf("%s", appt.doctor);
    printf("Enter Description: ");
    getchar(); 
    fgets(appt.description, MAX_APPOINTMENT_DESC, stdin);
    appt.description[strcspn(appt.description, "\n")] = 0; 

    fp = fopen(APPOINTMENTS_FILE, "a");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }

    fprintf(fp, "%d,%d,%s,%s,%s,%s\n",
            appt.id, appt.patientId, appt.date,
            appt.time, appt.doctor, appt.description);

    fclose(fp);
    printf("Appointment added successfully with ID: %d\n", appt.id);
}


void viewAppointments(void) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }

    Appointment appt;
    printf("\n--- Appointment List ---\n");
    while (fscanf(fp, "%d,%d,%19[^,],%9[^,],%99[^,],%199[^\n]\n",
                  &appt.id, &appt.patientId, appt.date, appt.time,
                  appt.doctor, appt.description) == 6) {
        printf("ID: %d | Patient ID: %d | Date: %s | Time: %s | Doctor: %s | Desc: %s\n",
               appt.id, appt.patientId, appt.date, appt.time, appt.doctor, appt.description);
    }

    fclose(fp);
}

void updateAppointment(void) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }

    Appointment appts[500];
    size_t count = 0;

    while (fscanf(fp, "%d,%d,%19[^,],%9[^,],%99[^,],%199[^\n]\n",
                  &appts[count].id, &appts[count].patientId, appts[count].date,
                  appts[count].time, appts[count].doctor, appts[count].description) == 6) {
        count++;
    }
    fclose(fp);

    int id;
    printf("Enter Appointment ID to update: ");
    scanf("%d", &id);

    for (size_t i = 0; i < count; i++) {
        if (appts[i].id == id) {
            printf("Enter new Date (YYYY-MM-DD): ");
            scanf("%s", appts[i].date);
            printf("Enter new Time (HH:MM): ");
            scanf("%s", appts[i].time);
            printf("Enter new Doctor: ");
            scanf("%s", appts[i].doctor);
            printf("Enter new Description: ");
            getchar();
            fgets(appts[i].description, MAX_APPOINTMENT_DESC, stdin);
            appts[i].description[strcspn(appts[i].description, "\n")] = 0;
            break;
        }
    }

    fp = fopen(APPOINTMENTS_FILE, "w");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }
    for (size_t i = 0; i < count; i++) {
        fprintf(fp, "%d,%d,%s,%s,%s,%s\n",
                appts[i].id, appts[i].patientId, appts[i].date,
                appts[i].time, appts[i].doctor, appts[i].description);
    }
    fclose(fp);

    printf("Appointment updated successfully.\n");
}

void deleteAppointment(void) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }

    Appointment appts[500];
    size_t count = 0;

    while (fscanf(fp, "%d,%d,%19[^,],%9[^,],%99[^,],%199[^\n]\n",
                  &appts[count].id, &appts[count].patientId, appts[count].date,
                  appts[count].time, appts[count].doctor, appts[count].description) == 6) {
        count++;
    }
    fclose(fp);

    int id;
    printf("Enter Appointment ID to delete: ");
    scanf("%d", &id);

    size_t newCount = 0;

    for (size_t i = 0; i < count; i++) {
        if (appts[i].id != id) {
            appts[newCount++] = appts[i];
        }
    }

    fp = fopen(APPOINTMENTS_FILE, "w");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }
    for (size_t i = 0; i < newCount; i++) {
        fprintf(fp, "%d,%d,%s,%s,%s,%s\n",
                appts[i].id, appts[i].patientId, appts[i].date,
                appts[i].time, appts[i].doctor, appts[i].description);
    }
    fclose(fp);

    printf("Appointment deleted successfully.\n");
}

void loadAppointmentsFromCSV(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }

    Appointment appt;
    while (fscanf(fp, "%d,%d,%19[^,],%9[^,],%99[^,],%199[^\n]\n",
                  &appt.id, &appt.patientId, appt.date, appt.time,
                  appt.doctor, appt.description) == 6) {
        printf("ID: %d | Patient ID: %d | Date: %s | Time: %s | Doctor: %s | Desc: %s\n",
               appt.id, appt.patientId, appt.date, appt.time, appt.doctor, appt.description);
    }
    fclose(fp);
}


