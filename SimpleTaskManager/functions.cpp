#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include "functions.h"

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

    if (Process32First(snapshot.hSnap, &snapshot.pe)) {
        do {
            std::wcout
                << L"Name: " << snapshot.pe.szExeFile
                << "\033[" << 50 << 'G'
                << L"PID: " << snapshot.pe.th32ProcessID
                << "\033[" << 65 << 'G'
                << L"Thread Count: " << snapshot.pe.cntThreads
                << "\033[" << 85 << 'G'
                << L"Priority: " << snapshot.pe.pcPriClassBase
                << L"\n";
        } while (Process32Next(snapshot.hSnap, &snapshot.pe));
    }

    CloseHandle(snapshot.hSnap);
}

int killByName(const wstring& name) {
    int killed = 0;

    Snapshot snapshot = createSnapshot();

    if (Process32First(snapshot.hSnap, &snapshot.pe)) {
        do {
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
                        std::wcout << L"Failed to kill PID "
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