#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Shared constants
#define MAX_PATIENT_NAME 100
#define MAX_PATIENT_ID   20
#define MAX_PATIENT_PHONE 20
#define MAX_TREATMENT_ID 20
#define MAX_TREATMENT_DESC 200
#define MAX_APPOINTMENT_DESC 200
#define MAX_APPOINTMENT_ID 20
#define MAX_DATE_LEN 20
#define MAX_TIME_LEN 10

// Structs
typedef struct {
    char id[MAX_PATIENT_ID];
    char name[MAX_PATIENT_NAME];
    int age;
    char phone[MAX_PATIENT_PHONE];
} Patient;

typedef struct {
    char id[MAX_TREATMENT_ID];
    char patientId[MAX_PATIENT_ID];
    char description[MAX_TREATMENT_DESC];
} Treatment;

typedef struct {
    int id;
    int patientId;
    char date[MAX_DATE_LEN];
    char time[MAX_TIME_LEN];
    char doctor[MAX_PATIENT_NAME];
    char description[MAX_APPOINTMENT_DESC]; 
} Appointment;

// Menu management functions
void managePatients();
void manageAppointments();
void manageTreatments();

#endif
