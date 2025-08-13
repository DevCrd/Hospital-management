IMPORT manager.h  // Struct definitions + function prototypes

// =======================
// Data Initialization
// =======================

DECLARE arrays:
    patients[MAX_PATIENTS]
    appointments[MAX_APPOINTMENTS]
    treatments[MAX_TREATMENTS]

DECLARE counters:
    patient_count = 0
    appointment_count = 0
    treatment_count = 0

// =======================
// Load Existing Data
// =======================


FUNCTION load_data():
    LOAD patients from "patients/patients.csv"
        PARSE each line -> populate Patient struct
        UPDATE patient_count

    LOAD appointments from "patients/appointments.csv"
        PARSE each line -> populate Appointment struct
        UPDATE appointment_count

    LOAD treatments from "treatments/treatments.csv"
        PARSE each line -> populate Treatment struct
        UPDATE treatment_count
END FUNCTION

// =======================
// Save Data
// =======================

FUNCTION save_data():
    WRITE all patients to "patients/patients.csv"
    WRITE all appointments to "patients/appointments.csv"
    WRITE all treatments to "treatments/treatments.csv"
END FUNCTION

// =======================
// Patient Management
// =======================
FUNCTION add_patient():
    PROMPT for name, age, sex, phone
    ASSIGN unique id = patient_count + 1
    SET is_active = 1
    APPEND to patients[]
    INCREMENT patient_count

FUNCTION list_patients():
    FOR each patient in patients[]:
        IF is_active == 1:
            DISPLAY patient info

FUNCTION update_patient():
    PROMPT for patient id
    FIND patient in patients[]
    IF found:
        PROMPT updated details
        UPDATE patient fields

FUNCTION delete_patient():
    PROMPT for patient id
    FIND patient in patients[]
    IF found:
        SET is_active = 0
        REMOVE related appointments & treatments

// =======================
// Appointment Management
// =======================
FUNCTION add_appointment():
    PROMPT for patient id
    IF patient exists AND is_active == 1:
        PROMPT for date, time, doctor
        ASSIGN unique id
        SET is_active = 1
        APPEND to appointments[]
        INCREMENT appointment_count

FUNCTION list_appointments():
    FOR each appointment in appointments[]:
        IF is_active == 1:
            DISPLAY appointment info

FUNCTION update_appointment():
    PROMPT for appointment id
    FIND in appointments[]
    IF found:
        PROMPT updated details
        UPDATE fields

FUNCTION delete_appointment():
    PROMPT for appointment id
    FIND in appointments[]
    IF found:
        SET is_active = 0

// =======================
// Treatment Management
// =======================
FUNCTION add_treatment():
    PROMPT for patient id
    IF patient exists AND is_active == 1:
        PROMPT for date, description
        ASSIGN unique id
        SET is_active = 1
        APPEND to treatments[]
        INCREMENT treatment_count

FUNCTION list_treatments():
    FOR each treatment in treatments[]:
        IF is_active == 1:
            DISPLAY treatment info

FUNCTION update_treatment():
    PROMPT for treatment id
    FIND in treatments[]
    IF found:
        PROMPT updated details
        UPDATE fields

FUNCTION delete_treatment():
    PROMPT for treatment id
    FIND in treatments[]
    IF found:
        SET is_active = 0

// =======================
// MAIN MENU
// =======================
FUNCTION main():
    CALL load_data()

    LOOP FOREVER:
        DISPLAY menu:
            1. Add Patient
            2. List Patients
            3. Update Patient
            4. Delete Patient
            5. Add Appointment
            6. List Appointments
            7. Update Appointment
            8. Delete Appointment
            9. Add Treatment
            10. List Treatments
            11. Update Treatment
            12. Delete Treatment
            0. Save & Exit

        READ choice

        SWITCH(choice):
            CASE 1: add_patient()
            CASE 2: list_patients()
            CASE 3: update_patient()
            CASE 4: delete_patient()
            CASE 5: add_appointment()
            CASE 6: list_appointments()
            CASE 7: update_appointment()
            CASE 8: delete_appointment()
            CASE 9: add_treatment()
            CASE 10: list_treatments()
            CASE 11: update_treatment()
            CASE 12: delete_treatment()
            CASE 0:
                save_data()
                EXIT PROGRAM
            DEFAULT:
                DISPLAY "Invalid choice"
END FUNCTION

END PROGRAM
