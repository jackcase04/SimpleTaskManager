#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "functions.h"

#include <psapi.h>

using namespace std;

Snapshot createSnapshot() {
    Snapshot snapshot;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap == INVALID_HANDLE_VALUE) return {};

    PROCESSENTRY32 pe{};
    pe.dwSize = sizeof(PROCESSENTRY32);

    snapshot.hSnap = hSnap;
    snapshot.pe = pe;

    return snapshot;
}

void printCurrentProcesses() {
    Snapshot snapshot = createSnapshot();

    SIZE_T memory = 0;

    if (Process32First(snapshot.hSnap, &snapshot.pe)) {
        do {
            // attempt to open process to access memory
            HANDLE hProc = OpenProcess(
                PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,
                FALSE,
                snapshot.pe.th32ProcessID
            );

            if (hProc) {
                PROCESS_MEMORY_COUNTERS pmc;

                if (GetProcessMemoryInfo(hProc, &pmc, sizeof(pmc))) {
                    memory = pmc.WorkingSetSize / 1024;
                }
                else {
                    memory = 0;
                }
            }
            else {
                memory = 0;
            }

            if (!hProc == 0) {CloseHandle(hProc);}
            
            wcout
                << L"Name: " << snapshot.pe.szExeFile
                << "\033[" << 50 << 'G'
                << L"PID: " << snapshot.pe.th32ProcessID
                << "\033[" << 65 << 'G'
                << L"Thread Count: " << snapshot.pe.cntThreads
                << "\033[" << 85 << 'G'
                << L"Priority: " << snapshot.pe.pcPriClassBase;
            if (memory == 0) {
                wcout
                    << "\033[" << 100 << 'G'
                    << L"Memory Access Denied"
                    << L"\n";
            }
            else {
                wcout
                    << "\033[" << 100 << 'G'
                    << L"Memory: " << memory << L" KB"
                    << L"\n";
            }
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

        } while (Process32Next(snapshot.hSnap, &snapshot.pe));
    }

    CloseHandle(snapshot.hSnap);
}

int killByName(const wstring& name) {
    int killed = 0;

    Snapshot snapshot = createSnapshot();

    if (Process32First(snapshot.hSnap, &snapshot.pe)) {
        do {
            // check if process is one to be killed (could be multiple, so don't stop after 1)
            if (name == snapshot.pe.szExeFile) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, snapshot.pe.th32ProcessID);
                if (hProc) {
                    if (TerminateProcess(hProc, 1)) {
                        ++killed;
                        std::wcout << L"Killed " << snapshot.pe.szExeFile
                            << L" (PID " << snapshot.pe.th32ProcessID
                            << L")\n";
                    }
                    else {
                        std::wcout << L"Failed to kill PID: "
                            << snapshot.pe.th32ProcessID
                            << L"\n";
                    }
                    CloseHandle(hProc);
                }
                else {
                    std::wcout << L"Cannot open PID " << snapshot.pe.th32ProcessID << L"\n";
                }
            }
        } while (Process32Next(snapshot.hSnap, &snapshot.pe));
    }

    CloseHandle(snapshot.hSnap);

    if (killed == 0) cout << "No processes with that name" << endl;
    return killed;
}