// DllCall-CPP_CALL_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <windows.h>
#include <cstdio>

int Calldllexport()
{
#pragma region Calldllexport
	// DLL function signature  
	typedef int(*importFunction)(int, int);

	importFunction addNumbers;
	int result;

	// Load DLL file  
	HINSTANCE hinstLib = LoadLibrary(".\\Dll_dllexport.dll");
	if (hinstLib == NULL) {
		printf("ERROR: unable to load DLL\n");
		system("pause");
		return 1;
	}

	// Get function pointer  
	addNumbers = (importFunction)GetProcAddress(hinstLib, "Add");
	if (addNumbers == NULL) {
		printf("ERROR: unable to find DLL function\n");
		FreeLibrary(hinstLib);
		system("pause");
		return 1;
	}

	result = addNumbers(10, 20);
	printf("The result is %d\n", result);

	// Unload DLL file  
	FreeLibrary(hinstLib);
	system("pause");
	return 0;

#pragma endregion
}


using namespace CppMathFunc;
int Callnamespace_ref_class()
{
	Arithmetics^ a = gcnew Arithmetics();
	double d = Arithmetics().Add(10, 20);
	printf("The result is %f\n", d);
	system("pause");
	return d;
}

int main()
{
	return Calldllexport();
	//return Callnamespace_ref_class();
}



