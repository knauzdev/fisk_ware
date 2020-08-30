#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "core.hpp"

#include "Detours\detours.h"
#include "Detours\detver.h"
HMODULE thisDLL;
Core* core;
DWORD WINAPI update(LPVOID lpParameter)
{
	core->update();
	core->hacks->detachHooks();
	FreeLibraryAndExitThread(thisDLL, 0x0);
	return 0;
}

void init()
{
	
	//func_sendPacket(&data);
	core = new Core();
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, update, 0, 0, &myThreadID);
}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		init();
		thisDLL = hinstDLL;
		break;

	case DLL_THREAD_ATTACH:

		break;

	case DLL_THREAD_DETACH:

		break;

	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}