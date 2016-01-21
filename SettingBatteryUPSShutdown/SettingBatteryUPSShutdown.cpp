// SettingBatteryUPSShutdown.cpp : DLL エクスポートの実装です。


#include "stdafx.h"
#include "resource.h"
#include "SettingBatteryUPSShutdown.h"


class CSettingBatteryUPSShutdownModule : public CAtlDllModuleT< CSettingBatteryUPSShutdownModule >
{
public :
	DECLARE_LIBID(LIBID_SettingBatteryUPSShutdownLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SETTINGBATTERYUPSSHUTDOWN, "{AD051BD7-C4BB-4C61-9167-FD053620F8F1}")
};

CSettingBatteryUPSShutdownModule _AtlModule;


#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL エントリ ポイント
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif




// DLL を OLE によってアンロードできるようにするかどうかを指定します。
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// 要求された型のオブジェクトを作成するクラス ファクトリを返します。
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - エントリをシステム レジストリに追加します。
STDAPI DllRegisterServer(void)
{
    // オブジェクト、タイプ ライブラリおよびタイプ ライブラリ内のすべてのインターフェイスを登録します
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - エントリをレジストリから削除します。
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

