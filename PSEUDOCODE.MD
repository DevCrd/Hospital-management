START PROGRAM

DEFINE struct Patient:
    id (int)
    name (string)
    age (int)
    gender (string)
    address (string)
    phone (string)
    email (string)

DEFINE struct Appointment:
    appointment_id (int)
    patient_id (int)
    doctor_name (string)
    date (string)
    time (string)
    description (string)
    status (string)

DECLARE dynamic array patient_list
DECLARE dynamic array appointment_list

FUNCTION loadDataFromCSV(patients_path, appointments_path):
    OPEN patients_path for reading
    IF file exists:
        FOR each line (skip header):
            PARSE fields
            CREATE Patient struct
            APPEND to patient_list
    ELSE:
        INIT empty patient_list

    OPEN appointments_path for reading
    IF file exists:
        FOR each line (skip header):
            PARSE fields
            CREATE Appointment struct
            APPEND to appointment_list
    ELSE:
        INIT empty appointment_list
END FUNCTION

FUNCTION saveDataToCSV(patients_path, appointments_path):
    OPEN patients_path for writing
    WRITE CSV header
    FOR each Patient in patient_list:
        WRITE CSV row

    OPEN appointments_path for writing
    WRITE CSV header
    FOR each Appointment in appointment_list:
        WRITE CSV row
END FUNCTION

FUNCTION addPatient():
    PROMPT for patient details
    GENERATE unique patient_id
    CREATE Patient struct
    APPEND to patient_list
END FUNCTION

FUNCTION updatePatient():
    PROMPT for patient_id
    SEARCH patient_list for matching id
    IF found:
        PROMPT for updated details
        UPDATE fields
    ELSE:
        DISPLAY "Patient not found"
END FUNCTION

FUNCTION searchPatient():
    PROMPT for name substring
    FOR each Patient in patient_list:
        IF name contains substring:
            DISPLAY patient info
END FUNCTION

FUNCTION deletePatient():
    PROMPT for patient_id
    SEARCH patient_list
    IF found:
        REMOVE from patient_list
        REMOVE related appointments
    ELSE:
        DISPLAY "Patient not found"
END FUNCTION

FUNCTION bookAppointment():
    PROMPT for patient_id
    IF patient exists:
        PROMPT for doctor_name, date, time, description
        GENERATE unique appointment_id
        CREATE Appointment struct (status = "BOOKED")
        APPEND to appointment_list
    ELSE:
        DISPLAY "Patient not found"
END FUNCTION

FUNCTION viewAppointments():
    FOR each Appointment in appointment_list:
        DISPLAY appointment info
END FUNCTION

FUNCTION AddTreatment():
    PROMPT for patient_id
    IF patient exists:
        PROMPT for date, description
        GENERATE unique Treatment_id
        CREATE treatment struct (status = "ACTIVE")
        APPEND to treatment_list
    ELSE:
        DISPLAY "Patient not found"
END FUNCTION

FUNCTION UPDATETreatment():
    PROMPT for patient_id
    SEARCH patient_list for matching id
    IF found:
        prompt for Treatment_id
            IF found:
                UPDATE treatment struct (status = "INACTIVE")
            ELSE:
                DISPLAY "Treatment not found"
                return 1;
    ELSE:
        DISPLAY "Patient not found"
END FUNCTION

FUNCTION viewTreatment():
    PROMPT for patient_id
    FOR each treatment in treatment_list:
        IF treatment.patient_id == patient_id:
            DISPLAY date, description, status
END FUNCTION


MAIN:
    CALL loadDataFromCSV("patients/patients.csv", "patients/appointments.csv")

    LOOP:
        DISPLAY menu options
        READ choice

        SWITCH choice:
            CASE 1: CALL addPatient()
            CASE 2: CALL updatePatient()
            CASE 3: CALL searchPatient()
            CASE 4: CALL deletePatient()
            CASE 5: CALL bookAppointment()
            CASE 6: CALL viewAppointments()
            CASE 7: CALL viewTreatmentHistory()
            CASE 8:
                CALL saveDataToCSV()
                EXIT LOOP
            DEFAULT:
                DISPLAY "Invalid choice"

END PROGRAM
