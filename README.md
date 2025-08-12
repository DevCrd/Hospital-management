# Hospital Patient Management System (HPMS)

> **Short:** A simple, menu-driven C program to manage patient records, appointments and treatment history. Data is persisted using CSV files so the program can be stopped and restarted without losing information.

---

## Table of Contents

1. Project Overview
2. Features
3. Project Structure
4. Prerequisites
5. Build & Run (step-by-step)
6. Data files & CSV format
7. CLI menu and expected behavior
8. Function reference (what each function does)
9. Testing & sample session
10. Troubleshooting
11. Extending the project (suggestions)
12. Coding conventions


---

## 1. Project Overview

HPMS is designed to help small hospitals/clinics manage:

* Patient personal records
* Doctor appointments
* Treatment history per patient

The app is intentionally simple (C, CLI, CSV persistence) so it is suitable as a capstone that demonstrates file I/O, dynamic memory management, structures, and basic data modeling.

## 2. Features

* Add / Update / Search / Delete patient records.
* Book, view and cancel appointments.
* Record and view treatment history per patient.
* Load from and save to CSV files for persistence.
* Menu-driven, easy-to-run CLI interface.

## 3. Project Structure

```
/var/www/html/Hospital-management
├─ doctors/             # doctor CSVs, optional doctor-specific helpers
├─ patients/            # patient CSVs, backups, or per-patient files
├─ main.c               # program entry + menu
├─ manager.c            # implementation of business logic (add/search/save...)
├─ manager.h            # struct definitions + public prototypes
├─ README.md            # this file
```

>

## 4. Prerequisites

* A UNIX-like environment (Linux, macOS, WSL on Windows)
* GCC (or clang) installed
* Basic shell (bash)

Recommended gcc flags for development:

```
gcc -std=c11 -Wall -Wextra -pedantic -g
```

## 5. Build & Run (step-by-step)

**1) Clone / copy project** to a local folder.

**2) Prepare data files (see section 6 for formats).** Create the `patients/` and `doctors/` directories (if not already present) and place CSV files there (example filenames used by the program below):

* `patients/patients.csv`
* `patients/appointments.csv`
* `doctors/doctors.csv` (optional)

**3) Build**

* Simple `gcc` command (single-step compile):

```bash
mkdir -p bin
gcc -std=c11 -Wall -Wextra -pedantic main.c manager.c -o bin/hpms
```

* Or using a `Makefile` (recommended for convenience). Example target:

```Makefile
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
SRC=main.c manager.c
OBJ=$(SRC:.c=.o)
BIN=bin/hpms

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN) *.o
```

Then run `make` at the project root.

**4) Run**

```
./bin/hpms
```

On start the program attempts to load CSV files. If none exist, it will start with an empty dataset and will create CSVs on exit (or when the save action is invoked).

## 6. Data files & CSV format

The program persists data as CSVs. Use UTF-8 plain text. Use the headers shown below — the program expects these columns (order matters unless you adapt the parser).

### patients/patients.csv

```
id,name,age,gender,address,phone,email
1,John Doe,34,Male,"12 Main St",+2348012345678,john@example.com
```

* `id` — integer unique patient id
* `name` — full name
* `age` — integer
* `gender` — text (Male/Female/Other)
* `address` — quoted if contains commas
* `phone` — string
* `email` — string

### patients/appointments.csv

```
appointment_id,patient_id,doctor_name,date,time,description,status
1001,1,Dr. Ada,2025-08-15,09:30,"Follow-up: high BP",BOOKED
```

* `appointment_id` — integer unique
* `patient_id` — integer referencing patients.id
* `doctor_name` — string
* `date` — YYYY-MM-DD
* `time` — HH\:MM (24h)
* `description` — short text about purpose or treatment
* `status` — BOOKED / CANCELLED / DONE

### (Optional) doctors/doctors.csv

```
doctor_id,name,specialty,phone,email
200,Dr. Ada,Cardiology,+2348000000000,ada@hospital.test
```

> The minimal program requires only `patients.csv` and `appointments.csv`. If the files don't exist they will be created on first save.

## 7. CLI menu and expected behavior

When you run `./bin/hpms`, you will see a menu similar to:

```
Hospital Patient Management System
1) Add Patient
2) Update Patient
3) Search Patient
4) Delete Patient
5) Book Appointment
6) View Appointments
7) View Treatment History
8) Save & Exit
Enter choice: _
```

Each option maps to a function in `manager.c` (see section 8). Inputs are interactive CLI prompts. Dates/times are not validated strictly by the example program — prefer `YYYY-MM-DD` and `HH:MM`.

## 8. Function reference (what each function does)

> This section lists the public functions you should find (or add) to `manager.c`/`manager.h`. If your function names differ, map them accordingly.

### Data loading & persistence

* `void loadDataFromCSV(const char *patientsPath, const char *appointmentsPath);
  `
  **Purpose:** Read `patients.csv` and `appointments.csv` into memory structures (dynamic arrays).
  **Inputs:** file paths.
  **Outputs:** fills global or passed `patientList` and `appointmentList`.
  **Side-effects:** allocates memory using `malloc`/`realloc`. Handle missing files by creating empty lists.

* `void saveDataToCSV(const char *patientsPath, const char *appointmentsPath);
  `
  **Purpose:** Write current in-memory arrays back to CSVs.
  **Inputs:** file paths.
  **Outputs:** writes files (overwrites or atomically replaces).
  **Side-effects:** flushes data to disk.

### Patient operations

* `int addPatient(struct Patient p);
  `
  **Purpose:** Add a new patient record.
  **Inputs:** a `Patient` struct (or interactive prompts inside the function).
  **Outputs:** returns newly assigned patient id or `-1` on error.
  **Side-effects:** appends to `patientList` (realloc if needed).

* `int updatePatient(int id, struct Patient newData);
  `
  **Purpose:** Update an existing patient by id.
  **Inputs:** patient id and new patient data.
  **Outputs:** 0 on success, -1 if not found.

* `struct Patient* findPatientById(int id);
  `
  **Purpose:** Locate a patient by id and return pointer or NULL.

* `int deletePatient(int id);
  `
  **Purpose:** Remove a patient from the list. Also optionally cascade-delete appointments for that patient.
  **Outputs:** 0 success, -1 not found.

* `int searchPatientsByName(const char *name, struct Patient **matches, int *matchCount);
  `
  **Purpose:** Find patients where `name` is a substring (case-insensitive).
  **Outputs:** an allocated array of matches (caller frees), and count.

### Appointment & treatment operations

* `int bookAppointment(struct Appointment a);
  `
  **Purpose:** Create and store a new appointment (checks that referenced patient exists).
  **Inputs:** `Appointment` struct with patient id and doctor/date/time/desc.
  **Outputs:** appointment\_id on success, -1 on error.

* `int cancelAppointment(int appointmentId);
  `
  **Purpose:** Cancel an appointment (marks `status = CANCELLED`).

* `void viewAppointments();
  `
  **Purpose:** Print all appointments (or accept filters like date/doctor/patient).

* `void viewAppointmentsByPatient(int patientId);
  `
  **Purpose:** Print appointments for a single patient (past and future).

* `void viewTreatmentHistory(int patientId);
  `
  **Purpose:** List treatments/appointments that include `description` for a patient. This is basically `viewAppointmentsByPatient` but formatted as treatment history.

### Utility functions

* `int generatePatientId();` — returns next available unique patient id (e.g., last id + 1).
* `int generateAppointmentId();` — same for appointments.
* `char* trim(char *s);` — remove whitespace.
* `char** splitCSVLine(const char *line, int *cols);` — simple CSV parser for a line (handles quoted fields minimally).
* `void freeAll();` — free all allocated memory before exit.

> **Memory note:** Whenever functions allocate memory that is returned to the caller (e.g., arrays of matches), add clear documentation who must free the memory and when.

## 9. Testing & sample session

### Sample test data (create these files before running):

**patients/patients.csv**

```
id,name,age,gender,address,phone,email
1,John Doe,34,Male,"12 Main St",+2348012345678,john@example.com
2,Jane Smith,28,Female,"34 Park Ave",+2348098765432,jane@example.com
```

**patients/appointments.csv**

```
appointment_id,patient_id,doctor_name,date,time,description,status
1001,1,Dr. Ada,2025-08-15,09:30,"Follow-up: BP",BOOKED
1002,2,Dr. Kalu,2025-08-16,11:00,"New patient consult",BOOKED
```

### Example run (manual):

1. Start: `./bin/hpms`
2. Choose `3` (Search Patient) → enter `Jane` → program prints Jane's record.
3. Choose `5` (Book Appointment) → enter patient id `1`, doctor name, date `2025-09-01`, time `10:00`, description `Checkup`.
4. Choose `6` (View Appointments) → see the new appointment.
5. Choose `8` (Save & Exit) → CSVs updated.

### Automated tests (suggested)

* Add a small test program or script that runs the program with input redirected from a file (bash `here-doc`) and checks output.
* Unit tests for `splitCSVLine`, `generatePatientId`, `findPatientById` can be added as separate `*_test.c` files compiled into a `tests` binary.

## 10. Troubleshooting (common issues)

* **Cannot open CSV files:** Check file paths and permissions. Running `./bin/hpms` from the repo root expects the patient CSV path used in code (relative paths).
* **Segfaults:** Likely from invalid memory access — check null pointers returned by `malloc`/`realloc` and that returned values from `findPatientById` are checked before use.
* **Line parsing oddities:** Basic CSV parser may not handle complex quoting or embedded newlines. Keep CSV lines simple.
* **Duplicate IDs:** If you edit CSVs manually, ensure `id`/`appointment_id` columns remain unique.

## 11. Extending the project (ideas for future work)

* Add a `Makefile` and CI checks.
* Replace CSV with a lightweight embedded DB (SQLite) for safer transactions.
* Add date/time validation and timezone support.
* Add role-based access (admin vs nurse vs doctor) and simple authentication.
* Add export to JSON and a REST API server.
* Implement unit tests and memory-leak checks (valgrind).

## 12. Coding conventions

* Target `C11` standard.
* Use `snake_case` for functions and variables.
* Document functions with short comments: purpose, params, return value, side effects.
* Free any heap memory you allocate.
