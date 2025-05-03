#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

int main()
{
    char input = ' ';
    wstring input2 = L" ";
    int killed = 0;

    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------------------Welcome to Simple Task Manager!--------------------------------------------" << endl;
    cout << "------------------------------------------------To start, press Enter.-------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    
    cin.get();

    cout << "Listing Processes..." << endl;
    // allow user to see message
    Sleep(1000);

    do {
        if (input == 'k') {
            cout << "Enter process name to be terminated." << endl;
            //wcin >> input2;
            cin.ignore(1000,'\n');
            getline(wcin, input2);
            killed = killByName(input2);
            cout << killed << " Processes killed." << endl;
            killed = 0;
            Sleep(2000);
        }
        else {
            // Clear the screen
            system("cls");

            printCurrentProcesses();
        }

        do {
            cout << endl << "Possible commands are: " << endl
                << " - \"r\" to refresh processes" << endl
                << " - \"k\" to kill process by name" << endl
                << " - \"q\" to quit" << endl;
            cin >> input;
        } while (!(input == 'r') && !(input == 'q') && !(input == 'k'));
    } while (input != 'q');

    return 0;
}