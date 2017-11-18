

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Apr 06 14:31:49 2017
 */
/* Compiler settings for FolderTool.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FolderTool_i_h__
#define __FolderTool_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRightMenu_FWD_DEFINED__
#define __IRightMenu_FWD_DEFINED__
typedef interface IRightMenu IRightMenu;
#endif 	/* __IRightMenu_FWD_DEFINED__ */


#ifndef __RightMenu_FWD_DEFINED__
#define __RightMenu_FWD_DEFINED__

#ifdef __cplusplus
typedef class RightMenu RightMenu;
#else
typedef struct RightMenu RightMenu;
#endif /* __cplusplus */

#endif 	/* __RightMenu_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IRightMenu_INTERFACE_DEFINED__
#define __IRightMenu_INTERFACE_DEFINED__

/* interface IRightMenu */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRightMenu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5ECD9EC1-9591-438A-A16D-8DD07E87ADD4")
    IRightMenu : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IRightMenuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRightMenu * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRightMenu * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRightMenu * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRightMenu * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRightMenu * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRightMenu * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRightMenu * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IRightMenuVtbl;

    interface IRightMenu
    {
        CONST_VTBL struct IRightMenuVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRightMenu_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRightMenu_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRightMenu_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRightMenu_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRightMenu_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRightMenu_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRightMenu_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRightMenu_INTERFACE_DEFINED__ */



#ifndef __FolderToolLib_LIBRARY_DEFINED__
#define __FolderToolLib_LIBRARY_DEFINED__

/* library FolderToolLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FolderToolLib;

EXTERN_C const CLSID CLSID_RightMenu;

#ifdef __cplusplus

class DECLSPEC_UUID("A54A1DE3-A037-4D39-BD75-CE713B1BE28D")
RightMenu;
#endif
#endif /* __FolderToolLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


