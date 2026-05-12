#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    char new_digit = '5';
    double value = 123.456;
    char buffer[64];

    printf("Starting %g\n", value);
    
    // Convert to string with fixed decimal places
    int len = snprintf(buffer, sizeof(buffer), "%g", value);
    float back_to_float = strtof(buffer, NULL);
    printf("Value as string: %s\n", buffer);
    printf("Length of string: %d\n", len);
    printf("Back to float: %g\n", back_to_float);

    float add_one = back_to_float + 1.01f;
    printf("Back to float + 1.01: %g\n", add_one);

    len = snprintf(buffer, sizeof(buffer), "%g", add_one);
    printf("Add one as string: %s\n", buffer);
    
    // Append new digit to the end of the number
    // This is a hacky way to do it, but it works for testing
    if (strchr(buffer, '.')) {
        // If there's a decimal point, just append the digit
        strncat(buffer, &new_digit, 1);
    } else {
        // If there's no decimal point, add one and then append the digit
        float new_value = back_to_float * 10 + (new_digit - '0');
        snprintf(buffer, sizeof(buffer), "%g", new_value);
    }

    printf("Value after appending digit '%c': %s\n", new_digit, buffer);

    char* clr_buffer = buffer;
    while (*clr_buffer) {
        *clr_buffer = '\0';
        clr_buffer++;
    }

    printf("Buffer after clearing: '%s'\n", buffer);

    return 0;
}