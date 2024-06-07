#include<iostream>
#include<windows.h>
using namespace std;
int main() {
    // ProcessInfo function 
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId = 0;
    DWORD dwThreadId = 0;
    //StartupInfo structure
    STARTUPINFO si;
    //PROCESSINFO structure
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si)); // to clear block of memory and initialise every structure member to 0
    ZeroMemory(&pi, sizeof(pi)); // to clear block of memory and initialise every structure member to 0
    BOOL pCreateProcess;
    pCreateProcess = CreateProcessA(
        "C:\\Program Files\\HxD\\HxD.exe", // application path 
        NULL,// for cli
        NULL,// security attribute
        NULL,//thread security attribute 
        FALSE,// inherit
        0, // flag
        NULL, //environment
        NULL, // current directory is same so null
        &si, // startup info
        &pi// process info
    );

    if (pCreateProcess) {
        cout << "Creating Process success" << '\n';
    }
    else cout << "Creating process failed" << '\n';

    cout << GetCurrentProcessId() << '\n';
    cout << "Process ID-> " << pi.dwProcessId << '\n';
    cout << "Thread ID-> " << pi.dwThreadId << '\n';

    //waiting for the childprocess to complete
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    system("PAUSE");
}