/**
 * calculator.c
 * 
 * Implementation of calculator logic functions.
 * This file contains the business logic separated from the GUI.
 */

#include <stdlib.h>
#include <errno.h>
#include "../include/calculator.h"

/**
 * Calculates the sum of two double precision floating-point numbers.
 * 
 * @param a The first number to add
 * @param b The second number to add
 * @return The sum of a and b
 */
double calculate_sum(double a, double b) {
    return a + b;
}

/**
 * Parses a string and converts it to a double.
 * 
 * @param str The string to parse
 * @param result Pointer to store the parsed result
 * @return 1 if parsing was successful, 0 if parsing failed
 */
int parse_number(const char* str, double* result) {
    char* endptr;
    errno = 0;
    
    // Attempt to parse the string as a double
    *result = strtod(str, &endptr);
    
    // Check for parsing errors
    if (errno != 0 || endptr == str || *endptr != '\0') {
        return 0; // Parsing failed
    }
    
    return 1; // Parsing succeeded
}
