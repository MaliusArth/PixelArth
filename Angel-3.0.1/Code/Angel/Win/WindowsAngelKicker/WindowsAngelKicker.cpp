// WindowsAngelKicker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>
#include <process.h>
#include <errno.h>

#define ANGEL_EXE_NAME "IntroGame.exe"

int main(int argc, char** argv)
{
	_chdir("bits");

	intptr_t retVal = _execl(ANGEL_EXE_NAME, ANGEL_EXE_NAME);

	return 0;
}


