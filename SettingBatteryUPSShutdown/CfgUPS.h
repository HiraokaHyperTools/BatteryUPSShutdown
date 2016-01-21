// CfgUPS.h : CCfgUPS の宣言

#pragma once
#include "resource.h"       // メイン シンボル

#include "SettingBatteryUPSShutdown.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM の完全サポートを含んでいない Windows Mobile プラットフォームのような Windows CE プラットフォームでは、単一スレッド COM オブジェクトは正しくサポートされていません。ATL が単一スレッド COM オブジェクトの作成をサポートすること、およびその単一スレッド COM オブジェクトの実装の使用を許可することを強制するには、_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA を定義してください。ご使用の rgs ファイルのスレッド モデルは 'Free' に設定されており、DCOM Windows CE 以外のプラットフォームでサポートされる唯一のスレッド モデルと設定されていました。"
#endif



// CCfgUPS

class ATL_NO_VTABLE CCfgUPS :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCfgUPS, &CLSID_CfgUPS>,
	public IDispatchImpl<ICfgUPS, &IID_ICfgUPS, &LIBID_SettingBatteryUPSShutdownLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCfgUPS()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CFGUPS)


BEGIN_COM_MAP(CCfgUPS)
	COM_INTERFACE_ENTRY(ICfgUPS)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	class RUt {
	public:
		static DWORD QueryDWORDVal(LPCTSTR pszValue, DWORD defval) {
			CRegKey rkParm;
			DWORD val = 0;
			LONG res;

			if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown"), STANDARD_RIGHTS_READ|KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS))) {
				if (0 == (res = rkParm.QueryDWORDValue(pszValue, val))) {
					return val;
				}
			}
			return defval;
		}

		static bool WriteDWORDVal(LPCTSTR pszValue, DWORD val) {
			CRegKey rkParm;
			LONG res;
			if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown"), KEY_WRITE))) {
				if (0 == (res = rkParm.SetDWORDValue(pszValue, val))) {
					return true;
				}
			}
			return false;
		}

		static bool QueryStr(LPCTSTR pszValue, CString &str) {
			CRegKey rkParm;
			DWORD val = 0;
			LONG res;
			if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown"), STANDARD_RIGHTS_READ|KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS))) {
				ULONG cch = 5000;
				LPTSTR pszBuff = str.GetBuffer(cch);
				if (0 == (res = rkParm.QueryStringValue(pszValue, pszBuff, &cch))) {
					str.ReleaseBuffer(cch);
					return true;
				}
				str.ReleaseBuffer(0);
			}
			return false;
		}

		static bool WriteStr(LPCTSTR pszValue, CString str) {
			CRegKey rkParm;
			LONG res;
			if (0 == (res = rkParm.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\HIRAOKA HYPERS TOOLS, Inc.\\MyBatteryUPSShutdown"), KEY_WRITE))) {
				if (0 == (res = rkParm.SetStringValue(pszValue, str))) {
					return true;
				}
			}
			return false;
		}
	};

public:
    virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FirstSecs( 
        /* [retval][out] */ LONG *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = RUt::QueryDWORDVal(_T("FirstSecs"), 300);
		return S_OK;
	}
    
    virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FirstSecs( 
        /* [in] */ LONG newVal)
	{
		if (RUt::WriteDWORDVal(_T("FirstSecs"), newVal))
			return S_OK;
		return E_FAIL;
	}
    
    virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SecondsSecs( 
        /* [retval][out] */ LONG *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = RUt::QueryDWORDVal(_T("SecondsSecs"), 120);
		return S_OK;
	}
    
    virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SecondsSecs( 
        /* [in] */ LONG newVal)
	{
		if (RUt::WriteDWORDVal(_T("SecondsSecs"), newVal))
			return S_OK;
		return E_FAIL;
	}
    
    virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Servers( 
        /* [retval][out] */ BSTR *pVal)
	{
		CString m_PCs;
		if (RUt::QueryStr(_T("Servers"), m_PCs)) {
			*pVal = m_PCs.AllocSysString();
			return (*pVal != NULL) ? S_OK : E_OUTOFMEMORY;
		}
		return E_FAIL;
	}
    
    virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Servers( 
        /* [in] */ BSTR newVal)
	{
		if (RUt::WriteStr(_T("Servers"), newVal))
			return S_OK;
		return E_FAIL;
	}

    virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentStatus( 
        /* [retval][out] */ LONG *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = RUt::QueryDWORDVal(_T("CurrentStatus"), 0);
		return S_OK;
	}

	STDMETHOD(get_Cmdline)(BSTR* pVal);
	STDMETHOD(put_Cmdline)(BSTR newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(CfgUPS), CCfgUPS)
