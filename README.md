# calc_c

A simple Windows GUI calculator application written in C that adds two numbers. This is an experiment using LLMs to write Windows executables.

## Description

This is a C program that uses the Windows API (`windows.h`) to create a graphical user interface for calculating the sum of two numbers. The program features a clean separation between the GUI code and the calculation logic.

## Features

- Simple and intuitive GUI with two input fields
- Calculate button to perform the addition
- Input validation with error messages for invalid numbers
- Result displayed in a message box
- Clean code structure with separated concerns

## Project Structure

```
calc_c/
├── include/          # Header files
│   └── calculator.h  # Calculator logic interface
├── src/              # Source files
│   ├── calc.c        # Main GUI application
│   └── calculator.c  # Calculator logic implementation
├── tests/            # Test files (if any)
└── README.md         # This file
```

## Prerequisites

- Windows operating system
- GCC compiler (MinGW-w64 recommended)
- Make utility (optional, for using Makefile)

## Building the Project

### Using Make

```bash
make
```

This will compile the project and create `calc.exe` in the project root directory.

### Manual Compilation

```bash
gcc -o calc.exe src/calc.c src/calculator.c -I include -mwindows
```

### Clean Build Artifacts

```bash
make clean
```

## Running the Application

After building, simply run the executable:

```bash
./calc.exe
```

Or double-click `calc.exe` in Windows Explorer.

## Usage

1. Enter the first number in the "Number 1" field
2. Enter the second number in the "Number 2" field
3. Click the "Calculate Sum" button
4. The result will be displayed in a message box

The program validates input and will show an error message if invalid numbers are entered.

## Development

### Code Structure

The project follows a modular design:

- **GUI Layer** (`src/calc.c`): Handles all Windows API calls and user interface
- **Logic Layer** (`src/calculator.c`): Contains pure calculation and parsing functions
- **Interface** (`include/calculator.h`): Defines the contract between GUI and logic

This separation makes the code easier to test, maintain, and extend.

## License

This project is provided as-is for educational purposes.
