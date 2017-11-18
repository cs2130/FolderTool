// dllmain.h : 模块类的声明。

class CFolderToolModule : public ATL::CAtlDllModuleT< CFolderToolModule >
{
public :
	DECLARE_LIBID(LIBID_FolderToolLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FOLDERTOOL, "{973A3B23-FDFC-4513-BE1F-7A5E6F3DCF11}")
};

extern class CFolderToolModule _AtlModule;
