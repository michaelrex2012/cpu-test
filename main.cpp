#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cmath>
#include <windows.h>
#include <stdio.h>

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
        if (floor(totalTime) == totalTime && totalTime != before){
            cout << "[" << chrono::system_clock::now() << "] " << totalTime << "/" << runTime << endl;
            before = totalTime;
        }
    }

    cout << endl << "Your score by lines printed per second is: " << endl << (i / runTime) / 1000 <<
            " ln/ms" << endl << endl;
    system("pause");

    return 0;
}
