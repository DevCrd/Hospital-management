CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
TARGET  = hpms

# Source files from all modules
SOURCES = main.c manager.c \
          patients/patients.c \
          appointments/appointments.c \
          treatments/treatments.c

OBJECTS = $(SOURCES:.c=.o)

# Test sources
TEST_SOURCES = tests/test_data.c manager.c \
               patients/patients.c \
               appointments/appointments.c \
               treatments/treatments.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
TEST_TARGET  = hpms_test

.PHONY: all clean run test seed

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Pattern rule for object files
%.o: %.c manager.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# Test build and run
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(TEST_TARGET)

# Seed dummy data into CSVs
seed:
	@echo "Seeding patients.csv..."
	@echo "P001,John Doe,35,555-1234" > patients.csv
	@echo "P002,Jane Smith,29,555-5678" >> patients.csv
	@echo "Seeding treatments.csv..."
	@echo "T001,P001,Physical Therapy" > treatments.csv
	@echo "T002,P002,Blood Test" >> treatments.csv
	@echo "Seeding appointments.csv..."
	@echo "A001,P001,2025-08-14,09:00,Dr. Brown" > appointments.csv
	@echo "A002,P002,2025-08-15,11:00,Dr. White" >> appointments.csv
	@echo "Dummy data seeded successfully."

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET)
