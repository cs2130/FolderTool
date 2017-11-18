// FolderTool.cpp : DLL ������ʵ�֡�


#include "stdafx.h"
#include "resource.h"
#include "FolderTool_i.h"
#include "dllmain.h"


// ����ȷ�� DLL �Ƿ���� OLE ж�ء�
STDAPI DllCanUnloadNow(void)
{
	return _AtlModule.DllCanUnloadNow();
}

// ����һ���๤���Դ������������͵Ķ���
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - ��ϵͳע���������
STDAPI DllRegisterServer(void)
{
	// ע��������Ϳ�����Ϳ��е����нӿ�
	//HRESULT hr = _AtlModule.DllRegisterServer();
	// ע��������Ϳ�����Ϳ��е����нӿ�
	HRESULT hr;
	HKEY hKey;

	static char pszGUID[] = "{A54A1DE3-A037-4D39-BD75-CE713B1BE28D}";

	hr = _AtlModule.DllRegisterServer();
	if (FAILED(hr))
	{
		return hr;
	}

	/*
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, sizeof(szExePath));
	string strLoad(szExePath);
	int pos = strLoad.rfind('\\');
	string strNameExe = strLoad.substr(0, pos+1)+"ColorPix.exe";
	MessageBox(NULL, strNameExe.c_str(), _T(""), MB_OK);

	HKEY hKEY;
	HKEY hKeyRoot = HKEY_CURRENT_USER;
	long ret0=(::RegOpenKeyEx(hKeyRoot, "SoftWare\FolderTool", 0, KEY_ALL_ACCESS, &hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		MessageBox("����д�����!");
		return E_FAIL;
	}

	if (RegCreateKeyA(HKEY_CURRENT_USER, 
	"SoftWare\FolderTool", &hKey) != ERROR_SUCCESS)
	{
	return E_FAIL;
	}

	if (RegSetValueA(hKey, NULL, REG_SZ, strNameExe.c_str(),
	strNameExe.length()) != ERROR_SUCCESS)
	{
	RegCloseKey(hKey);
	return E_FAIL;
	}

	*/

	if (RegCreateKeyA(HKEY_CLASSES_ROOT, 
		"*\\shellex\\ContextMenuHandlers\\FolderTool", &hKey) != ERROR_SUCCESS)
	{
		return E_FAIL;
	}

	if (RegSetValueA(hKey, NULL, REG_SZ, pszGUID,
		(DWORD)strlen(pszGUID)) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return E_FAIL;
	}

	if (RegCreateKeyA(HKEY_CLASSES_ROOT, 
		"Directory\\shellex\\ContextMenuHandlers\\FolderTool", &hKey) != ERROR_SUCCESS)
	{
		return E_FAIL;
	}

	if (RegSetValueA(hKey, NULL, REG_SZ, pszGUID,
		(DWORD)strlen(pszGUID)) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return E_FAIL;
	}

	if (RegCreateKeyA(HKEY_CLASSES_ROOT, 
		"Folder\\shellex\\ContextMenuHandlers\\FolderTool", &hKey) != ERROR_SUCCESS)
	{
		return E_FAIL;
	}

	if (RegSetValueA(hKey, NULL, REG_SZ, pszGUID,
		(DWORD)strlen(pszGUID)) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return E_FAIL;
	}

	if (RegCreateKeyA(HKEY_CLASSES_ROOT, 
		"Directory\\Background\\shellex\\ContextMenuHandlers\\FolderTool", &hKey) != ERROR_SUCCESS)
	{
		return E_FAIL;
	}

	if (RegSetValueA(hKey, NULL, REG_SZ, pszGUID,
		(DWORD)strlen(pszGUID)) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return E_FAIL;
	}
	RegCloseKey(hKey);
	//#define SZ_DIRCONTEXTMENUEXT	_T("Directory\\shellex\\ContextMenuHandlers\\Mumtaz")
	//#define SZ_FILECONTEXTMENUEXT	_T("*\\shellex\\ContextMenuHandlers\\Mumtaz")
	//#define SZ_FOLDERCONTEXTMENUEXT	_T("Folder\\shellex\\ContextMenuHandlers\\Mumtaz")

	return hr;
}

// DllUnregisterServer - ��ϵͳע������Ƴ��
STDAPI DllUnregisterServer(void)
{
	//HRESULT hr = _AtlModule.DllUnregisterServer();
	RegDeleteKeyA(HKEY_CLASSES_ROOT, "Directory\\Background\\shellex\\ContextMenuHandlers\\FolderTool");
	RegDeleteKeyA(HKEY_CLASSES_ROOT, "Folder\\shellex\\ContextMenuHandlers\\FolderTool");
	RegDeleteKeyA(HKEY_CLASSES_ROOT, "Directory\\shellex\\ContextMenuHandlers\\FolderTool");
	RegDeleteKeyA(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\FolderTool");
	return _AtlModule.DllUnregisterServer();
}

// DllInstall - ���û��ͼ������ϵͳע�������һ���/�Ƴ��
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{	
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}


