#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cmath>
#include <windows.h>
#include <cstdio>
#include "color.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    ofstream logFile("output.log");

    int runTime = 60;
    int iterations = 0;
    int totalTime = 0;
    int beforeTime = -1;
    int counter = 0;
    int priority = 3;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-p" || arg == "--cpu-priority" && i + 1 < argc) {
            priority = stoi(argv[++i]);
        }
        if (arg == "-t" || arg == "--time" && i + 1 < argc) {
            runTime = stoi(argv[++i]);
        }
    }


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
        iterations++;
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
         << (iterations / runTime) / 1000 << " ln/ms" << endl << endl;
    logFile << "[" << chrono::system_clock::now() << "] "
         << "RESULT" << " "
         << (iterations / runTime) / 1000 << " ln/ms";

    system("pause");
    return 0;
}