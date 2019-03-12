#pragma once

#include <stdio.h>

namespace MultiByteAndWideChar
{
	class Char
	{
	public:
		Char();
		~Char();
		wchar_t* to_wchar_t(char*);
		char* ReadFromMultiByte(FILE*);
		void WriteToMultiByte(FILE*, char*);
	};

	class WideChar
	{
	public:
		WideChar();
		~WideChar();
		char* to_char(wchar_t*);
		wchar_t* ReadFromWideChar(FILE*);
		void WriteToWideChar(FILE*, wchar_t*);
	};
}

