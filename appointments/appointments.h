#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include "../manager.h" // for Appointment struct and shared constants

// ==========================
// Appointment Management Prototypes
// ==========================

void addAppointment(void);

void viewAppointments(void);

void updateAppointment(void);

void deleteAppointment(void);

// CSV handling

void loadAppointmentsFromCSV(const char *filename);

void saveAppointmentsToCSV(const char *filename);

#endif 
