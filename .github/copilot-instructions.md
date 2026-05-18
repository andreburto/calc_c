# calc_c

## Rules

- This is a C program that calculates the sum of two numbers.
- This uses `windows.h` to create a simple GUI for input and output.
- Document the code with comments to explain the functionality of each part of the program.
- The program should be structured in a way that separates the GUI code from the logic for calculating the sum.
- The main file should be named `calc.c` and should include a `main` function that initializes the GUI and handles user interactions.
- Program files go in the `src` directory, and header files go in the `include` directory. Test files go in the `tests` directory.
- All errors should be handled gracefully, with appropriate error messages displayed to the user in a message box only.

## Design

- The GUI background should be yellow, and the text should be black for good contrast.

The layout should look like this:

```
+---------------+
| [number here] |
+---+---+---+---+
| 7 | 8 | 9 | + |
+---+---+---+---+
| 4 | 5 | 6 | - |
+---+---+---+---+
| 1 | 2 | 3 | * |
+---+---+---+---+
|   0   | . | / |
+---+---+---+---+
| C | = | % | ^ | 
+---+---+---+---+
|TIP 10%|TIP 20%|
+-------+-------+
| [text]| TIP % |
+---------------+ 
```

## Workflow

- Run the executable to open the GUI.
- The program is a floating-point calculator that allows the user to input a number, select an operation (addition, subtraction, multiplication, division), and then input another number to perform the calculation.
- The user can click the "C" button to clear the input and start a new calculation.
- The "^" button will perform exponentiation, and the "%" button will perform modulus operation.
- The result of the calculation will be displayed in the input field after the user clicks the "=" button.
- The program should handle division by zero and other invalid operations gracefully, displaying an appropriate error message in a message box.
- The maximum number of digits that can be input should be limited to 9 to prevent overflow issues, not including the decimal point.
- Pressing the "." button should allow the user to input a decimal point for floating-point numbers, but only one decimal point should be allowed per number.
- The "TIP 10%" multiplies the current value by 1.1, and the "TIP 20%" button will multiply the current value by 1.2, allowing the user to quickly calculate tips for a bill.
- The [text] field allows the user to input a custom tip percentage. When the user clicks the "TIP %" button, it will read the value from the [text] field, convert it to a multiplier (e.g., 15% becomes 1.15), and apply it to the current value. Ony accest 1 to 99 for the custom tip percentage.
- Numbers show up in a read-only input field, and the user can only interact with the buttons to input numbers and operations. That field is in the top row of the layout.