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

    cout << "Welcome to Simple Task Manager!" << endl
        << "To start, press Enter." << endl;
    cin.get();

    cout << "Listing Processes..." << endl;
    // allow user to see message
    Sleep(1000);

    do {
        if (input == 'k') {
            cout << "Enter process name to be terminated." << endl;
            wcin >> input2;
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
