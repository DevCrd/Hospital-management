#ifndef TREATMENTS_H
#define TREATMENTS_H

#include "../manager.h" // for Appointment struct and shared constants


// ==========================
// Treatment Management Prototypes
// ==========================


void addTreatment();

void viewTreatments();

void updateTreatment();

void deleteTreatment();

// CSV handling

void loadTreatmentsFromCSV(const char *filename);
void saveTreatmentsToCSV(const char *filename);

#endif
