#ifndef PATIENTS_H
#define PATIENTS_H

#include "../manager.h" // for Patients struct and shared constants


// ==========================
// Patient Management Prototypes
// ==========================

void addPatient();

void viewPatients();

void updatePatient();

void deletePatient();

// CSV handling

void loadPatientsFromCSV(const char *filename);
void savePatientsToCSV(const char *filename);

#endif
