#include "TCHAR_STR.h"

enum { MAX_STRING_LEN = 1024 };
const TCHAR terminal = '\0';


void TCHAR_STR::DelStr()
{
	if (str != nullptr)
	{
		delete[] str;
		//若沒將指標指向nullptr會造成當機
		str = nullptr;
	}
}

void TCHAR_STR::SetStr(const TCHAR* arg)
{
	int newlen = int(_tcslen(arg));
	if (newlen>MAX_STRING_LEN)
		newlen = MAX_STRING_LEN;

	if (newlen != len)
	{
		DelStr();
	}
	if (str == nullptr)
		str = new TCHAR[newlen + 1];

	if (newlen != len)
		len = newlen;

	for (int i = 0; i<len; i++)
		str[i] = arg[i];

	str[len] = terminal;
}

const TCHAR* TCHAR_STR::StrAppend(const TCHAR* arg)
{
	TCHAR* newstr = nullptr;

	int len2 = int(_tcslen(arg));
	int newlen = len + len2;

	if (newlen > MAX_STRING_LEN)
		newlen = MAX_STRING_LEN;

	newstr = new TCHAR[newlen + 1]();

	for (int i = 0; i<newlen; i++)
	{
		if (i<len)
			newstr[i] = str[i];
		else
			newstr[i] = arg[i - len];
	}
	newstr[newlen] = terminal;
	return newstr;
}

TCHAR_STR::TCHAR_STR()
{
	SetStr(_T(""));
}
TCHAR_STR::TCHAR_STR(const TCHAR* arg)
{
	SetStr(arg);
}
TCHAR_STR::~TCHAR_STR()
{
	DelStr();
}

TCHAR_STR::operator const TCHAR*()
{
	return str;	//形態轉換
}

void TCHAR_STR::operator = (const TCHAR* tchar)
{
	SetStr(tchar);
}
void TCHAR_STR::operator = (const TCHAR_STR& baseStr)
{
	SetStr(baseStr.str);
}
void TCHAR_STR::operator = (const int num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%d"), num);
	SetStr(buf);
}
void TCHAR_STR::operator = (const float num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%.6f"), num);
	SetStr(buf);
}

bool TCHAR_STR::CmpStr(const TCHAR* tchar)
{
	int newlen=int( _tcslen(tchar));
	if(str == NULL || newlen!=len)
		return false;
	for(int i=0;i<len;i++)
	{
		if(str[i]!=tchar[i])
			return false;
	}
	return true;
}
bool TCHAR_STR::operator == (const TCHAR* tchar)
{
	return CmpStr(tchar);
}
bool TCHAR_STR::operator == (const TCHAR_STR& baseStr)
{
	return CmpStr(baseStr.str);
}
bool TCHAR_STR::operator == (const int num)
{
	TCHAR buf[32] ;
	_stprintf_s(buf,_T("%d"),num);
	return CmpStr(buf);
}
bool TCHAR_STR::operator == (const float num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%.6f"), num);
	return CmpStr(buf);
}


const TCHAR* TCHAR_STR::operator + (const TCHAR* tchar)
{
	return StrAppend(tchar);
}
const TCHAR* TCHAR_STR::operator + (const TCHAR_STR& baseStr)
{
	return StrAppend(baseStr.str);
}
const TCHAR* TCHAR_STR::operator + (const int num)
{
	TCHAR buf[256] ;
	_stprintf_s(buf,_T("%d"),num);

	return StrAppend(buf);
}
const TCHAR* TCHAR_STR::operator + (const float num)
{
	TCHAR buf[256];
	_stprintf_s(buf, _T("%.6f"), num);

	return StrAppend(buf);
}

void TCHAR_STR::operator += (const TCHAR* tchar)
{
	TCHAR newstr[MAX_STRING_LEN+1];
	_tcscpy_s(newstr,StrAppend(tchar));
	SetStr(newstr);
}
void TCHAR_STR::operator += (const TCHAR_STR& tchar)
{
	TCHAR newstr[MAX_STRING_LEN+1];
	_tcscpy_s(newstr,StrAppend(tchar.str));
	SetStr(newstr);
}
void TCHAR_STR::operator += (const int num)
{
	TCHAR buf[32] ;
	_stprintf_s(buf,_T("%d"),num);

	SetStr(StrAppend(buf));

	//TCHAR newstr[MAX_STRING_LEN+1];
	//_tcscpy_s(newstr,StrAppend(buf));
	//SetStr(newstr);
}
void TCHAR_STR::operator += (const unsigned int num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%d"), num);

	TCHAR newstr[MAX_STRING_LEN + 1];
	_tcscpy_s(newstr, StrAppend(buf));
	SetStr(newstr);
}
void TCHAR_STR::operator += (const float num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%.6f"), num);

	TCHAR newstr[MAX_STRING_LEN + 1];
	_tcscpy_s(newstr, StrAppend(buf));
	SetStr(newstr);
}

void TCHAR_STR::operator += (const bool b)
{
	if (b == true)
	{
		//如果這裡的L編譯錯誤請將專案的Character Set設成Use Unicode Character Set
		SetStr(StrAppend(L"true"));
	}
	else
	{
		SetStr(StrAppend(L"false"));
	}
}