#ifndef TREATMENTS_H
#define TREATMENTS_H

#include "../manager.h" // for Treatment struct and shared constants


// ==========================
// Treatment Management Prototypes
// ==========================


void addTreatment();

void viewTreatments();

void updateTreatment();

void deleteTreatment();

void searchTreatmentsByPatientId();


// CSV handling 

void loadTreatmentsFromCSV();
void saveTreatmentsToCSV();

#endif
