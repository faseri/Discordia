// Checker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"


int main()
{
	//ShellExecute(NULL, 0, _T("C:\\Windows\\System32\\cmd.exe"), 0, 0, SW_HIDE);

	system("powershell.exe SCHTASKS.exe /Create /SC MINUTE /TN \"Test\" /TR C:\\Windows\\System32\\cmd.exe /F");

	system("pause");
    return 0;
}

