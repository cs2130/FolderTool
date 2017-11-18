// dllmain.cpp : DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "FolderTool_i.h"
#include "dllmain.h"

CFolderToolModule _AtlModule;
HINSTANCE         _hInstance;

// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	_hInstance = hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
