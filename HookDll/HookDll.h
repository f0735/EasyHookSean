// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HOOKDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HOOKDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HOOKDLL_EXPORTS
#define HOOKDLL_API __declspec(dllexport)
#else
#define HOOKDLL_API __declspec(dllimport)
#endif

#include <d3d11.h>
#include <dxgi.h>
#using "EasyHook.dll"
#using <System.dll>

using namespace System;
using namespace EasyHook;

namespace test
{
	public ref class Main : EasyHook::IEntryPoint
	{
	public:
		Main(RemoteHooking::IContext ^InContext, String ^InChannelName);
		~Main();
		void Run(RemoteHooking::IContext ^InContext, String ^InChannelName);
	private:
		LocalHook ^lhtest;
	};
}

// This class is exported from the HookDll.dll
class HOOKDLL_API CHookDll {
public:
	CHookDll(void);
	// TODO: add your methods here.
};

extern HOOKDLL_API int nHookDll;

HOOKDLL_API int fnHookDll(void);

typedef HRESULT (WINAPI *D3D11CreateDevicePtr)(
	_In_opt_ IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	_In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	_COM_Outptr_opt_ ID3D11Device** ppDevice,
	_Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
	_COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext);

typedef HRESULT (WINAPI *CreateDXGIFactoryFnPtr)(REFIID riid, void **ppFactory);