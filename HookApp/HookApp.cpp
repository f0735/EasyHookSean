// HookApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "easyhook.h"
#using "EasyHook.dll"

using namespace System;
using namespace System::Diagnostics;
using namespace EasyHook;

#define NativeAppName TEXT("MultiMon10.exe")
//#define NativeAppName TEXT("DesktopDuplication.exe")
#define HookDllName TEXT("HookDll.dll")

int main()
{
	//int TargetProcessId = 0;
	ULONG TargetProcessId = 0;
	NTSTATUS sts = 0;

	Debug::Print(__FUNCTION__);
	Console::WriteLine(L"Hello World");

	//sts = RhCreateAndInject(TEXT("NativeApp.exe"), NULL, 0, EASYHOOK_INJECT_DEFAULT, NULL, L"HookDll.dll", NULL, 0, &TargetProcessId);
	sts = RhCreateAndInject(
		NativeAppName,
		L"-output 0",
		0,
		EASYHOOK_INJECT_DEFAULT,
		NULL,
		HookDllName,
		NULL,
		0,
		&TargetProcessId);
	/*RemoteHooking::CreateAndInject(
		"NativeApp.exe", 
		"", 
		CREATE_NEW_CONSOLE,
		InjectionOptions::Default,
		"",
		"HookDll.dll",
		TargetProcessId,
		"");*/

	/*RemoteHooking::Inject(
		TargetProcessId,
		InjectionOptions::Default,
		".\\HookDll.dll",
		".\\HookDll.dll",
		"");*/
	//printf("\n[Error(0x%p)]: \"%S\" (code: %d {0x%p})\n", (PVOID)sts, RtlGetLastErrorString(), RtlGetLastError(), (PVOID)RtlGetLastError());

    return 0;
}

