#include <windows.h> 
#include <stdio.h> 
 
// Function for handling keyboard messages 
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) { 
    if (nCode == HC_ACTION) { 
        KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam; 
        int keycode = kbdStruct->vkCode; 
        printf("Key code: %d\n", keycode); 
    } 
    return CallNextHookEx(NULL, nCode, wParam, lParam); 
} 
 
int main() { 
    // Set a hook to handle keyboard messages 
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0); 
    if (hHook == NULL) { 
        printf("SetWindowsHookEx failed with error code %d\n", GetLastError()); 
        return 1; 
    } 
 
    // Message loop to keep the application running 
    MSG msg; 
    while (GetMessage(&msg, NULL, 0, 0)) { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
 
        // Check for the ESC key 
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { 
            break; 
        } 
    } 
 
    UnhookWindowsHookEx(hHook); 
 
    return 0; 
}