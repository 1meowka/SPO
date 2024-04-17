#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define ID_BUTTON_CALCULATE 101
#define ID_COMBOBOX_FROM 102
#define ID_COMBOBOX_TO 103
#define ID_EDIT_INPUT 104
#define ID_EDIT_OUTPUT 105

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwnd;
    MSG msg;
    WNDCLASS wc = {0};

    wc.lpszClassName = TEXT("MyAppCalc");
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClass(&wc);
    hwnd = CreateWindow(wc.lpszClassName, TEXT("Converter"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 350, 200, 0, 0, hInstance, 0);

    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hComboBoxFrom, hComboBoxTo, hEditInput, hEditOutput;
    static TCHAR buffer[256];
    static double inputVal, outputVal;

    switch(message) {
        case WM_CREATE:
            CreateWindow(TEXT("STATIC"), TEXT("From:"), WS_VISIBLE | WS_CHILD, 50, 30, 50, 20, hwnd, NULL, NULL, NULL);
            hComboBoxFrom = CreateWindow(TEXT("COMBOBOX"), NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 100, 30, 150, 200, hwnd, (HMENU)ID_COMBOBOX_FROM, NULL, NULL);
            SendMessage(hComboBoxFrom, CB_ADDSTRING, 0, (LPARAM)TEXT("Kilogram"));
            SendMessage(hComboBoxFrom, CB_ADDSTRING, 0, (LPARAM)TEXT("Ton"));
            SendMessage(hComboBoxFrom, CB_ADDSTRING, 0, (LPARAM)TEXT("Gram"));
            SendMessage(hComboBoxFrom, CB_ADDSTRING, 0, (LPARAM)TEXT("Milligram"));

            CreateWindow(TEXT("STATIC"), TEXT("To:"), WS_VISIBLE | WS_CHILD, 50, 60, 50, 20, hwnd, NULL, NULL, NULL);
            hComboBoxTo = CreateWindow(TEXT("COMBOBOX"), NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 100, 60, 150, 200, hwnd, (HMENU)ID_COMBOBOX_TO, NULL, NULL);
            SendMessage(hComboBoxTo, CB_ADDSTRING, 0, (LPARAM)TEXT("Kilogram"));
            SendMessage(hComboBoxTo, CB_ADDSTRING, 0, (LPARAM)TEXT("Ton"));
            SendMessage(hComboBoxTo, CB_ADDSTRING, 0, (LPARAM)TEXT("Gram"));
            SendMessage(hComboBoxTo, CB_ADDSTRING, 0, (LPARAM)TEXT("Milligram"));

            CreateWindow(TEXT("STATIC"), TEXT("Input:"), WS_VISIBLE | WS_CHILD, 50, 90, 50, 20, hwnd, NULL, NULL, NULL);
            hEditInput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 90, 100, 20, hwnd, (HMENU)ID_EDIT_INPUT, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Output:"), WS_VISIBLE | WS_CHILD, 50, 120, 50, 20, hwnd, NULL, NULL, NULL);
            hEditOutput = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 100, 120, 100, 20, hwnd, (HMENU)ID_EDIT_OUTPUT, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Calculate"), WS_VISIBLE | WS_CHILD, 220, 90, 80, 20, hwnd, (HMENU)ID_BUTTON_CALCULATE, NULL, NULL);
            break;
        
        case WM_COMMAND:
            switch(LOWORD(wParam)) {
                case ID_BUTTON_CALCULATE:
                    GetWindowText(hEditInput, buffer, sizeof(buffer));
                    inputVal = atof(buffer);

                    int indexFrom = SendMessage(hComboBoxFrom, CB_GETCURSEL, 0, 0);
                    int indexTo = SendMessage(hComboBoxTo, CB_GETCURSEL, 0, 0);

                    switch(indexFrom) {
                        case 0: // Kilogram
                            switch(indexTo) {
                                case 0: // Kilogram
                                    outputVal = inputVal;
                                    break;
                                case 1: // Ton
                                    outputVal = inputVal / 1000;
                                    break;
                                case 2: // Gram
                                    outputVal = inputVal * 1000;
                                    break;
                                case 3: // Milligram
                                    outputVal = inputVal * 1e+6;
                                    break;
                            }
                            break;
                        case 1: // Ton
                            switch(indexTo) {
                                case 0: // Kilogram
                                    outputVal = inputVal * 1000;
                                    break;
                                case 1: // Ton
                                    outputVal = inputVal;
                                    break;
                                case 2: // Gram
                                    outputVal = inputVal * 1e+6;
                                    break;
                                case 3: // Milligram
                                    outputVal = inputVal * 1e+9;
                                    break;
                            }
                            break;
                        case 2: // Gram
                            switch(indexTo) {
                                case 0: // Kilogram
                                    outputVal = inputVal / 1000;
                                    break;
                                case 1: // Ton
                                    outputVal = inputVal / 1e+6;
                                    break;
                                case 2: // Gram
                                    outputVal = inputVal;
                                    break;
                                case 3: // Milligram
                                    outputVal = inputVal * 1000;
                                    break;
                            }
                            break;
                        case 3: // Milligram
                            switch(indexTo) {
                                case 0: // Kilogram
                                    outputVal = inputVal / 1e+6;
                                    break;
                                case 1: // Ton
                                    outputVal = inputVal / 1e+9;
                                    break;
                                case 2: // Gram
                                    outputVal = inputVal / 1000;
                                    break;
                                case 3: // Milligram
                                    outputVal = inputVal;
                                    break;
                            }
                            break;
                    }

                    snprintf(buffer, sizeof(buffer), "%f", outputVal);
                    SetWindowText(hEditOutput, buffer);
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

//gcc calc.c -Wall -o mycalcu.exe -mwindows
// ./mycalcu