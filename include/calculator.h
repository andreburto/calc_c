#ifndef CALCULATOR_H
#define CALCULATOR_H

/**
 * calculator.h
 * 
 * Header file containing the calculator logic interface.
 * This separates the calculation logic from the GUI implementation.
 */

// Operation types for the calculator
typedef enum {
    OP_NONE,        // No operation selected
    OP_ADD,         // Addition
    OP_SUBTRACT,    // Subtraction
    OP_MULTIPLY,    // Multiplication
    OP_DIVIDE,      // Division
    OP_MODULUS,     // Modulus operation
    OP_POWER        // Exponentiation
} Operation;

// Calculator state structure
typedef struct {
    double current_value;   // Current number being entered or result
    double stored_value;    // Previously stored number for operation
    Operation operation;    // Current operation pending
    int has_decimal;        // Flag for whether we're entering decimals
    int entering_new;       // Flag indicating if we're starting a new number entry
    int digit_count;        // Number of digits entered (max 9, not including decimal point)
} CalculatorState;

/**
 * Initializes the calculator state.
 * 
 * @param state Pointer to the calculator state structure
 */
void init_calculator(CalculatorState* state);

/**
 * Handles a digit button press (0-9).
 * 
 * @param state Pointer to the calculator state structure
 * @param digit The digit pressed (0-9)
 * @return 1 if digit was accepted, 0 if maximum digits reached
 */
int handle_digit(CalculatorState* state, int digit);

/**
 * Handles decimal point button press.
 * 
 * @param state Pointer to the calculator state structure
 * @return 1 if decimal was accepted, 0 if already has decimal
 */
int handle_decimal(CalculatorState* state);

/**
 * Handles an operation button press (+, -, *, /, %, ^).
 * 
 * @param state Pointer to the calculator state structure
 * @param op The operation to perform
 */
void handle_operation(CalculatorState* state, Operation op);

/**
 * Handles the equals button press.
 * 
 * @param state Pointer to the calculator state structure
 * @param error_msg Buffer to store error message if division by zero occurs
 * @param error_msg_size Size of the error message buffer
 * @return 1 if calculation succeeded, 0 if error occurred (e.g., division by zero)
 */
int handle_equals(CalculatorState* state, char* error_msg, int error_msg_size);

/**
 * Handles the clear button press.
 * 
 * @param state Pointer to the calculator state structure
 */
void handle_clear(CalculatorState* state);

/**
 * Handles tip calculation buttons (10% or 20%).
 * Multiplies the current value by the tip multiplier.
 * 
 * @param state Pointer to the calculator state structure
 * @param multiplier The multiplier to apply (e.g., 1.1 for 10%, 1.2 for 20%)
 */
void handle_tip(CalculatorState* state, double multiplier);

/**
 * Gets the current display value as a string.
 * 
 * @param state Pointer to the calculator state structure
 * @param buffer Buffer to store the display string
 * @param buffer_size Size of the buffer
 */
void get_display_string(const CalculatorState* state, char* buffer, int buffer_size);

/**
 * Performs the actual calculation based on the operation.
 * 
 * @param value1 First operand
 * @param value2 Second operand
 * @param op Operation to perform
 * @param result Pointer to store the result
 * @return 1 if calculation succeeded, 0 if error occurred (e.g., division by zero)
 */
int perform_calculation(double value1, double value2, Operation op, double* result);

#endif // CALCULATOR_H
