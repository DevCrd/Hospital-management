#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MANAGER_H
#define MANAGER_H

// =========================
// Constants
// =========================
#define MAX_NAME_LEN 64
#define MAX_DATE_LEN 16
#define MAX_DESC_LEN 128

// =========================
// Struct Definitions
// =========================
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char sex[8];
    char phone[24];
    int is_active;
} Patient;

typedef struct {
    int id;
    int patient_id;
    char date[MAX_DATE_LEN];
    char time[8];
    char doctor[64];
    int is_active;
} Appointment;

typedef struct {
    int id;
    int patient_id;
    char date[MAX_DATE_LEN];
    char description[MAX_DESC_LEN];
    int is_active;
} Treatment;

// =========================
// Function Prototypes
// =========================

// Patient management
void add_patient(Patient *patients, int *count);
void list_patients(Patient *patients, int count);
void update_patient(Patient *patients, int count);
void delete_patient(Patient *patients, int *count);

// Appointment management
void add_appointment(Appointment *appointments, int *count, Patient *patients, int patient_count);
void list_appointments(Appointment *appointments, int count);
void update_appointment(Appointment *appointments, int count);
void delete_appointment(Appointment *appointments, int *count);

// Treatment management
void add_treatment(Treatment *treatments, int *count, Patient *patients, int patient_count);
void list_treatments(Treatment *treatments, int count);
void update_treatment(Treatment *treatments, int count);
void delete_treatment(Treatment *treatments, int *count);

// Utility functions
void save_data(Patient *patients, int patient_count,
               Appointment *appointments, int appointment_count,
               Treatment *treatments, int treatment_count);

void load_data(Patient *patients, int *patient_count,
               Appointment *appointments, int *appointment_count,
               Treatment *treatments, int *treatment_count);

#endif // MANAGER_H
