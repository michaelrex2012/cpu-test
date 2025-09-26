#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <windows.h>

using namespace std;

int main() {
    int i = 0;
    int totalTime = 0;
    int runTime;
    int before = totalTime;

    cout << "This program will test your single tread speed!" << endl;
    cout << "Enter the amount of seconds you want the test to run: ";
    cin >> runTime;


    const auto start = chrono::high_resolution_clock::now();


    while (totalTime < runTime) {
        i++;
        auto end = chrono::high_resolution_clock::now();
        totalTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        if (floor(totalTime) == totalTime && totalTime != before){
            cout << totalTime << endl;
            before = totalTime;
        }
    }

    cout << endl << "Your score by lines printed per second is: " << endl << (i / runTime) / 1000 <<
            " ln/ms" << endl << endl;
    system("pause");

    return 0;
}
