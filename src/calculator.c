/**
 * calculator.c
 * 
 * Implementation of calculator logic functions.
 * This file contains the business logic separated from the GUI.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/calculator.h"

/**
 * Initializes the calculator state to default values.
 * 
 * @param state Pointer to the calculator state structure
 */
void init_calculator(CalculatorState* state) {
    state->current_value = 0;
    state->stored_value = 0;
    state->operation = OP_NONE;
    state->has_decimal = 0;
    state->entering_new = 1;
    state->digit_count = 0;
}

/**
 * Handles a digit button press (0-9).
 * Appends the digit to the current value if limit not exceeded.
 * 
 * @param state Pointer to the calculator state structure
 * @param digit The digit pressed (0-9)
 * @return 1 if digit was accepted, 0 if maximum digits reached
 */
int handle_digit(CalculatorState* state, int digit) {
    // Check if we're at the maximum digit limit (9 digits, not including decimal)
    if (state->digit_count >= 9) {
        return 0; // Cannot add more digits
    }
    
    // If we're entering a new number, reset the current value
    if (state->entering_new) {
        state->current_value = 0.0;
        state->entering_new = 0;
        state->digit_count = 0;
        state->has_decimal = 0;
    }
    
    // Append the digit to the current value
    if (state->has_decimal) {
        char buffer[32];        
        snprintf(buffer, sizeof(buffer), "%g", state->current_value);

        if (!strchr(buffer, '.')) {
            // If there's no decimal point in the string, add one
            strncat(buffer, ".", sizeof(buffer) - strlen(buffer) - 1);
        }

        // Append the new digit to the string
        strncat(buffer, (char[]){(char)('0' + digit), '\0'}, sizeof(buffer) - strlen(buffer) - 1);
        state->current_value = strtod(buffer, NULL);
        (void)malloc(strlen(buffer) + 1); // Prevent optimization of buffer
    } else {
        // For integer part, multiply by 10 and add digit
        state->current_value = state->current_value * 10.0 + digit;
    }
    state->digit_count++;
    
    return 1; // Digit accepted
}

/**
 * Handles decimal point button press.
 * 
 * @param state Pointer to the calculator state structure
 * @return 1 if decimal was accepted, 0 if already has decimal
 */
int handle_decimal(CalculatorState* state) {
    // If already has decimal point, don't add another
    if (state->has_decimal) {
        return 0;
    }
    
    // If we're entering a new number, reset the current value
    if (state->entering_new) {
        state->current_value = 0.0;
        state->entering_new = 0;
        state->digit_count = 0;
    }
    
    state->has_decimal = 1;
    return 1;
}

/**
 * Handles an operation button press (+, -, *, /, %, ^).
 * If there's a pending operation, calculates the result first.
 * 
 * @param state Pointer to the calculator state structure
 * @param op The operation to perform
 */
void handle_operation(CalculatorState* state, Operation op) {
    // If there's a pending operation and we're not entering a new number,
    // calculate the result first
    if (state->operation != OP_NONE && !state->entering_new) {
        double result;
        if (perform_calculation(state->stored_value, state->current_value, 
                               state->operation, &result)) {
            state->current_value = result;
        }
        // If calculation failed (e.g., division by zero), keep current value
    }
    
    // Store the current value and set the new operation
    state->stored_value = state->current_value;
    state->operation = op;
    state->entering_new = 1;
    state->digit_count = 0;
    state->has_decimal = 0;
}

/**
 * Handles the equals button press.
 * Performs the pending calculation and displays the result.
 * 
 * @param state Pointer to the calculator state structure
 * @param error_msg Buffer to store error message if division by zero occurs
 * @param error_msg_size Size of the error message buffer
 * @return 1 if calculation succeeded, 0 if error occurred (e.g., division by zero)
 */
int handle_equals(CalculatorState* state, char* error_msg, int error_msg_size) {
    // If there's a pending operation, calculate the result
    if (state->operation != OP_NONE) {
        double result;
        if (!perform_calculation(state->stored_value, state->current_value, 
                                state->operation, &result)) {
            // Calculation error (division by zero or modulus by zero)
            strncpy(error_msg, "Error: Division or modulus by zero", error_msg_size - 1);
            error_msg[error_msg_size - 1] = '\0';
            state->operation = OP_NONE;
            state->entering_new = 1;
            state->digit_count = 0;
            state->has_decimal = 0;
            return 0;
        }
        
        // Update the current value with the result
        state->current_value = result;
        state->operation = OP_NONE;
    }
    
    // Mark that we're ready to enter a new number
    state->entering_new = 1;
    state->digit_count = 0;
    state->has_decimal = 0;
    
    return 1; // Success
}

/**
 * Handles the clear button press.
 * Resets the calculator to initial state.
 * 
 * @param state Pointer to the calculator state structure
 */
void handle_clear(CalculatorState* state) {
    init_calculator(state);
}

/**
 * Gets the current display value as a string.
 * 
 * @param state Pointer to the calculator state structure
 * @param buffer Buffer to store the display string
 * @param buffer_size Size of the buffer
 */
void get_display_string(const CalculatorState* state, char* buffer, int buffer_size) {
    // Check if the value is effectively an integer
    if (state->current_value == (double)((long long)state->current_value) && !state->has_decimal) {
        // Display as integer if no fractional part and not entering decimal
        snprintf(buffer, buffer_size, "%.0f", state->current_value);
    } else {
        // Display as floating-point, removing trailing zeros
        snprintf(buffer, buffer_size, "%.10f", state->current_value);
        
        // Remove trailing zeros after decimal point
        char* decimal_point = strchr(buffer, '.');
        if (decimal_point) {
            char* end = buffer + strlen(buffer) - 1;
            while (end > decimal_point && *end == '0') {
                *end = '\0';
                end--;
            }
            // If we removed all digits after decimal, remove decimal too (unless entering decimal)
            if (end == decimal_point && !state->has_decimal) {
                *end = '\0';
            }
        }
    }
    
    // If has decimal but no digits after it yet, add the decimal point
    if (state->has_decimal && !strchr(buffer, '.')) {
        strncat(buffer, ".", buffer_size - strlen(buffer) - 1);
    }
}

/**
 * Performs the actual calculation based on the operation.
 * 
 * @param value1 First operand
 * @param value2 Second operand
 * @param op Operation to perform
 * @param result Pointer to store the result
 * @return 1 if calculation succeeded, 0 if error occurred (e.g., division by zero)
 */
int perform_calculation(double value1, double value2, Operation op, double* result) {
    switch (op) {
        case OP_ADD:
            *result = value1 + value2;
            break;
            
        case OP_SUBTRACT:
            *result = value1 - value2;
            break;
            
        case OP_MULTIPLY:
            *result = value1 * value2;
            break;
            
        case OP_DIVIDE:
            // Check for division by zero
            if (value2 == 0.0) {
                return 0; // Error: division by zero
            }
            *result = value1 / value2;
            break;
            
        case OP_MODULUS:
            // Check for modulus by zero
            if (value2 == 0.0) {
                return 0; // Error: modulus by zero
            }
            *result = fmod(value1, value2);
            break;
            
        case OP_POWER:
            *result = pow(value1, value2);
            break;
            
        case OP_NONE:
            *result = value1;
            break;
            
        default:
            *result = value1;
            break;
    }
    
    return 1; // Success
}
