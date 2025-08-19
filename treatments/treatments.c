#include "treatments.h"

#define TREATMENTS_FILE "treatments.csv"

Treatment treatments[MAX_TREATMENTS];
int treatmentCount = 0;

// Utility
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void generateTreatmentID(char *idBuffer, int index) {
    sprintf(idBuffer, "T%03d", index + 1);
}

void loadTreatmentsFromCSV() {
    FILE *fp = fopen(TREATMENTS_FILE, "r");
    if (!fp) {
        perror("Error opening treatments file");
        return;
    }

    treatmentCount = 0;
    while (fscanf(fp, "%19[^,],%19[^,],%199[^\n]\n",
                  treatments[treatmentCount].id,
                  treatments[treatmentCount].patientId,
                  treatments[treatmentCount].description) == 3) {
        treatmentCount++;
        if (treatmentCount >= MAX_TREATMENTS) break;
    }
    fclose(fp);
}

void saveTreatmentsToCSV() {
    FILE *fp = fopen(TREATMENTS_FILE, "w");
    if (!fp) {
        perror("Failed to write treatments file");
        return;
    }

    for (int i = 0; i < treatmentCount; i++) {
        fprintf(fp, "%s,%s,%s\n",
                treatments[i].id,
                treatments[i].patientId,
                treatments[i].description);
    }
    fclose(fp);
}

void addTreatment() {
    if (treatmentCount >= MAX_TREATMENTS) {
        printf("Cannot add more treatments.\n");
        return;
    }

    // Flush input buffer
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    Treatment t;
    generateTreatmentID(t.id, treatmentCount);

    printf("Enter Patient ID: ");
    fgets(t.patientId, MAX_PATIENT_ID, stdin);
    t.patientId[strcspn(t.patientId, "\n")] = '\0';

    if (strlen(t.patientId) == 0) {
        printf("Patient ID cannot be empty.\n");
        return;
    }

    printf("Enter Treatment Description: ");
    fgets(t.description, MAX_TREATMENT_DESC, stdin);
    t.description[strcspn(t.description, "\n")] = '\0';

    if (strlen(t.description) == 0) {
        printf("Description cannot be empty.\n");
        return;
    }

    treatments[treatmentCount++] = t;
    saveTreatmentsToCSV();
    printf("Treatment added successfully with ID: %s\n", t.id);
}

void viewTreatments() {
    printf("\n--- Treatment List ---\n");
    for (int i = 0; i < treatmentCount; i++) {
        printf("%s,%s,%s\n",
               treatments[i].id,
               treatments[i].patientId,
               treatments[i].description);
    }
}

// void updateTreatment() {
//     char id[MAX_TREATMENT_ID];

//     // Clear input buffer before reading
//     int ch;
//     while ((ch = getchar()) != '\n' && ch != EOF);

//     printf("Enter Treatment ID to update: ");
//     fgets(id, MAX_TREATMENT_ID, stdin);
//     id[strcspn(id, "\n")] = '\0';

//     for (int i = 0; i < treatmentCount; i++) {
//         if (strcmp(treatments[i].id, id) == 0) {
//             printf("Enter new Patient ID: ");
//             fgets(treatments[i].patientId, MAX_PATIENT_ID, stdin);
//             treatments[i].patientId[strcspn(treatments[i].patientId, "\n")] = '\0';

//             printf("Enter new Description:");
//             fgets(treatments[i].description, MAX_TREATMENT_DESC, stdin);
//             treatments[i].description[strcspn(treatments[i].description, "\n")] = '\0';

//             saveTreatmentsToCSV();
//             printf("Treatment updated.\n");
//             return;
//         }
//     }
//     printf("Treatment with ID %s not found.\n", id);
// }


void updateTreatment() {
    char id[MAX_TREATMENT_ID];

    // Clear input buffer before reading
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Enter Treatment ID to update: ");
    fgets(id, MAX_TREATMENT_ID, stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < treatmentCount; i++) {
        if (strcmp(treatments[i].id, id) == 0) {
            // Show existing data
            printf("\nCurrent Patient ID: %s\n", treatments[i].patientId);
            printf("Current Description: %s\n", treatments[i].description);

            // Get new data
            printf("\nEnter new Patient ID (or press Enter to keep current): ");
            char newPatientId[MAX_PATIENT_ID];
            fgets(newPatientId, MAX_PATIENT_ID, stdin);
            newPatientId[strcspn(newPatientId, "\n")] = '\0';
            if (strlen(newPatientId) > 0) {
                strcpy(treatments[i].patientId, newPatientId);
            }

            printf("Enter new Description (or press Enter to keep current): ");
            char newDescription[MAX_TREATMENT_DESC];
            fgets(newDescription, MAX_TREATMENT_DESC, stdin);
            newDescription[strcspn(newDescription, "\n")] = '\0';
            if (strlen(newDescription) > 0) {
                strcpy(treatments[i].description, newDescription);
            }

            saveTreatmentsToCSV();
            printf("\nTreatment updated.\n");
            return;
        }
    }

    printf("Treatment with ID %s not found.\n", id);
}





void deleteTreatment() {
    char id[MAX_TREATMENT_ID];

    // Flush input buffer
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Enter Treatment ID to delete: ");
    fgets(id, MAX_TREATMENT_ID, stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < treatmentCount; i++) {
        if (strcmp(treatments[i].id, id) == 0) {
            for (int j = i; j < treatmentCount - 1; j++) {
                treatments[j] = treatments[j + 1];
            }
            treatmentCount--;
            saveTreatmentsToCSV();
            printf("Treatment deleted.\n");
            return;
        }
    }
    printf("Treatment with ID %s not found.\n", id);
}
