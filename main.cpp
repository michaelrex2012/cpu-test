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
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

using namespace std;

HRESULT GetCpuTemperature(double& temperatureCelsius)
{
    temperatureCelsius = -1.0;

    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
        return hr;

    hr = CoInitializeSecurity(
        nullptr, -1, nullptr, nullptr,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr, EOAC_NONE, nullptr);
    if (FAILED(hr))
    {
        CoUninitialize();
        return hr;
    }

    IWbemLocator* pLocator = nullptr;
    hr = CoCreateInstance(
        CLSID_WbemLocator,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID*)&pLocator);
    if (FAILED(hr))
    {
        CoUninitialize();
        return hr;
    }

    IWbemServices* pServices = nullptr;
    BSTR namespaceName = SysAllocString(L"root\\CIMV2");
    hr = pLocator->ConnectServer(
        namespaceName,
        nullptr,
        nullptr,
        nullptr,
        0,
        nullptr,
        nullptr,
        &pServices);
    SysFreeString(namespaceName);
    pLocator->Release();

    if (FAILED(hr))
    {
        CoUninitialize();
        return hr;
    }

    hr = CoSetProxyBlanket(
        pServices,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        nullptr,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        EOAC_NONE);

    if (FAILED(hr))
    {
        pServices->Release();
        CoUninitialize();
        return hr;
    }

    BSTR query = SysAllocString(L"SELECT * FROM Win32_PerfFormattedData_Counters_ThermalZoneInformation");
    BSTR wql = SysAllocString(L"WQL");

    IEnumWbemClassObject* pEnumerator = nullptr;
    hr = pServices->ExecQuery(
        wql,
        query,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr,
        &pEnumerator);

    SysFreeString(query);
    SysFreeString(wql);

    if (FAILED(hr))
    {
        pServices->Release();
        CoUninitialize();
        return hr;
    }

    IWbemClassObject* pClassObject = nullptr;
    ULONG returnedCount = 0;

    while (pEnumerator && pEnumerator->Next(WBEM_INFINITE, 1, &pClassObject, &returnedCount) == S_OK)
    {
        VARIANT vtTemp;
        VariantInit(&vtTemp);

        hr = pClassObject->Get(L"Temperature", 0, &vtTemp, nullptr, nullptr);
        if (SUCCEEDED(hr) && (vtTemp.vt == VT_I4))
        {
            long rawTemp = vtTemp.lVal;
            if (rawTemp > 0)
            {
                temperatureCelsius = (static_cast<double>(rawTemp) / 10.0) - 273.15;
                VariantClear(&vtTemp);
                pClassObject->Release();
                break;
            }
        }
        VariantClear(&vtTemp);
        pClassObject->Release();
    }

    if (pEnumerator) pEnumerator->Release();
    pServices->Release();
    CoUninitialize();

    return hr;
}

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