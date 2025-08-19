#include "treatments.h"

#define TREATMENTS_FILE "treatments.csv"
#define PATIENTS_FILE "patients.csv"

Treatment treatments[MAX_TREATMENTS];
int treatmentCount = 0;


void generateNewTreatmentId(char *newId) {
    FILE *fp = fopen(TREATMENTS_FILE, "r");
    int maxId = 0;

    if (fp) {
        Treatment temp;
        while (fscanf(fp, "%19[^,],%19[^,],%199[^\n]\n",
                      temp.id, temp.patientId, temp.description) == 3) {
            int num = 0;
            if (sscanf(temp.id, "T%d", &num) == 1 && num > maxId) {
                maxId = num;
            }
        }
        fclose(fp);
    }

    sprintf(newId, "T%03d", maxId + 1);
}

int patientExists(const char *patientId) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp) return 0;

    Patient temp;
    int found = 0;

    while (fscanf(fp, "%19[^,],%99[^,],%d,%7[^,],%19[^,],%19[^,],%19[^\n]\n",
                  temp.id, temp.name, &temp.age, temp.gender,
                  temp.address, temp.phone, temp.email) == 7) {
        // printf("Comparing: file patient.id = '%s' | searching for = '%s'\n",
        //        temp.id, patientId);  
        if (strcmp(temp.id, patientId) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
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

    Treatment t;
    generateNewTreatmentId(t.id);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);


    printf("Enter Patient ID (e.g., P001): ");
    fgets(t.patientId, MAX_PATIENT_ID, stdin);
    trimNewline(t.patientId);


        
    if (!patientExists(t.patientId)) {
        printf("Error: Patient with ID %s does not exist. Treatment not added.\n", t.patientId);
        return;
    }

    printf("Enter Treatment Description: ");
    fgets(t.description, MAX_TREATMENT_DESC, stdin);
    trimNewline(t.description);

    treatments[treatmentCount++] = t;
    saveTreatmentsToCSV();
    printf("Treatment added successfully with ID: %s\n", t.id);
}

void viewTreatments() {
    printf("\n--- Treatment List ---\n");
    for (int i = 0; i < treatmentCount; i++) {
        printf("ID: %s | Patient ID: %s | Description: %s\n",
               treatments[i].id,
               treatments[i].patientId,
               treatments[i].description);
    }
}

void updateTreatment() {
    char id[MAX_TREATMENT_ID];

    loadTreatmentsFromCSV();

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter Treatment ID to update: ");
    fgets(id, MAX_TREATMENT_ID, stdin);
    trimNewline(id);

    for (int i = 0; i < treatmentCount; i++) {
        if (strcmp(treatments[i].id, id) == 0) {
            char buffer[256];

            printf("Enter new Patient ID [%s]: ", treatments[i].patientId);
            if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
                trimNewline(buffer);
                if (!patientExists(buffer)) {
                    printf("Error: Patient with ID %s does not exist. Update cancelled.\n", buffer);
                    return;
                }
                strncpy(treatments[i].patientId, buffer, MAX_PATIENT_ID);
            }

            printf("Enter new Description [%s]: ", treatments[i].description);
            if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') {
                trimNewline(buffer);
                strncpy(treatments[i].description, buffer, MAX_TREATMENT_DESC);
            }

            saveTreatmentsToCSV();
            printf("Treatment updated successfully.\n");
            return;
        }
    }
    printf("Treatment with ID %s not found.\n", id);
}

void deleteTreatment() {
    char id[MAX_TREATMENT_ID];
    
    loadTreatmentsFromCSV();

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter Treatment ID to delete: ");
    fgets(id, MAX_TREATMENT_ID, stdin);
    trimNewline(id);

    for (int i = 0; i < treatmentCount; i++) {
        if (strcmp(treatments[i].id, id) == 0) {
            for (int j = i; j < treatmentCount - 1; j++) {
                treatments[j] = treatments[j + 1];
            }
            treatmentCount--;
            saveTreatmentsToCSV();
            printf("Treatment deleted successfully.\n");
            return;
        }
    }
    printf("Treatment with ID %s not found.\n", id);
}
