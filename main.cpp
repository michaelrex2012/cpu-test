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

    int runTime = 60;
    int priority = 3;
    string versionNum = "v0.1 Beta";
    string mode = "run";
    string outputPath = "output.log";

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if ((arg == "-p" || arg == "--cpu-priority") && i + 1 < argc) {
            priority = stoi(argv[++i]);
        }
        if ((arg == "-t" || arg == "--time") && i + 1 < argc) {
            runTime = stoi(argv[++i]);
        }
        if (arg == "-h" || arg == "--help") {
            mode = "help";
        }
        if (arg == "-v" || arg == "--version") {
            mode = "version";
        }
        if (arg == "-i" || arg == "--info") {
            mode = "info";
        }
        if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
            outputPath = argv[++i];
        }
        if (arg == "-no-ansi") {
            mode = "no-ansi";
        }
    }

    if (priority == 1) {
        SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
    }
    if (priority == 2) {
        SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
    }
    if (priority == 3) {
        SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    }
    if (priority == 4) {
        SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
    }
    if (priority == 5) {
        SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    }

    if (priority < 1 || priority > 5) {
        priority = 3;
    }

    if (mode == "version") {
        cout << versionNum;
    }

    if (mode == "info") {
        ofstream infoFile(outputPath);

        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
        infoFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;
        infoFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors;
    }

    if (mode == "help") {
        cout << "-h --help: Displays this help and exits" << endl;
        cout << "-v --version: Displays this program's version number and exits" << endl;
        cout << "-p --cpu-priority: Set run priority (Default unset, 1 is low, 3 is normal, and 5 is realtime)" << endl;
        cout << "-i --info: Displays machine info and exits" << endl;
        cout << "-t --time: Set time to run" << endl;
        cout << "-o --output: Specify an output file" << endl;
        cout << "--no-ansi: Disables ANSI color codes" << endl;
        cout << "-s --silent: Disables output to stout but still outputs to log file" << endl;
        cout << "--no-pause: Disables pause at end of benchmark";
    }

    if (mode == "run") {
        ofstream logFile(outputPath);

        int counter = 0;
        int beforeTime = -1;
        int iterations = 0;
        int totalTime = 0;
        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
        logFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;
        logFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;
        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " << "Priority of this test: " << priority << endl;
        logFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " << "Priority of this test: " << priority << endl;

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
    }

    if (mode == "no-ansi") {
        ofstream logFile(outputPath);

        int counter = 0;
        int beforeTime = -1;
        int iterations = 0;
        int totalTime = 0;
        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
        logFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " <<"Page Size: " << sysInfo.dwPageSize << " B" << endl;
        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;
        logFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;
        cout << "[" << chrono::system_clock::now() << "] "
                     << BACK_YELLOW << "INFO" << RESET << " " << "Priority of this test: " << priority << endl;
        logFile << "[" << chrono::system_clock::now() << "] "
                     << "INFO" << " " << "Priority of this test: " << priority << endl;

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
    }
    return 0;
}