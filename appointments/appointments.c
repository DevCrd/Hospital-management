#include "appointments.h"

#define APPOINTMENTS_FILE "appointments.csv"

// Data storage
Appointment appointments[100];
int appointmentCount = 0;

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}
void generateNewAppointmentId(char *newId) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    int maxId = 0;

    if (fp) {
        Appointment temp;
        while (fscanf(fp, "%19[^,],%19[^,],%19[^,],%9[^,],%19[^,],%199[^\n]\n",
                      temp.id, temp.patientId, temp.date,
                      temp.time, temp.doctor, temp.description) == 6) {
            int num = 0;
            if (sscanf(temp.id, "A%d", &num) == 1 && num > maxId) {
                maxId = num;
            }
        }
        fclose(fp);
    }

    sprintf(newId, "A%03d", maxId + 1);
}

void addAppointment(void) {
    Appointment appt;
    generateNewAppointmentId(appt.id); 

    printf("Enter Patient ID (e.g., P001): ");
    scanf("%s", appt.patientId);

    int patientFound = 0;
    FILE *fp = fopen("patients.csv", "r");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }

    Patient tempPatient;
    while (fscanf(fp, "%19[^,],%99[^,],%d,%7[^,],%19[^,],%19[^,],%19[^\n]\n",
                  tempPatient.id, tempPatient.name, &tempPatient.age,
                  tempPatient.gender, tempPatient.address,
                  tempPatient.phone, tempPatient.email) == 6) {
        
        if (strcmp(tempPatient.id, appt.patientId) == 0) {
            patientFound = 1;
            break;
        }
    }
    fclose(fp);
    // printf("Comparing: tempPatient.id = '%s' | appt.patientId = '%s'\n",
    //     tempPatient.id, appt.patientId);
    if (!patientFound) {
        printf("Error: Patient with ID %s does not exist. Appointment not added.\n", appt.patientId);
        return;
    }

    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", appt.date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", appt.time);
    printf("Enter Doctor: ");
    getchar();
    fgets(appt.doctor, sizeof(appt.doctor), stdin);
    trimNewline(appt.doctor);
    printf("Enter Description: ");
    getchar();
    fgets(appt.description, MAX_APPOINTMENT_DESC, stdin);
    trimNewline(appt.description);


    fp = fopen(APPOINTMENTS_FILE, "a"); 
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }

    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
            appt.id, appt.patientId, appt.date,
            appt.time, appt.doctor, appt.description);

    fclose(fp);
    printf("Appointment added successfully with ID: %s\n", appt.id);
}

void viewAppointments(void) {
    FILE *fp = fopen(APPOINTMENTS_FILE, "r");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }

    Appointment appt;
    printf("\n--- Appointment List ---\n");
    while (fscanf(fp, "%19[^,],%19[^,],%19[^,],%9[^,],%19[^,],%199[^\n]\n",
                  appt.id, appt.patientId, appt.date, appt.time,
                  appt.doctor, appt.description) == 6) {
        printf("ID: %s | Patient ID: %s | Date: %s | Time: %s | Doctor: %s | Desc: %s\n",
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

    while (fscanf(fp, "%19[^,],%19[^,],%19[^,],%9[^,],%19[^,],%199[^\n]\n",
                  appts[count].id, appts[count].patientId, appts[count].date,
                  appts[count].time, appts[count].doctor, appts[count].description) == 6) {
        count++;
    }
    fclose(fp);

    char id[MAX_APPOINTMENT_ID];
    printf("Enter Appointment ID to update: ");
    scanf("%s", id);
    getchar();

    for (size_t i = 0; i < count; i++) {
        if (strcmp(appts[i].id, id) == 0) {
            char buffer[256];

            printf("Enter new Date (YYYY-MM-DD) [%s]: ", appts[i].date);
            if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
                trimNewline(buffer);
                strncpy(appts[i].date, buffer, sizeof(appts[i].date));
            }
            // scanf("%s", appts[i].date); // we can't use scanf for the operation because it skips whitespace change it to fget

            printf("Enter new Time (HH:MM) [%s]: ", appts[i].time);
            if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
                trimNewline(buffer);
                strncpy(appts[i].time, buffer, sizeof(appts[i].time));
            }

            printf("Enter new Doctor [%s]: ", appts[i].doctor);
            if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
                trimNewline(buffer);
                strncpy(appts[i].doctor, buffer, sizeof(appts[i].doctor)-1);
                appts[i].doctor[sizeof(appts[i].doctor)-1] = '\0';
            }

            printf("Enter new Description [%s]: ", appts[i].description);
            if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
                trimNewline(buffer);
                strncpy(appts[i].description, buffer, sizeof(appts[i].description));
            }

            break;
        }
    }

    fp = fopen(APPOINTMENTS_FILE, "w");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }
    for (size_t i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
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

    while (fscanf(fp, "%19[^,],%19[^,],%19[^,],%9[^,],%19[^,],%199[^\n]\n",
                  appts[count].id, appts[count].patientId, appts[count].date,
                  appts[count].time, appts[count].doctor, appts[count].description) == 6) {
        count++;
    }
    fclose(fp);

    char id[MAX_APPOINTMENT_ID];
    printf("Enter Appointment ID to delete: ");
    scanf("%s", id);

    size_t newCount = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(appts[i].id, id) != 0) {
            appts[newCount++] = appts[i];
        }
    }

    fp = fopen(APPOINTMENTS_FILE, "w");
    if (!fp) {
        perror("Error opening appointments file");
        return;
    }
    for (size_t i = 0; i < newCount; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
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
    while (fscanf(fp, "%19[^,],%19[^,],%19[^,],%9[^,],%19[^,],%199[^\n]\n",
                  appt.id, appt.patientId, appt.date, appt.time,
                  appt.doctor, appt.description) == 6) {
        printf("ID: %s | Patient ID: %s | Date: %s | Time: %s | Doctor: %s | Desc: %s\n",
               appt.id, appt.patientId, appt.date, appt.time, appt.doctor, appt.description);
    }
    fclose(fp);
}
