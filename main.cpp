#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cmath>
#include <windows.h>
#include <cstdio>
#include "color.h"

using namespace std;

int main() {
    int i = 0;
    int totalTime = 0;
    int runTime;
    int before = totalTime;

    cout << "This program will test your single tread speed!" << endl;
    cout << "Enter the amount of seconds you want the test to run: ";
    cin >> runTime;
    cout << endl;


    const auto start = chrono::high_resolution_clock::now();


    while (totalTime < runTime) {
        i++;
        auto end = chrono::high_resolution_clock::now();
        totalTime = chrono::duration_cast<chrono::seconds>(end - start).count();
        if (floor(totalTime) == totalTime && totalTime != before) {
            cout << "[" << chrono::system_clock::now() << "] " << BOLD_BACK_GREEN << "PROGRESS" << RESET << " " << totalTime << "/" << runTime << " s" << endl;
            before = totalTime;
        }
    }

    cout << endl << RESET << "Your score by lines printed per second is: " << endl << (i / runTime) / 1000 <<
            "ln/ms" << endl << endl;
    system("pause");

    return 0;
}
