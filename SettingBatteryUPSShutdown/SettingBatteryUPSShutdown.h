

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Thu Jan 21 15:06:07 2016
 */
/* Compiler settings for .\SettingBatteryUPSShutdown.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __SettingBatteryUPSShutdown_h__
#define __SettingBatteryUPSShutdown_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICfgUPS_FWD_DEFINED__
#define __ICfgUPS_FWD_DEFINED__
typedef interface ICfgUPS ICfgUPS;
#endif 	/* __ICfgUPS_FWD_DEFINED__ */


#ifndef __CfgUPS_FWD_DEFINED__
#define __CfgUPS_FWD_DEFINED__

#ifdef __cplusplus
typedef class CfgUPS CfgUPS;
#else
typedef struct CfgUPS CfgUPS;
#endif /* __cplusplus */

#endif 	/* __CfgUPS_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __ICfgUPS_INTERFACE_DEFINED__
#define __ICfgUPS_INTERFACE_DEFINED__

/* interface ICfgUPS */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICfgUPS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6FD6E87-E212-4B5C-8793-E68AEE2FEDEF")
    ICfgUPS : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FirstSecs( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FirstSecs( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecondsSecs( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SecondsSecs( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Servers( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Servers( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentStatus( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cmdline( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Cmdline( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICfgUPSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICfgUPS * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICfgUPS * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICfgUPS * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICfgUPS * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICfgUPS * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICfgUPS * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICfgUPS * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FirstSecs )( 
            ICfgUPS * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FirstSecs )( 
            ICfgUPS * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SecondsSecs )( 
            ICfgUPS * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SecondsSecs )( 
            ICfgUPS * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Servers )( 
            ICfgUPS * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Servers )( 
            ICfgUPS * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentStatus )( 
            ICfgUPS * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cmdline )( 
            ICfgUPS * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Cmdline )( 
            ICfgUPS * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ICfgUPSVtbl;

    interface ICfgUPS
    {
        CONST_VTBL struct ICfgUPSVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICfgUPS_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICfgUPS_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICfgUPS_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICfgUPS_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICfgUPS_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICfgUPS_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICfgUPS_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICfgUPS_get_FirstSecs(This,pVal)	\
    (This)->lpVtbl -> get_FirstSecs(This,pVal)

#define ICfgUPS_put_FirstSecs(This,newVal)	\
    (This)->lpVtbl -> put_FirstSecs(This,newVal)

#define ICfgUPS_get_SecondsSecs(This,pVal)	\
    (This)->lpVtbl -> get_SecondsSecs(This,pVal)

#define ICfgUPS_put_SecondsSecs(This,newVal)	\
    (This)->lpVtbl -> put_SecondsSecs(This,newVal)

#define ICfgUPS_get_Servers(This,pVal)	\
    (This)->lpVtbl -> get_Servers(This,pVal)

#define ICfgUPS_put_Servers(This,newVal)	\
    (This)->lpVtbl -> put_Servers(This,newVal)

#define ICfgUPS_get_CurrentStatus(This,pVal)	\
    (This)->lpVtbl -> get_CurrentStatus(This,pVal)

#define ICfgUPS_get_Cmdline(This,pVal)	\
    (This)->lpVtbl -> get_Cmdline(This,pVal)

#define ICfgUPS_put_Cmdline(This,newVal)	\
    (This)->lpVtbl -> put_Cmdline(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICfgUPS_get_FirstSecs_Proxy( 
    ICfgUPS * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ICfgUPS_get_FirstSecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICfgUPS_put_FirstSecs_Proxy( 
    ICfgUPS * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ICfgUPS_put_FirstSecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICfgUPS_get_SecondsSecs_Proxy( 
    ICfgUPS * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ICfgUPS_get_SecondsSecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICfgUPS_put_SecondsSecs_Proxy( 
    ICfgUPS * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ICfgUPS_put_SecondsSecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICfgUPS_get_Servers_Proxy( 
    ICfgUPS * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICfgUPS_get_Servers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICfgUPS_put_Servers_Proxy( 
    ICfgUPS * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICfgUPS_put_Servers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICfgUPS_get_CurrentStatus_Proxy( 
    ICfgUPS * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ICfgUPS_get_CurrentStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICfgUPS_get_Cmdline_Proxy( 
    ICfgUPS * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICfgUPS_get_Cmdline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ICfgUPS_put_Cmdline_Proxy( 
    ICfgUPS * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICfgUPS_put_Cmdline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICfgUPS_INTERFACE_DEFINED__ */



#ifndef __SettingBatteryUPSShutdownLib_LIBRARY_DEFINED__
#define __SettingBatteryUPSShutdownLib_LIBRARY_DEFINED__

/* library SettingBatteryUPSShutdownLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SettingBatteryUPSShutdownLib;

EXTERN_C const CLSID CLSID_CfgUPS;

#ifdef __cplusplus

class DECLSPEC_UUID("705708FB-9418-41C1-B348-E7919D5D9D42")
CfgUPS;
#endif
#endif /* __SettingBatteryUPSShutdownLib_LIBRARY_DEFINED__ */

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


