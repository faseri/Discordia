#include <Windows.h>
#include <WinHttp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#pragma comment(lib, "winhttp.lib")

using namespace std;

class HTTP
{
public:
	string Request(string domain, string url, string dat);
private:
	std::wstring get_utf16(const std::string &str, int codepage);
};