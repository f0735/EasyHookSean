// NativeApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <NativeDll.h>

int main()
{
	int i = 0;
	
	i = fnNativeDll();

	printf("%d", i);

	while (1)
	{
		Sleep(5000);
		printf("I'm Sleeping!");
	}

    return 0;
}

