#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

using namespace std;

void ListAllProcessWithName(DWORD dwProcessID) {
    BOOL bEnumProcessModule = FALSE;
    HMODULE bArray;
    DWORD bytesNeeded = 0;

    //open each process based on their PID
    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,    // PROCESS_VM_READ - Required to read memory in a process 
        //PROCESS_QUERY_INFORMATION - Required to retrieve certain information about a process
        FALSE,
        dwProcessID
    );
    wchar_t chProcessName[MAX_PATH] = L"UNKNOWN";
    wchar_t chProcessPath[MAX_PATH] = L"UNKNOWN PATH";

    if (hProcess) {
        //To get the process modules
        bEnumProcessModule = EnumProcessModulesEx(
            hProcess,
            &bArray,
            sizeof(bArray),
            &bytesNeeded,
            LIST_MODULES_ALL
        );
        if (bEnumProcessModule) {
            //to get the Process Module's Name. 
            GetModuleBaseName(
                hProcess,
                bArray,
                chProcessName,
                sizeof(chProcessName) / sizeof(wchar_t)
            );
            //to get the Process Path's Name. 
            GetModuleFileNameEx(
                hProcess,
                bArray,
                chProcessPath,
                sizeof(chProcessPath) / sizeof(wchar_t)
            );
        }

        cout << "---------------------------------" << '\n';
        wcout << L"Module BaseName : " << chProcessName << '\n';
        wcout << L"Module Path : " << chProcessPath << '\n';
        cout << "---------------------------------" << '\n';
        /*printf("Module BaseName : %p\n", chProcessName);
        printf("Module Path     : %p\n", chProcessPath);*/
        /*printf("Module BaseName : %ws\n", chProcessName);
        printf("Module Path     : %ws\n", chProcessPath);*/
        cout << "Process ID" << dwProcessID << '\n';
        cout << "---------------------------------" << '\n';




        CloseHandle(hProcess); // closin each process handle
    }
    


}
int main() {

    DWORD processes[2048] = { 0 };
    BOOL EnumProcess = FALSE;
    DWORD bytesNeeded = 0;

    // Enumerating the process
    EnumProcess = EnumProcesses( 
        processes,                                //array that receives the list of process identifier
        sizeof(processes),                       //size of the process array
        &bytesNeeded                            //no. of bytes returned in the array, this will be the output
    );

    //Calculating total no. of processes
    DWORD TotalNoOfProcess = bytesNeeded / sizeof(DWORD); // to find total no. of process after enumerating the process , which will be contained by bytesNeeded parameter.
    cout << "Total no. of processes: " << TotalNoOfProcess << '\n';

    //Calling each process id and getting its module names
    for (size_t i = 0; i < TotalNoOfProcess; i++) {
    //for (size_t i = 0; i < 3; i++) {


        //printf("process id: %x\n", processes[i]);

        ListAllProcessWithName(processes[i]);
    }

    system("PAUSE");

}