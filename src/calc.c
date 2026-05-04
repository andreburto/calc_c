/**
 * calc.c
 * 
 * Main GUI application for a simple calculator that adds two numbers.
 * This program uses the Windows API (windows.h) to create a GUI with
 * two input fields and a calculate button.
 */

#include <windows.h>
#include <stdio.h>
#include "../include/calculator.h"

// Window dimensions
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 280

// Control IDs
#define ID_TEXTBOX1 101
#define ID_TEXTBOX2 102
#define ID_BUTTON_CALCULATE 103
#define ID_RESULT_LABEL 104

// Global handles for controls
HWND hTextBox1;
HWND hTextBox2;
HWND hButtonCalculate;
HWND hLabel1;
HWND hLabel2;
HWND hResultLabel;

// Yellow background brush for the window
HBRUSH hYellowBrush;

// Font for result label
HFONT hResultFont;

/**
 * Window procedure callback function.
 * Handles all messages sent to the window.
 * 
 * @param hwnd Handle to the window
 * @param msg The message identifier
 * @param wParam Additional message parameter
 * @param lParam Additional message parameter
 * @return Result of message processing
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Create yellow background brush
            hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
            
            // Create font for result label
            hResultFont = CreateFont(
                20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial"
            );
            
            // Create label for first input
            hLabel1 = CreateWindow("STATIC", "Number 1:",
                        WS_VISIBLE | WS_CHILD,
                        20, 20, 120, 20,
                        hwnd, NULL, NULL, NULL);
            
            // Create first input textbox
            hTextBox1 = CreateWindow("EDIT", "",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                                    150, 20, 200, 25,
                                    hwnd, (HMENU)ID_TEXTBOX1, NULL, NULL);
            
            // Create label for second input
            hLabel2 = CreateWindow("STATIC", "Number 2:",
                        WS_VISIBLE | WS_CHILD,
                        20, 60, 120, 20,
                        hwnd, NULL, NULL, NULL);
            
            // Create second input textbox
            hTextBox2 = CreateWindow("EDIT", "",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                                    150, 60, 200, 25,
                                    hwnd, (HMENU)ID_TEXTBOX2, NULL, NULL);
            
            // Create calculate button
            hButtonCalculate = CreateWindow("BUTTON", "Calculate",
                                           WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                           120, 110, 150, 35,
                                           hwnd, (HMENU)ID_BUTTON_CALCULATE, NULL, NULL);
            
            // Create result display field
            hResultLabel = CreateWindow("STATIC", "",
                                       WS_VISIBLE | WS_CHILD | SS_CENTER,
                                       20, 160, 350, 30,
                                       hwnd, (HMENU)ID_RESULT_LABEL, NULL, NULL);
            
            // Set font for result label
            SendMessage(hResultLabel, WM_SETFONT, (WPARAM)hResultFont, TRUE);
            break;
        }
        
        case WM_COMMAND: {
            // Handle button click
            if (LOWORD(wParam) == ID_BUTTON_CALCULATE) {
                char buffer1[256];
                char buffer2[256];
                double num1, num2, result;
                
                // Get text from first textbox
                GetWindowText(hTextBox1, buffer1, sizeof(buffer1));
                
                // Get text from second textbox
                GetWindowText(hTextBox2, buffer2, sizeof(buffer2));
                
                // Parse the first number
                if (!parse_number(buffer1, &num1)) {
                    // Clear the answer field
                    SetWindowText(hResultLabel, "");
                    // Show error message box
                    MessageBox(hwnd, 
                              "Invalid input for the first number.\nPlease enter a valid number.",
                              "Error",
                              MB_OK | MB_ICONERROR);
                    return 0;
                }
                
                // Parse the second number
                if (!parse_number(buffer2, &num2)) {
                    // Clear the answer field
                    SetWindowText(hResultLabel, "");
                    // Show error message box
                    MessageBox(hwnd,
                              "Invalid input for the second number.\nPlease enter a valid number.",
                              "Error",
                              MB_OK | MB_ICONERROR);
                    return 0;
                }
                
                // Calculate the sum using the calculator logic
                result = calculate_sum(num1, num2);
                
                // Format and display the result in the result field
                char resultMessage[512];
                sprintf(resultMessage, "%.2f + %.2f = %.2f", num1, num2, result);
                SetWindowText(hResultLabel, resultMessage);
}
            break;
        }
        
        case WM_CTLCOLORSTATIC: {
            // Set yellow background and black text for labels
            HDC hdcStatic = (HDC)wParam;
            SetTextColor(hdcStatic, RGB(0, 0, 0));  // Black text
            SetBkColor(hdcStatic, RGB(255, 255, 0));  // Yellow background
            return (LRESULT)hYellowBrush;
        }
        
        case WM_DESTROY: {
            // Clean up the yellow brush
            if (hYellowBrush) {
                DeleteObject(hYellowBrush);
            }
            // Clean up the font
            if (hResultFont) {
                DeleteObject(hResultFont);
            }
            // Post quit message when window is closed
            PostQuitMessage(0);
            return 0;
        }
        
        default:
            // Default message handling
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    
    return 0;
}

/**
 * Main entry point for the Windows GUI application.
 * 
 * @param hInstance Handle to the current instance of the application
 * @param hPrevInstance Handle to the previous instance (always NULL in Win32)
 * @param lpCmdLine Command line arguments
 * @param nCmdShow How the window should be displayed initially
 * @return Exit code
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "CalculatorWindowClass";
    
    // Register the window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));  // Yellow background
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error",
                  MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Extended window style
        CLASS_NAME,                     // Window class name
        "Simple Calculator",            // Window title
        WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, // Window style (fixed size)
        CW_USEDEFAULT, CW_USEDEFAULT,  // Position
        WINDOW_WIDTH, WINDOW_HEIGHT,    // Size
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );
    
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error",
                  MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Show the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}
