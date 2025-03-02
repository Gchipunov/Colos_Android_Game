#include <windows.h>

// Global variables to store the key remapping
int originalKey = VK_A; // Example: Original key is 'A'
int remappedKey = VK_B; // Example: Remapped key is 'B'

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN: //Handle system keys like Alt+key
        if (wParam == originalKey) {
            // Simulate the remapped key press
            keybd_event(remappedKey, 0, 0, 0); // Press
            return 0; // Prevent the original key from being processed
        }
        break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
        if (wParam == originalKey) {
            // Simulate the remapped key release
            keybd_event(remappedKey, 0, KEYEVENTF_KEYUP, 0); // Release
            return 0; // Prevent the original key from being processed
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Window class definition
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"KeyRemapWindowClass";

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        L"KeyRemapWindowClass",
        L"Key Remapper",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

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

// Example usage and how to change remaps:
// To remap 'C' to 'D', change the global variables to:
// originalKey = 'C';
// remappedKey = 'D';
// To remap '1' to '2', change the global variables to:
// originalKey = VK_1;
// remappedKey = VK_2;
// To remap 'F1' to 'F2', change the global variables to:
// originalKey = VK_F1;
// remappedKey = VK_F2;

// To get the virtual key codes, look up the windows virtual key codes.
