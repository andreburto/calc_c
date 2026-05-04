#ifndef CALCULATOR_H
#define CALCULATOR_H

/**
 * calculator.h
 * 
 * Header file containing the calculator logic interface.
 * This separates the calculation logic from the GUI implementation.
 */

/**
 * Calculates the sum of two double precision floating-point numbers.
 * 
 * @param a The first number to add
 * @param b The second number to add
 * @return The sum of a and b
 */
double calculate_sum(double a, double b);

/**
 * Parses a string and converts it to a double.
 * 
 * @param str The string to parse
 * @param result Pointer to store the parsed result
 * @return 1 if parsing was successful, 0 if parsing failed
 */
int parse_number(const char* str, double* result);

#endif // CALCULATOR_H
