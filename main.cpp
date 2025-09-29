#define WIN32_DCOM
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cmath>
#include <windows.h>
#include <cstdio>
#include "color.h"
#include "TCHAR.h"

using namespace std;

int main() {
    cout << "This program will test your single thread speed!" << endl;
    cout << "Enter the amount of seconds you want the test to run: ";
    int runTime;
    cin >> runTime;
    cout << endl;

    int i = 0;
    int totalTime = 0;
    int beforeTime = -1;
    int counter = 0;

    const auto start = chrono::high_resolution_clock::now();

    while (totalTime < runTime) {
        i++;
        auto end = chrono::high_resolution_clock::now();
        totalTime = chrono::duration_cast<chrono::seconds>(end - start).count();

        if (totalTime != beforeTime)
        {
            cout << "[" << chrono::high_resolution_clock::now() << "] "
                 << BOLD_BACK_GREEN << "PROGRESS" << RESET << " " << totalTime << "/" << runTime << " s" << endl;
            beforeTime = totalTime;
            counter++;
        }
    }

    cout << "[" << chrono::high_resolution_clock::now() << "] "
         << BOLD_BACK_MAGENTA << "RESULT" << RESET << " "
         << (i / runTime) / 100 << " ln/ms" << endl << endl;

    system("pause");
    return 0;
}