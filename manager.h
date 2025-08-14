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
#define MAX_PATIENT_GENDER 8
#define MAX_PATIENT_EMAIL 20    
#define MAX_PATIENT_ADDRESS 20
#define MAX_TREATMENT_ID 20
#define MAX_TREATMENT_DESC 200
#define MAX_APPOINTMENT_DESC 200
#define MAX_APPOINTMENT_ID 20
#define MAX_DATE_LEN 20
#define MAX_TIME_LEN 10
#define MAX_DOCTOR_NAME 20
    

// Structs
typedef struct {
    int age;
    char id[MAX_PATIENT_ID];
    char name[MAX_PATIENT_NAME];
    char gender[MAX_PATIENT_GENDER];
    char phone[MAX_PATIENT_PHONE];
    char address[MAX_PATIENT_ADDRESS];
    char email[MAX_PATIENT_EMAIL];

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
    char doctor[MAX_DOCTOR_NAME];
    char description[MAX_APPOINTMENT_DESC]; 
} Appointment;

// Menu management functions
void managePatients();
void manageAppointments();
void manageTreatments();

#endif
