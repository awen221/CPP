#include "MultiByteAndWideChar.h"
#include <windows.h>

namespace MultiByteAndWideChar
{
	const char char_term = '\0';
	const wchar_t wchar_t_term = '\0';

	Char::Char()
	{
	}
	Char::~Char()
	{
	}
	wchar_t* Char::to_wchar_t(char* chr)
	{
		int size = MultiByteToWideChar(CP_ACP, 0, chr, -1, NULL, 0);

		wchar_t* wchar = new wchar_t[size];
		MultiByteToWideChar(CP_ACP, 0, chr, -1, wchar, size);
		wchar[size - 1] = wchar_t_term;
		return wchar;
	}
	char* Char::ReadFromMultiByte(FILE* pFile)
	{
		int size;
		fread(&size, sizeof(int), 1, pFile);

		char* chr = new char[size];
		fread(&chr, size, 1, pFile);
		chr[size - 1] = char_term;
		return chr;
	}
	void Char::WriteToMultiByte(FILE* pFile, char* chr)
	{
		int size = int(strlen(chr) + 1);
		fwrite(&size, sizeof(int), 1, pFile);

		fwrite(&chr, size, 1, pFile);
	}


	WideChar::WideChar()
	{
	}
	WideChar::~WideChar()
	{
	}
	char* WideChar::to_char(wchar_t* wchar)
	{
		int size = WideCharToMultiByte(CP_ACP, NULL, wchar, -1, NULL, 0, NULL, NULL);
		
		char* chr = new char[size];
		WideCharToMultiByte(CP_ACP, NULL, wchar, -1, chr, size, NULL, NULL);
		chr[size - 1] = char_term;
		return chr;
	}
	wchar_t* WideChar::ReadFromWideChar(FILE* pFile)
	{
		int size;
		fread(&size, sizeof(int), 1, pFile);

		wchar_t* wchar = new wchar_t[size];
		fread(&wchar, size, 1, pFile);
		wchar[size - 1] = wchar_t_term;
		return wchar;
	}
	void WideChar::WriteToWideChar(FILE* pFile, wchar_t* wchar)
	{
		int size = int(wcslen(wchar) + 1);
		fwrite(&size, sizeof(int), 1, pFile);

		fwrite(&wchar, size, 1, pFile);
	}
}
