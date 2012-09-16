

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Sep 16 14:11:07 2012
 */
/* Compiler settings for IE2EM.idl:
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

#ifndef __IE2EM_h__
#define __IE2EM_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIE2EMUrlTaker_FWD_DEFINED__
#define __IIE2EMUrlTaker_FWD_DEFINED__
typedef interface IIE2EMUrlTaker IIE2EMUrlTaker;
#endif 	/* __IIE2EMUrlTaker_FWD_DEFINED__ */


#ifndef __IE2EMUrlTaker_FWD_DEFINED__
#define __IE2EMUrlTaker_FWD_DEFINED__

#ifdef __cplusplus
typedef class IE2EMUrlTaker IE2EMUrlTaker;
#else
typedef struct IE2EMUrlTaker IE2EMUrlTaker;
#endif /* __cplusplus */

#endif 	/* __IE2EMUrlTaker_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IIE2EMUrlTaker_INTERFACE_DEFINED__
#define __IIE2EMUrlTaker_INTERFACE_DEFINED__

/* interface IIE2EMUrlTaker */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IIE2EMUrlTaker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE1A243C-C7CB-4543-AC32-A2D2CA879663")
    IIE2EMUrlTaker : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendUrl( 
            /* [in] */ BSTR strUrl,
            /* [in] */ BSTR strInfo,
            /* [in] */ BSTR strRef,
            /* [retval][out] */ VARIANT_BOOL *prVB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEmuleVersion( 
            /* [retval][out] */ BSTR *pstrVer) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIE2EMUrlTakerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIE2EMUrlTaker * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIE2EMUrlTaker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIE2EMUrlTaker * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIE2EMUrlTaker * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIE2EMUrlTaker * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIE2EMUrlTaker * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIE2EMUrlTaker * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendUrl )( 
            IIE2EMUrlTaker * This,
            /* [in] */ BSTR strUrl,
            /* [in] */ BSTR strInfo,
            /* [in] */ BSTR strRef,
            /* [retval][out] */ VARIANT_BOOL *prVB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEmuleVersion )( 
            IIE2EMUrlTaker * This,
            /* [retval][out] */ BSTR *pstrVer);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IIE2EMUrlTaker * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IIE2EMUrlTakerVtbl;

    interface IIE2EMUrlTaker
    {
        CONST_VTBL struct IIE2EMUrlTakerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIE2EMUrlTaker_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIE2EMUrlTaker_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIE2EMUrlTaker_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIE2EMUrlTaker_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIE2EMUrlTaker_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIE2EMUrlTaker_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIE2EMUrlTaker_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIE2EMUrlTaker_SendUrl(This,strUrl,strInfo,strRef,prVB)	\
    ( (This)->lpVtbl -> SendUrl(This,strUrl,strInfo,strRef,prVB) ) 

#define IIE2EMUrlTaker_GetEmuleVersion(This,pstrVer)	\
    ( (This)->lpVtbl -> GetEmuleVersion(This,pstrVer) ) 

#define IIE2EMUrlTaker_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIE2EMUrlTaker_INTERFACE_DEFINED__ */



#ifndef __IE2EMLib_LIBRARY_DEFINED__
#define __IE2EMLib_LIBRARY_DEFINED__

/* library IE2EMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IE2EMLib;

EXTERN_C const CLSID CLSID_IE2EMUrlTaker;

#ifdef __cplusplus

class DECLSPEC_UUID("48618374-565F-4CA0-B8CD-6F496C997FAF")
IE2EMUrlTaker;
#endif
#endif /* __IE2EMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


