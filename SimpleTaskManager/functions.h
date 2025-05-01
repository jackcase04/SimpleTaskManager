#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>

using namespace std;

struct Snapshot {
	HANDLE hSnap;
	PROCESSENTRY32 pe;
};

Snapshot createSnapshot();

void printCurrentProcesses();

int killByName(const std::wstring& name);

#endif