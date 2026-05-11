#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    double value = 123.456;
    char buffer[64];

    printf("Starting %.f\n", value);
    
    // Convert to string with fixed decimal places
    int len = snprintf(buffer, sizeof(buffer), "%f", value);
    printf("Value as string: %s\n", buffer);
    printf("Length of string: %d\n", len);
    
    // Find decimal point and count digits after it
    char* decimal_pos = strchr(buffer, '.');
    int decimal_places = 0;
    printf("Decimal position in string: %s\n", decimal_pos);
    printf("Decimal position in char: %c\n", *decimal_pos);
    if (decimal_pos) {
        decimal_pos++;
        while (*decimal_pos) {
            if (*decimal_pos >= '0' && *decimal_pos <= '9') {
                printf("Decimal digit: %c\n", *decimal_pos);
                decimal_places++;
            }
            decimal_pos++;
        }
    }
    
    printf("Decimal places counted: %d\n", decimal_places);
    
    return 0;
}