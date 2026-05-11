# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I include
LDFLAGS = -mwindows -lm

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Output executable
TARGET = calc.exe

# Source files
SOURCES = $(SRC_DIR)/calc.c $(SRC_DIR)/calculator.c

# Object files
OBJECTS = $(OBJ_DIR)/calc.o $(OBJ_DIR)/calculator.o

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo Build complete: $(TARGET)

# Clean build artifacts
clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(TARGET)
	@echo Clean complete

# Rebuild from scratch
rebuild: clean all

# Run the application
run: $(TARGET)
	@$(TARGET)

.PHONY: all clean rebuild run
