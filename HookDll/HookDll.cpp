// HookDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HookDll.h"
#include <easyhook.h>

using namespace test;
using namespace System;
using namespace System::Diagnostics;

typedef int (CALLBACK* pfnNativeDll)(void);

// This is an example of an exported variable
HOOKDLL_API int nHookDll=0;
pfnNativeDll tmp = NULL;
D3D11CreateDevicePtr pfnD3D11CreateDevice = NULL;
CreateDXGIFactoryFnPtr pfnCreateDXGIFactory = NULL;

// This is an example of an exported function.
HOOKDLL_API int fnHookDll(void)
{
	printf("Hello World, I'm Hook Dll!\n");

	CHookDll aa;

	if (tmp)
	{
		tmp();
	}

	int a1 = aa.test1();
	int a2 = aa.test2();
	int a3 = a2 - a1;

    return 43;
}

HRESULT WINAPI CreateDXGIFactoryHook(REFIID riid, void **ppFactory)
{
	Beep(500, 500);

	if (pfnCreateDXGIFactory)
	{
		return pfnCreateDXGIFactory(riid, ppFactory);
	}
	
	return NULL;
}

HRESULT WINAPI D3D11CreateDeviceHook
(
	_In_opt_ IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	_In_reads_opt_(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	_COM_Outptr_opt_ ID3D11Device** ppDevice,
	_Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
	_COM_Outptr_opt_ ID3D11DeviceContext** ppImmediateContext)
{
	OutputDebugStringA(__FUNCTION__);

	Beep(500, 500);

	//MessageBox(nullptr, L"D3D11CreateDeviceHook", L"sean", MB_OK| MB_TASKMODAL);

	if (pfnD3D11CreateDevice)
	{
		printf("calling origional D3D11CreateDevice()\n");
		//MessageBox(nullptr, L"calling origional D3D11CreateDevice()", L"sean", MB_OK);
		return pfnD3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
	}
	else
	{
		return NULL;
	}
}
// This is the constructor of a class that has been exported.
// see HookDll.h for the class definition
CHookDll::CHookDll()
{
    return;
}

int CHookDll::test1()
{
	return 1;
}

ULONG CHookDll::test2(void)
{
	return 2;
}

extern "C" HOOKDLL_API void NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{
	//fnNativeDll();

	HOOK_TRACE_INFO hHook = { NULL };
	HMODULE hNativeDll = LoadLibrary(TEXT("dxgi.dll"));
	//HMODULE hNativeDll = LoadLibrary(TEXT("NativeDll.dll"));
	//HMODULE hNativeDll = LoadLibrary(TEXT("d3d11.dll"));

	if (hNativeDll)
	{
		printf("GetModuleHandle %p!\n", hNativeDll);
		/*tmp = (pfnNativeDll)GetProcAddress(hNativeDll, "D3D11CreateDevice");
		if (tmp)
		{
			printf("GetProcAddress %p!\n", tmp);
		}
		else
		{
			printf("Can not GetProcAddress! err:0x%X\n", GetLastError());
		}*/
		pfnCreateDXGIFactory = (CreateDXGIFactoryFnPtr)GetProcAddress(hNativeDll, "CreateDXGIFactory");
		if (pfnCreateDXGIFactory)
		{
			printf("GetProcAddress %p!\n", pfnCreateDXGIFactory);
		}
		else
		{
			printf("Can not GetProcAddress! err:0x%X\n", GetLastError());
			return;
		}
	}
	else
	{
		printf("Can not GetModuleHandle!\n");
		return;
	}
	
	DbgAttachDebugger();

	NTSTATUS result = LhInstallHook(
		(void*)pfnCreateDXGIFactory,
		CreateDXGIFactoryHook,
		NULL,
		&hHook);

	if (FAILED(result))
	{
		printf("NativeInjectionEntryPoint: Failed to install hook: %S\n", RtlGetLastErrorString());
	}
	else
	{
		printf("NativeInjectionEntryPoint: Hook 'fnNativeDll installed successfully.\n");
	}

	ULONG ACLEntries[1] = { 0 };

	// Disable the hook for the provided threadIds, enable for all others
	LhSetExclusiveACL(ACLEntries, 1, &hHook);

	RhWakeUpProcess();

	return;
}

Main::Main(RemoteHooking::IContext ^InContext, String ^InChannelName)
{
	Debug::Print(__FUNCTION__);
	
	lhtest = nullptr;

	return;
}

Main::~Main()
{
	Debug::Print(__FUNCTION__);
	return;
}

void Main::Run(RemoteHooking::IContext ^InContext, String ^InChannelName)
{
	Debug::Print(__FUNCTION__);

	HMODULE hNativeDll = LoadLibrary(TEXT("NativeDll.dll"));
	tmp = (pfnNativeDll)GetProcAddress(hNativeDll, "fnNativeDll");

	lhtest = LocalHook::CreateUnmanaged(
		(System::IntPtr)tmp,
		(System::IntPtr)fnHookDll,
		(System::IntPtr)nullptr);

	array<Int32, 1>^ aa = { 0 };
	lhtest->ThreadACL->SetExclusiveACL(aa);
	RhWakeUpProcess();

	return;
}