# Hospital Management System (C)

This is a simple Hospital Management System written in C.  
It manages **patients**, their **treatments**, and **appointments**.

---

## 📂 Project Structure

Hospital-management/
│── appointments/ # Appointment-related functions
│── patients/ # Patient-related functions
│── treatments/ # Treatment-related functions
│── manager.c # General/common functions
│── manager.h # Shared function prototypes & structs
│── main.c # Entry point of the program
│── Makefile # Build automation
│── README.md # This file
│── STUCTURE.md # Project design and data structure notes

---

## 🔧 Compilation

We use the `Makefile` to compile all modules into one executable.

To compile:

```bash

Run: make

This will produce an executable called: ***hpms***

▶️ Running the Program

Once compiled, run:

./hpms

📌 Function Prototypes

All major functions are declared in manager.h.

// Displays all patients

void displayPatients(void);

// Displays all treatments
void displayTreatments(void);

// Displays all appointments
void displayAppointments(void);

🛠 Steps to Add a New Module

Create a new folder for the module (e.g., billing/).

Inside it, create .c and .h files for the module.

Add function prototypes to manager.h.

Include the new .c file in the Makefile under the compilation list.

Call the new module’s function in main.c if needed.

📞 Example Usage
When running the program, you can choose options such as:

=== Hospital Management System ===
1. Manage Patients
2. Manage Treatments
3. Manage Appointments
4. Exit
Enter your choice:

⚠️ Notes

Make sure you have gcc installed:

sudo apt install gcc

