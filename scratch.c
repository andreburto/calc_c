#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
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
    printf("Back to float + 1: %g\n", add_one);
    
    return 0;
}