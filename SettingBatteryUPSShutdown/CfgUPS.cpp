// CfgUPS.cpp : CCfgUPS ‚ÌŽÀ‘•

#include "stdafx.h"
#include "CfgUPS.h"


// CCfgUPS


STDMETHODIMP CCfgUPS::get_Cmdline(BSTR* pVal)
{
	CString m_PCs;
	if (RUt::QueryStr(_T("Cmdline"), m_PCs)) {
		*pVal = m_PCs.AllocSysString();
		return (*pVal != NULL) ? S_OK : E_OUTOFMEMORY;
	}
	return E_FAIL;
}

STDMETHODIMP CCfgUPS::put_Cmdline(BSTR newVal)
{
	if (RUt::WriteStr(_T("Cmdline"), newVal))
		return S_OK;
	return E_FAIL;
}
