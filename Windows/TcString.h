#ifndef _TCSTRING_H_
#define _TCSTRING_H_

#include <windows.h>
#include <stdio.h>


class TcString
{
private:
	TCHAR* str;	//pointer
	void SetStr(const TCHAR*);
	bool CmpStr(const TCHAR*);
	const TCHAR* StrAppend(const TCHAR*, TCHAR*);

	WCHAR* CharToWchar(char*,WCHAR*);
	char* WcharToChar(WCHAR*, char*);
public:
	TcString();
	~TcString();
	int len;	//size of tchar

	operator const LPTSTR();
	operator const TCHAR*();

	void operator = (const TCHAR*);
	void operator = (const TcString&);
	void operator = (const int);
	void operator = (const float);
	
	bool operator == (const TCHAR*);
	bool operator == (const TcString&);
	bool operator == (const int);
	bool operator == (const float);

	const TCHAR* operator + (const TCHAR*);
	const TCHAR* operator + (const TcString&);
	const TCHAR* operator + (const int);
	const TCHAR* operator + (const float);

	void operator += (const TCHAR*);
	void operator += (const TcString&);
	void operator += (const int);
	void operator += (const unsigned int);
	void operator += (const float);
	void operator += (bool);

	WCHAR* GetWideChar();
	char* GetMultiByte(char*);

	void WriteToWideChar(FILE*);
	void WriteToMultiByte(FILE*);

	void ReadFromWideChar(FILE*);
	void ReadFromMultiByte(FILE*);
};

#endif