#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cmath>
#include <windows.h>
#include <cstdio>
#include "color.h"
#include "TCHAR.h"
#include <fstream>

using namespace std;

int main() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    ofstream logFile("output.log");

    cout << "This program will test your single thread speed!" << endl;
    cout << "Enter the amount of seconds you want the test to run: ";
    int runTime;
    cin >> runTime;
    cout << endl;

    int i = 0;
    int totalTime = 0;
    int beforeTime = -1;
    int counter = 0;


    cout << "[" << chrono::system_clock::now() << "] "
                 << BACK_YELLOW << "INFO" << RESET << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
    logFile << "[" << chrono::system_clock::now() << "] "
                 << "INFO" << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
    cout << "[" << chrono::system_clock::now() << "] "
                 << BACK_YELLOW << "INFO" << RESET << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;
    logFile << "[" << chrono::system_clock::now() << "] "
                 << "INFO" << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;

    const auto start = chrono::system_clock::now();

    while (totalTime < runTime) {
        i++;
        auto end = chrono::system_clock::now();
        totalTime = chrono::duration_cast<chrono::seconds>(end - start).count();

        if (totalTime != beforeTime)
        {
            cout << "[" << chrono::system_clock::now() << "] "
                 << BOLD_BACK_GREEN << "PROGRESS" << RESET << " " << totalTime << "/" << runTime << " s" << endl;
            logFile << "[" << chrono::system_clock::now() << "] "
                 << "PROGRESS" << " " << totalTime << "/" << runTime << " s" << endl;
            beforeTime = totalTime;
            counter++;
        }
    }

    cout << "[" << chrono::system_clock::now() << "] "
         << BOLD_BACK_MAGENTA << "RESULT" << RESET << " "
         << (i / runTime) / 1000 << " ln/ms" << endl << endl;
    logFile << "[" << chrono::system_clock::now() << "] "
         << "RESULT" << " "
         << (i / runTime) / 1000 << " ln/ms";

    system("pause");
    return 0;
}