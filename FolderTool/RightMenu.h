// RightMenu.h : CRightMenu ������

#pragma once
#include "resource.h"       // ������



#include "FolderTool_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;

#define SZ_MENUTEXT TEXT("�ļ��б�ע")
extern HINSTANCE         _hInstance;

// CRightMenu

class ATL_NO_VTABLE CRightMenu :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRightMenu, &CLSID_RightMenu>,
	public IDispatchImpl<IRightMenu, &IID_IRightMenu, &LIBID_FolderToolLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CRightMenu()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RIGHTMENU)

BEGIN_COM_MAP(CRightMenu)
	COM_INTERFACE_ENTRY(IRightMenu)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_hBitmap = LoadBitmap(_hInstance, MAKEINTRESOURCE(IDB_MENU));
		return S_OK;
	}

	void FinalRelease()
	{
		if (m_hBitmap)
		{
			DeleteObject(m_hBitmap);
		}
	}

public:
	enum 
	{
		IDM_CTXMENU = 100,
	};

public:

    HRESULT STDMETHODCALLTYPE Initialize( 
        /* [in] */ LPCITEMIDLIST pidlFolder,
        /* [in] */ IDataObject *pdtobj,
        /* [in] */ HKEY hkeyProgID)
    {
		
        HRESULT hr;
        UINT    nFileCount;
        UINT    nLen;
		ZeroMemory (m_pszFileName, MAX_PATH);

		if(pdtobj != NULL){
			FORMATETC fmt = 
			{
				CF_HDROP,
				NULL,
				DVASPECT_CONTENT,
				-1,
				TYMED_HGLOBAL
			};

			STGMEDIUM sm = 
			{
				TYMED_HGLOBAL
			};

			hr = pdtobj->GetData(&fmt, &sm);

			if (FAILED(hr))
			{
				return hr;
			}

			nFileCount = DragQueryFile((HDROP)sm.hGlobal, 0xFFFFFFFF, NULL, 0);

			if (nFileCount >= 1)
			{
				nLen = DragQueryFile((HDROP)sm.hGlobal, 0, m_pszFileName, sizeof(m_pszFileName));

				if (nLen >0 && nLen <MAX_PATH)
				{
					m_pszFileName[nLen] = _T('\0');
					hr = S_OK;
				}
				else
				{
					hr = E_INVALIDARG;
				}    
			}
			else
			{            
				hr = E_INVALIDARG;
			}
			ReleaseStgMedium(&sm);
		}else{
			hr = S_OK;
		}

        return hr;
    }

	/********************
	HRESULT STDMETHODCALLTYPE Initialize( LPCITEMIDLIST pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID)
	{
		//�ļ��б�
		if( pdtobj != NULL ) 
		{
			STGMEDIUM stg = { TYMED_HGLOBAL };
			FORMATETC etc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
			//��pdtobj�л�ȡ�ļ��б�ָ��,���Ǵ洢��HDROP��ʽ��
			if( SUCCEEDED( pdtobj->GetData( &etc, &stg ) ) ) 
			{
				//ȡ��HDROP���
				HDROP hDrop = (HDROP) ::GlobalLock( stg.hGlobal );
				//��ȡ�ò����б�ѡ�е��ļ�����Ŀ
				UINT uCount = ::DragQueryFile( hDrop, (UINT) -1, NULL, 0 );
				for( UINT uIndex = 0; uIndex < uCount; uIndex++ ) 
				{
					TCHAR szFileName[MAX_PATH] = { 0 };
					//��ȡ�ļ���
					::DragQueryFile(hDrop, uIndex, szFileName, (sizeof(szFileName) / sizeof(TCHAR)) - 1);

					//szFileNameΪ�ļ�(��)��
				}
				::GlobalUnlock( stg.hGlobal );
				::ReleaseStgMedium( &stg );
			}
		}    
		return S_OK;
	}
	*********************/

    STDMETHOD(QueryContextMenu)(THIS_
        HMENU hmenu,
        UINT indexMenu,
        UINT idCmdFirst,
        UINT idCmdLast,
        UINT uFlags)
    {
        MENUITEMINFO mii;

        if (uFlags & CMF_DEFAULTONLY)
        {
            return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);
        }

        memset((void*)&mii, 0, sizeof(mii));
        mii.cbSize      = sizeof(mii);
        mii.fMask       = MIIM_STRING | MIIM_CHECKMARKS | MIIM_ID | MIIM_STATE;
        mii.cch         = lstrlen(SZ_MENUTEXT);
        mii.dwTypeData  = SZ_MENUTEXT;

        /*
            ������hbmpChecked������hbmpItem��ԭ��
            - -�Լ��������Ծ�֪���ˡ�
        */
        //mii.hbmpItem
        mii.hbmpChecked = m_hBitmap;
        mii.hbmpUnchecked = m_hBitmap;
        mii.fState      = MFS_ENABLED;
        mii.wID         = idCmdFirst + indexMenu;

        if (!InsertMenuItem(hmenu, indexMenu, TRUE, &mii))       
        {
             return E_FAIL;
        }

        lstrcpynA(m_pszVerb, "protected_run", 32);
        lstrcpynW(m_pwszVerb, L"protected_run", 32);

		//indexMenu++;
		//InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION,0, NULL);
		//indexMenu++;

		/*
        
		UINT uCmdID = idCmdFirst;
		char *szMenuText_Popup = "�Զ���˵�";
		char *szMenuText_1 = "AAA";
		char *szMenuText_2 = "�Զ���˵�2...";
		char *szMenuText_3 = "�Զ���˵�3...";
		char *szMenuText_4 = "�Զ���˵�4...";
		indexMenu++;
		InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION, 0, NULL); 
		indexMenu++;

		HMENU hSubMenu = CreateMenu();

		if(hSubMenu)
		{
			InsertMenu(hSubMenu, 0, MF_STRING  | MF_BYPOSITION, uCmdID++, szMenuText_1);

			InsertMenu(hSubMenu, 1, MF_STRING  | MF_BYPOSITION, uCmdID++, szMenuText_2);

			InsertMenu(hSubMenu, 2, MF_STRING  | MF_BYPOSITION, uCmdID++, szMenuText_3);

			InsertMenu(hSubMenu, 3, MF_STRING  | MF_BYPOSITION, uCmdID++, szMenuText_4);
		}

		InsertMenu(hmenu, indexMenu, MF_STRING | MF_POPUP | MF_BYPOSITION, (UINT_PTR)hSubMenu, szMenuText_Popup);
		//(UINT_PTR)hSubMenu������uFlags����ΪMF_POPUPʱ��ָ������ʽ�˵����Ӳ˵��ľ���� 
		indexMenu++;
		InsertMenu(hmenu, indexMenu, MF_SEPARATOR | MF_BYPOSITION,0, NULL);
		indexMenu++;
		 return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, uCmdID );
		*/

        //return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, IDM_CTXMENU + 1);
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, IDM_CTXMENU + 1);
    }

    STDMETHOD(InvokeCommand)(THIS_
        LPCMINVOKECOMMANDINFO lpici)
    {
        BOOL fEx = FALSE;
        BOOL fUnicode = FALSE;

        if(lpici->cbSize == sizeof(CMINVOKECOMMANDINFOEX))
        {
            fEx = TRUE;
            if((lpici->fMask & CMIC_MASK_UNICODE))
            {
                fUnicode = TRUE;
            }
        }
        if( !fUnicode && HIWORD(lpici->lpVerb))
        {
            if(StrCmpIA(lpici->lpVerb, m_pszVerb))
            {
                return E_FAIL;
            }
        }
        else if( fUnicode && HIWORD(((CMINVOKECOMMANDINFOEX *) lpici)->lpVerbW))
        {
            if(StrCmpIW(((CMINVOKECOMMANDINFOEX *)lpici)->lpVerbW, m_pwszVerb))
            {
                return E_FAIL;
            }
        }
		else{
			 int len=strlen(m_pszFileName);
			 if(len==0){
				GotoInfo((LPSTR)lpici->lpDirectory);
				return E_FAIL;
			 }else{
				GotoInfo(m_pszFileName);
				return S_OK;
			 }
		}
		/*
        else if(LOWORD(lpici->lpVerb) != IDM_CTXMENU)
        {
			//MessageBox(NULL, lpici->lpDirectory, _T("load"), MB_OK);
			GotoInfo((LPSTR)lpici->lpDirectory);
            return E_FAIL;
        }
        else
        {
            //�ڴ˴������¼�.
            MessageBox(NULL, m_pszFileName, _T(""), MB_OK);
			GotoInfo(m_pszFileName);
            return S_OK;
        }
		*/

        return E_FAIL;
    }

    STDMETHOD(GetCommandString)(THIS_
        UINT_PTR    idCmd,
        UINT        uType,
        UINT      * pwReserved,
        LPSTR       pszName,
        UINT        cchMax)
    {
        HRESULT  hr = E_INVALIDARG;
        static CHAR szHelpTextA[] = "�ļ��б�ע";
        static WCHAR szHelpTextW[] = L"�ļ��б�ע";

        if(idCmd != IDM_CTXMENU)
        {
            return hr;
        }

        switch(uType)
        {
        case GCS_HELPTEXTA:
            lstrcpynA((CHAR*)pszName, szHelpTextA, cchMax);
            break; 

        case GCS_HELPTEXTW: 
            lstrcpynW((WCHAR*)pszName, szHelpTextW, cchMax);;
            break; 

        case GCS_VERBA:
            lstrcpynA((CHAR*)pszName, m_pszVerb, cchMax);
            break; 

        case GCS_VERBW:
            lstrcpynW((WCHAR*)pszName, m_pwszVerb, cchMax);
            break;

        default:
            hr = S_OK;
            break; 
        }
        return hr;
    }
public:
	void GotoInfo(LPSTR szFullPath){
		PROCESS_INFORMATION lpProcessInformation;
		STARTUPINFO startupinfo;
		memset(&startupinfo,0,sizeof(STARTUPINFO));
		memset(&lpProcessInformation,0,sizeof(PROCESS_INFORMATION));
		startupinfo.cb = sizeof(STARTUPINFO);
		startupinfo.dwFlags = STARTF_FORCEOFFFEEDBACK;
		startupinfo.dwX = 0;
		startupinfo.dwY = 0;
		startupinfo.lpDesktop = NULL;
		startupinfo.lpReserved = NULL;
		startupinfo.lpReserved2 = NULL;
		startupinfo.lpTitle = NULL;
		/*
		HKEY hKey;
		DWORD keyType = REG_SZ;//������������
		TCHAR getLoad[MAX_PATH];
		DWORD DataLen = MAX_PATH;//�������ݳ���
		long ret1=::RegQueryValueEx(hKey, _T("load"), NULL, &keyType, (LPBYTE)getLoad,&DataLen);
		MessageBox(NULL, getLoad, _T(""), MB_OK);
		*/
		HKEY hKEY;//�����йص�hKEY,�ڲ�ѯ����ʱҪ�ر�
		//����·��data_Set��ص�hKEY
		LPCTSTR data_Set= _T("Software\\FolderTool");
		//����ע���hKEY�򱣴�˺������򿪵ļ��ľ��
		if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_READ,&hKEY))
		{
			char dwValue[256];
			DWORD dwSzType = REG_SZ;
			DWORD dwSize = sizeof(dwValue);
			//"F:\\project\\FolderTool\\x64\\Release\\ColorPix.exe" F:\project\WinTool\Release
			if (::RegQueryValueEx(hKEY,_T("LOAD"), 0, &dwSzType, (LPBYTE)&dwValue, &dwSize) == ERROR_SUCCESS)
			{
				CreateProcess(dwValue, szFullPath, NULL, NULL, FALSE,
					NORMAL_PRIORITY_CLASS, NULL, NULL, &startupinfo, &lpProcessInformation);
			}
			//����������رմ򿪵�hKEY
			::RegCloseKey(hKEY);
		}
		
	}

private:
    TCHAR   m_pszFileName[MAX_PATH];
    HBITMAP m_hBitmap;
    CHAR    m_pszVerb[32];
    WCHAR   m_pwszVerb[32];

};

OBJECT_ENTRY_AUTO(__uuidof(RightMenu), CRightMenu)