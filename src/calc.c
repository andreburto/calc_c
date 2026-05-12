/**
 * calc.c
 * 
 * Main GUI application for a floating-point calculator with basic and advanced operations.
 * This program uses the Windows API (windows.h) to create a GUI with
 * a button grid layout for a calculator.
 */

#include <windows.h>
#include <stdio.h>
#include "../include/calculator.h"

// Window dimensions
#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 435

// Button dimensions
#define BUTTON_WIDTH 70
#define BUTTON_HEIGHT 50
#define BUTTON_MARGIN 5
#define BUTTON_START_X 10
#define BUTTON_START_Y 80

// Control IDs
#define ID_DISPLAY 100
#define ID_BUTTON_0 101
#define ID_BUTTON_1 102
#define ID_BUTTON_2 103
#define ID_BUTTON_3 104
#define ID_BUTTON_4 105
#define ID_BUTTON_5 106
#define ID_BUTTON_6 107
#define ID_BUTTON_7 108
#define ID_BUTTON_8 109
#define ID_BUTTON_9 110
#define ID_BUTTON_ADD 111
#define ID_BUTTON_SUBTRACT 112
#define ID_BUTTON_MULTIPLY 113
#define ID_BUTTON_DIVIDE 114
#define ID_BUTTON_EQUALS 115
#define ID_BUTTON_CLEAR 116
#define ID_BUTTON_DECIMAL 117
#define ID_BUTTON_MODULUS 118
#define ID_BUTTON_POWER 119

// Global handles for controls
HWND hDisplay;          // Display field at the top
HWND hButtons[20];      // Array for all buttons

// Yellow background brush for the window
HBRUSH hYellowBrush;

// Font for display and buttons
HFONT hDisplayFont;
HFONT hButtonFont;

// Calculator state
CalculatorState calcState;

/**
 * Updates the display with the current calculator value.
 * 
 * @param hwnd Handle to the main window
 */
void update_display(HWND hwnd) {
    char buffer[32];
    get_display_string(&calcState, buffer, sizeof(buffer));
    SetWindowText(hDisplay, buffer);
}

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
            // Initialize calculator state
            init_calculator(&calcState);
            
            // Create yellow background brush
            hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
            
            // Create font for display
            hDisplayFont = CreateFont(
                32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial"
            );
            
            // Create font for buttons
            hButtonFont = CreateFont(
                20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial"
            );
            
            // Create display field (read-only)
            hDisplay = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT", "0",
                WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_READONLY,
                BUTTON_START_X, 20,
                BUTTON_WIDTH * 4 + BUTTON_MARGIN * 3, 45,
                hwnd, (HMENU)ID_DISPLAY, NULL, NULL
            );
            SendMessage(hDisplay, WM_SETFONT, (WPARAM)hDisplayFont, TRUE);
            
            // Button layout coordinates (row, col) for 5x4 grid
            // Row 0: 7, 8, 9, +
            // Row 1: 4, 5, 6, -
            // Row 2: 1, 2, 3, *
            // Row 3: 0 (double width), ., /
            // Row 4: C, =, %, ^
            
            int buttonIndex = 0;
            
            // Row 0: 7, 8, 9, +
            int row = 0;
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "7",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 0 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_7, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "8",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 1 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_8, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "9",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 2 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_9, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "+",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 3 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_ADD, NULL, NULL);
            
            // Row 1: 4, 5, 6, -
            row = 1;
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "4",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 0 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_4, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "5",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 1 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_5, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "6",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 2 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_6, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "-",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 3 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_SUBTRACT, NULL, NULL);
            
            // Row 2: 1, 2, 3, *
            row = 2;
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "1",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 0 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_1, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "2",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 1 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_2, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "3",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 2 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_3, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "*",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 3 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_MULTIPLY, NULL, NULL);
            
            // Row 3: 0 (double width), ., /
            row = 3;
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "0",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 0 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH * 2 + BUTTON_MARGIN, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_0, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", ".",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 2 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_DECIMAL, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "/",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 3 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_DIVIDE, NULL, NULL);
            
            // Row 4: C, =, %, ^
            row = 4;
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "C",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 0 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_CLEAR, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "=",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 1 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_EQUALS, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "%",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 2 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_MODULUS, NULL, NULL);
            
            hButtons[buttonIndex++] = CreateWindow("BUTTON", "^",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                BUTTON_START_X + 3 * (BUTTON_WIDTH + BUTTON_MARGIN),
                BUTTON_START_Y + row * (BUTTON_HEIGHT + BUTTON_MARGIN),
                BUTTON_WIDTH, BUTTON_HEIGHT,
                hwnd, (HMENU)ID_BUTTON_POWER, NULL, NULL);
            
            // Set font for all buttons
            for (int i = 0; i < buttonIndex; i++) {
                SendMessage(hButtons[i], WM_SETFONT, (WPARAM)hButtonFont, TRUE);
            }
            
            break;
        }
        
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            // Handle digit buttons (0-9)
            if (wmId >= ID_BUTTON_0 && wmId <= ID_BUTTON_9) {
                int digit = wmId - ID_BUTTON_0;
                if (handle_digit(&calcState, digit)) {
                    update_display(hwnd);
                } else {
                    // Maximum digits reached
                    MessageBox(hwnd, 
                              "Maximum number of digits (9) reached.",
                              "Error",
                              MB_OK | MB_ICONWARNING);
                }
            }
            // Handle operation buttons
            else if (wmId == ID_BUTTON_ADD) {
                handle_operation(&calcState, OP_ADD);
                update_display(hwnd);
            }
            else if (wmId == ID_BUTTON_SUBTRACT) {
                handle_operation(&calcState, OP_SUBTRACT);
                update_display(hwnd);
            }
            else if (wmId == ID_BUTTON_MULTIPLY) {
                handle_operation(&calcState, OP_MULTIPLY);
                update_display(hwnd);
            }
            else if (wmId == ID_BUTTON_DIVIDE) {
                handle_operation(&calcState, OP_DIVIDE);
                update_display(hwnd);
            }
            else if (wmId == ID_BUTTON_MODULUS) {
                handle_operation(&calcState, OP_MODULUS);
                update_display(hwnd);
            }
            else if (wmId == ID_BUTTON_POWER) {
                handle_operation(&calcState, OP_POWER);
                update_display(hwnd);
            }
            // Handle decimal button
            else if (wmId == ID_BUTTON_DECIMAL) {
                if (handle_decimal(&calcState)) {
                    update_display(hwnd);
                } else {
                    // Already has decimal point
                    MessageBox(hwnd, 
                              "Number already has a decimal point.",
                              "Error",
                              MB_OK | MB_ICONWARNING);
                }
            }
            // Handle equals button
            else if (wmId == ID_BUTTON_EQUALS) {
                char error_msg[256];
                if (!handle_equals(&calcState, error_msg, sizeof(error_msg))) {
                    // Error occurred (e.g., division by zero)
                    MessageBox(hwnd, error_msg, "Error", MB_OK | MB_ICONERROR);
                }
                update_display(hwnd);
            }
            // Handle clear button
            else if (wmId == ID_BUTTON_CLEAR) {
                handle_clear(&calcState);
                update_display(hwnd);
            }
            
            break;
        }
        
        case WM_CTLCOLOREDIT: {
            // Set yellow background and black text for the display
            HDC hdcEdit = (HDC)wParam;
            SetTextColor(hdcEdit, RGB(0, 0, 0));    // Black text
            SetBkColor(hdcEdit, RGB(255, 255, 0));  // Yellow background
            return (LRESULT)hYellowBrush;
        }
        
        case WM_DESTROY: {
            // Clean up the yellow brush
            if (hYellowBrush) {
                DeleteObject(hYellowBrush);
            }
            // Clean up the fonts
            if (hDisplayFont) {
                DeleteObject(hDisplayFont);
            }
            if (hButtonFont) {
                DeleteObject(hButtonFont);
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

    // AllocConsole(); // Allocate a console for debugging output
    // freopen("CONOUT$", "w", stdout); // Redirect stdout to the console
    // freopen("CONOUT$", "w", stderr); // Redirect stderr to the console                    

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
        "Calculator",                   // Window title
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
