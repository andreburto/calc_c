# calc_c

## Rules

- This is a C program that calculates the sum of two numbers.
- This uses `windows.h` to create a simple GUI for input and output.
- Document the code with comments to explain the functionality of each part of the program.
- The program should be structured in a way that separates the GUI code from the logic for calculating the sum.
- The main file should be named `calc.c` and should include a `main` function that initializes the GUI and handles user interactions.
- Program files go in the `src` directory, and header files go in the `include` directory. Test files go in the `tests` directory.
- All errors should be handled gracefully, with appropriate error messages displayed to the user in a message box only.

## Workflow

- Run the executable to open the GUI.
- The program should show two input fields for the numbers and a button to perform the calculation.
- Fill in the input fields with the numbers you want to sum.
- When the button is clicked, the program should read the values from the input fields, calculate the sum, and only display the result in the field below the button.
- The program should handle invalid input gracefully, showing an error message box if the input is not a valid number.
- If is an error, clear the answer field and show the error message in a message box with the title "Error".

## Design

- The GUI background should be yellow, and the text should be black for good contrast.
- The input fields should be clearly labeled, and the button should be prominently placed for easy access.
- Label the input fields as "Number 1" and "Number 2", and the button should be labeled "Calculate".
- Label background color of the GUI should be yellow, and the text color should be black for good contrast.
- The result should be displayed in a message box with the title "Result" and the content showing the sum of the two numbers. If there is an error, the message box should have the title "Error" and display an appropriate error message.