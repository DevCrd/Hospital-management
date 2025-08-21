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

void searchAppointmentsByPatientId(void);

// CSV handling

void loadAppointmentsFromCSV(const char *filename);


#endif 
