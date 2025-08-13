#ifndef TREATMENTS_H
#define TREATMENTS_H

#include "../manager.h" // for Appointment struct and shared constants


// ==========================
// Treatment Management Prototypes
// ==========================

#define MAX_TREATMENTS 100
#define TREATMENTS_FILE "treatments.csv"

Treatment treatments[MAX_TREATMENTS];
int treatmentCount = 0;

// Utility
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}




void addTreatment(){
    if (treatmentCount >= MAX_TREATMENTS){
        printf("Cannot add more treatments. \n");
        return;
    }

    Treatment t;
    printf("Enter ID: ");
    scanf("%d", &t.id);
    clearInputBuffer();

    printf("Enter Name: ");
    fgets(t.patientId, MAX_PATIENT_NAME, stdin);
    t.patientId[strcspn(t.patientId, "\n")] = '\0';

    treatments[treatmentCount++] = t;
    print("Treatment added Successfully. \n");

}



void viewTreatments(){
    printf("\n--- Treatment List ---\n");
    for (int i = 0; i < treatmentCount; i++)
    {
        printf("ID: %d \n", treatments[i].id);
        printf("Patient_ID: %d \n", treatments[i].patientId);
        printf("Description: %d \n", treatments[i].description);
    }
    
}



void updateTreatment(){
    int id = 0;
    int found = 0;
    printf("Enter Treatment ID to Update");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < treatmentCount; i++){
        if (treatments[i].id == id){
            found = 1;  
            printf("Enter new Patient ID: ");
            fgets(treatments[i].patientId, MAX_PATIENT_ID, stdin);
            treatments[i].patientId[strcspn(treatments[i].patientId, "\n")] = '\0';

            printf("Enter new Description: ");
            fgets(treatments[i].description, MAX_TREATMENT_DESC, stdin);
            treatments[i].description[strcspn(treatments[i].description, "\n")] = '\0';

            printf("Treatment Update. \n");
            break;
        }
    }

    if (!found){
        printf("Treatment with ID %d not found. \n", id);
    }
}


void deleteTreatment(){
    int id = 0;
    int found = 0;
    printf("Enter Treatment ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < treatmentCount; i++){
        if(treatments[i].id == id){
            for(int j = i; j < treatmentCount - 1; j++){
                treatments[j] = treatments[j + 1];
            }
            treatmentCount--;
            found =  1;
            printf("Treatment Deleterd. \n");
            break;
        }
    }

    if (!found){
        printf("Treatment with ID %d not found. \n", id);
    }
}

// CSV handling 

void loadTreatmentsFromCSV(Treatment *treatments){
    FILE *fp = fopen(TREATMENTS_FILE, "r");
    if (fp == NULL){
        perror("Fail to open a file");
        return;
    }

    treatmentCount = 0;
    while (fscanf(fp, "%d, %99[^,], %255[^,], \n", 
        &treatments[treatmentCount].id, 
        treatments[treatmentCount].patientId, 
        treatments[treatmentCount].description) == 3){
        treatmentCount++; 
        if (treatmentCount >= MAX_TREATMENTS)
        break;     
    }
    fclose(fp);
}


void saveTreatmentsToCSV(Treatment *treatments) {
    FILE *fp = fopen(TREATMENTS_FILE, "w");
    if (!fp) {
        perror("Failed to write to file");
        return;
    }

    for (int i = 0; i < treatmentCount; i++) {
        fprintf(fp, "%d,%d,%s,\n",
                treatments[i].id,
                treatments[i].patientId,
                treatments[i].description);
    }

    fclose(fp);
}

#endif
