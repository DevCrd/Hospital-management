CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
TARGET  = hpms

# Source files from all modules
SOURCES = main.c manager.c \
          patients/patients.c \
          appointments/appointments.c \
          treatments/treatments.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Pattern rule for object files
%.o: %.c manager.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET) $(TEST_TARGET)
