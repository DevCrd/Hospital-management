#include "patients.h"

#define PATIENTS_FILE "patients.csv"

// Data storage
Patient patients[50];
int patientCount = 0;

void addPatient(void) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    int lastId = 0;

    if (fp) {
        Patient temp;
        while (fscanf(fp, "%d,%99[^,],%d,%19[^,],%199[^,],%19[^,],%99[^\n]\n",
                      &temp.id, temp.name, &temp.age, temp.gender,
                      temp.address, temp.phone, temp.email) == 7) {
            if (temp.id > lastId) {
                lastId = temp.id;
            }
        }
        fclose(fp);
    }

    Patient patient;
    patient.id = lastId + 1;

    printf("Enter Name: ");
    scanf("%s", patient.name);
    printf("Enter Age: ");
    scanf("%d", &patient.age);
    printf("Enter Gender: ");
    scanf("%s", patient.gender);
    printf("Enter Address: ");
    scanf("%s", patient.address);
    printf("Enter Phone: ");
    scanf("%s", patient.phone);
    printf("Enter Email: ");
    scanf("%s", patient.email);

    fp = fopen(PATIENTS_FILE, "a");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }

    fprintf(fp, "%d,%s,%d,%s,%s,%s,%s\n",
            patient.id, patient.name, patient.age, patient.gender,
            patient.address, patient.phone, patient.email);

    fclose(fp);
    printf("Patient added successfully with ID: %d\n", patient.id);
}

void viewPatients(void) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }

    Patient patient;
    printf("\n--- Patient List ---\n");
    while (fscanf(fp, "%d,%99[^,],%d,%19[^,],%199[^,],%19[^,],%99[^\n]\n",
                  &patient.id, patient.name, &patient.age, patient.gender,
                  patient.address, patient.phone, patient.email) == 7) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s | Address: %s | Phone: %s | Email: %s\n",
               patient.id, patient.name, patient.age, patient.gender,
               patient.address, patient.phone, patient.email);
    }

    fclose(fp);
}

void updatePatient(void) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }

    Patient patients[500];
    size_t count = 0;

    while (fscanf(fp, "%d,%99[^,],%d,%19[^,],%199[^,],%19[^,],%99[^\n]\n",
                  &patients[count].id, patients[count].name, &patients[count].age,
                  patients[count].gender, patients[count].address,
                  patients[count].phone, patients[count].email) == 7) {
        count++;
    }
    fclose(fp);

    int id;
    printf("Enter Patient ID to update: ");
    scanf("%d", &id);

    for (size_t i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("Enter new Name: ");
            scanf("%s", patients[i].name);
            printf("Enter new Age: ");
            scanf("%d", &patients[i].age);
            printf("Enter new Gender: ");
            scanf("%s", patients[i].gender);
            printf("Enter new Address: ");
            scanf("%s", patients[i].address);
            printf("Enter new Phone: ");
            scanf("%s", patients[i].phone);
            printf("Enter new Email: ");
            scanf("%s", patients[i].email);
            break;
        }
    }

    fp = fopen(PATIENTS_FILE, "w");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }
    for (size_t i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%d,%s,%s,%s,%s\n",
                patients[i].id, patients[i].name, patients[i].age,
                patients[i].gender, patients[i].address,
                patients[i].phone, patients[i].email);
    }
    fclose(fp);

    printf("Patient updated successfully.\n");
}

void deletePatient(void) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }

    Patient patients[500];
    size_t count = 0;

    while (fscanf(fp, "%d,%99[^,],%d,%19[^,],%199[^,],%19[^,],%99[^\n]\n",
                  &patients[count].id, patients[count].name, &patients[count].age,
                  patients[count].gender, patients[count].address,
                  patients[count].phone, patients[count].email) == 7) {
        count++;
    }
    fclose(fp);

    int id;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    size_t newCount = 0;

    for (size_t i = 0; i < count; i++) {
        if (patients[i].id != id) {
            patients[newCount++] = patients[i];
        }
    }

    fp = fopen(PATIENTS_FILE, "w");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }
    for (size_t i = 0; i < newCount; i++) {
        fprintf(fp, "%d,%s,%d,%s,%s,%s,%s\n",
                patients[i].id, patients[i].name, patients[i].age,
                patients[i].gender, patients[i].address,
                patients[i].phone, patients[i].email);
    }
    fclose(fp);

    printf("Patient deleted successfully.\n");
}

void searchPatient(void) {
    FILE *fp = fopen(PATIENTS_FILE, "r");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }

    char searchName[MAX_PATIENT_NAME];
    printf("Enter name to search for: ");
    scanf("%s", searchName);

    Patient patient;
    int found = 0;
    printf("\n--- Search Results ---\n");
    
    while (fscanf(fp, "%d,%99[^,],%d,%19[^,],%199[^,],%19[^,],%99[^\n]\n",
                  &patient.id, patient.name, &patient.age, patient.gender,
                  patient.address, patient.phone, patient.email) == 7) {
        if (strstr(patient.name, searchName) != NULL) {
            printf("ID: %d | Name: %s | Age: %d | Gender: %s | Address: %s | Phone: %s | Email: %s\n",
                   patient.id, patient.name, patient.age, patient.gender,
                   patient.address, patient.phone, patient.email);
            found = 1;
        }
    }

    if (!found) {
        printf("No patients found with name containing '%s'\n", searchName);
    }

    fclose(fp);
}

void loadPatientsFromCSV(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening patients file");
        return;
    }

    Patient patient;
    while (fscanf(fp, "%d,%99[^,],%d,%19[^,],%199[^,],%19[^,],%99[^\n]\n",
                  &patient.id, patient.name, &patient.age, patient.gender,
                  patient.address, patient.phone, patient.email) == 7) {
        printf("ID: %d | Name: %s | Age: %d | Gender: %s | Address: %s | Phone: %s | Email: %s\n",
               patient.id, patient.name, patient.age, patient.gender,
               patient.address, patient.phone, patient.email);
    }
    fclose(fp);
}
