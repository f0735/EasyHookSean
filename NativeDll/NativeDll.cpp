// NativeDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "NativeDll.h"


// This is an example of an exported variable
NATIVEDLL_API int nNativeDll=0;

// This is an example of an exported function.
NATIVEDLL_API int fnNativeDll(void)
{
	printf("Hello World, I'm Native Dll!\n");

    return 42;
}

// This is the constructor of a class that has been exported.
// see NativeDll.h for the class definition
CNativeDll::CNativeDll()
{
    return;
}
