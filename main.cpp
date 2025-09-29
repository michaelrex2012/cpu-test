#define _WIN32_DCOM
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <cmath>
#include <windows.h>
#include <cstdio>
#include "color.h"
#include "TCHAR.h"
#include <comdef.h>
#include <Wbemidl.h>

using namespace std;

int i = 0;
int totalTime = 0;
int runTime;
int beforeTime = totalTime;
int counter = totalTime;
long temp;

#pragma comment(lib, "wbemuuid.lib")

HRESULT GetCpuTemperature(LPLONG pTemperature)
{
        if (pTemperature == NULL)
                return E_INVALIDARG;

        *pTemperature = -1;
        HRESULT ci = CoInitialize(NULL);
        HRESULT hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
        if (SUCCEEDED(hr))
        {
                IWbemLocator *pLocator;
                hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
                if (SUCCEEDED(hr))
                {
                        IWbemServices *pServices;
                        BSTR ns = SysAllocString(L"root\\WMI");
                        hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
                        pLocator->Release();
                        SysFreeString(ns);
                        if (SUCCEEDED(hr))
                        {
                                BSTR query = SysAllocString(L"SELECT * FROM MSAcpi_ThermalZoneTemperature");
                                BSTR wql = SysAllocString(L"WQL");
                                IEnumWbemClassObject *pEnum;
                                hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
                                SysFreeString(wql);
                                SysFreeString(query);
                                pServices->Release();
                                if (SUCCEEDED(hr))
                                {
                                        IWbemClassObject *pObject;
                                        ULONG returned;
                                        hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
                                        pEnum->Release();
                                        if (SUCCEEDED(hr))
                                        {
                                                BSTR temp = SysAllocString(L"CurrentTemperature");
                                                VARIANT v;
                                                VariantInit(&v);
                                                hr = pObject->Get(temp, 0, &v, NULL, NULL);
                                                pObject->Release();
                                                SysFreeString(temp);
                                                if (SUCCEEDED(hr))
                                                {
                                                        *pTemperature = V_I4(&v);
                                                }
                                                VariantClear(&v);
                                        }
                                }
                        }
                        if (ci == S_OK)
                        {
                                CoUninitialize();
                        }
                }
        }
        return hr;
}

int main() {
    cout << "This program will test your single tread speed!" << endl;
    cout << "Enter the amount of seconds you want the test to run: ";
    cin >> runTime;
    cout << endl;


    const auto start = chrono::high_resolution_clock::now();


    while (totalTime < runTime) {
        i++;
        auto end = chrono::high_resolution_clock::now();
        totalTime = chrono::duration_cast<chrono::seconds>(end - start).count();
        if (floor(totalTime) == totalTime && totalTime != beforeTime) {
            cout << "[" << chrono::system_clock::now() << "] " << BOLD_BACK_GREEN << "PROGRESS" << RESET << " " << totalTime << "/" << runTime << " s" << endl;
            beforeTime = totalTime;
            counter++;
        }
        if (counter == 10) {
                GetCpuTemperature(&temp);
                cout << "[" << chrono::system_clock::now() << "] " << BOLD_BACK_CYAN << "USAGE" << RESET << printf("temp=%lf\n", ((double)temp / 10 - 273.15)) << endl;
                getc(stdin);
                counter = 0;
        }
    }

    cout << "[" << chrono::system_clock::now() << "] " << BOLD_BACK_MAGENTA << "RESULT" << RESET << " " << (i/runTime)/100 << " ln/" << "ms" << endl << endl;
    system("pause");

    return 0;
}
