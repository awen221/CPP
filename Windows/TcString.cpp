#include"TcString.h"
#include<tchar.h>


enum{MAX_STRING_LEN=1024};

TcString::TcString()
{
	str=NULL;
	len=-1;
	SetStr(_T(""));
}
TcString::~TcString()
{
	if(str != NULL)
		delete str;
}
TcString::operator const LPTSTR ()
{
	return str;	//形態轉換
}
TcString::operator const TCHAR*()
{
	return str;	//形態轉換
}


void TcString::SetStr(const TCHAR* tchar)
{
	int newlen = int(_tcslen(tchar));
	if (newlen>MAX_STRING_LEN)
		newlen = MAX_STRING_LEN;

	if(str != NULL && newlen!=len)
		delete str;

	if(str == NULL || newlen != len)
		str=new TCHAR[newlen+1];

	if (newlen != len)
		len = newlen;

	for(int i=0;i<len;i++)
		str[i]=tchar[i];
	str[len]=0;		
}
void TcString::operator = (const TCHAR* tchar)
{
	SetStr(tchar);
}
void TcString::operator = (const TcString& baseStr)
{
	SetStr(baseStr.str);
}
void TcString::operator = (const int num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%d"), num);
	SetStr(buf);
}
void TcString::operator = (const float num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%.6f"), num);
	SetStr(buf);
}

bool TcString::CmpStr(const TCHAR* tchar)
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
bool TcString::operator == (const TCHAR* tchar)
{
	return CmpStr(tchar);
}
bool TcString::operator == (const TcString& baseStr)
{
	return CmpStr(baseStr.str);
}
bool TcString::operator == (const int num)
{
	TCHAR buf[32] ;
	_stprintf_s(buf,_T("%d"),num);
	return CmpStr(buf);
}
bool TcString::operator == (const float num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%.6f"), num);
	return CmpStr(buf);
}

const TCHAR* TcString::StrAppend(const TCHAR* str2, TCHAR* newstr = NULL)
{		
	int len2=int ( _tcslen(str2) );
	int newlen=len+len2;

	if (newlen > MAX_STRING_LEN)
		newlen = MAX_STRING_LEN;

	newstr = new TCHAR[MAX_STRING_LEN+1]();

	for (int i = 0; i<newlen; i++)
	{
		if(i<len)
			newstr[i]=str[i];
		else
			newstr[i]=str2[i-len];
	}
	newstr[newlen]='\0';
	return newstr;
}
const TCHAR* TcString::operator + (const TCHAR* tchar)
{
	return StrAppend(tchar);
}
const TCHAR* TcString::operator + (const TcString& baseStr)
{
	return StrAppend(baseStr.str);
}
const TCHAR* TcString::operator + (const int num)
{
	TCHAR buf[256] ;
	_stprintf_s(buf,_T("%d"),num);

	return StrAppend(buf);
}
const TCHAR* TcString::operator + (const float num)
{
	TCHAR buf[256];
	_stprintf_s(buf, _T("%.6f"), num);

	return StrAppend(buf);
}

void TcString::operator += (const TCHAR* tchar)
{
	TCHAR newstr[MAX_STRING_LEN+1];
	_tcscpy_s(newstr,StrAppend(tchar));
	SetStr(newstr);
}
void TcString::operator += (const TcString& tchar)
{
	TCHAR newstr[MAX_STRING_LEN+1];
	_tcscpy_s(newstr,StrAppend(tchar.str));
	SetStr(newstr);
}
void TcString::operator += (const int num)
{
	TCHAR buf[32] ;
	_stprintf_s(buf,_T("%d"),num);

	TCHAR newstr[MAX_STRING_LEN+1];
	_tcscpy_s(newstr,StrAppend(buf));
	SetStr(newstr);
}
void TcString::operator += (const unsigned int num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%d"), num);

	TCHAR newstr[MAX_STRING_LEN + 1];
	_tcscpy_s(newstr, StrAppend(buf));
	SetStr(newstr);
}
void TcString::operator += (const float num)
{
	TCHAR buf[32];
	_stprintf_s(buf, _T("%.6f"), num);

	TCHAR newstr[MAX_STRING_LEN + 1];
	_tcscpy_s(newstr, StrAppend(buf));
	SetStr(newstr);
}
void TcString::operator += (bool b)
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

WCHAR* TcString::CharToWchar(char* chr,WCHAR* buf = NULL)
{
	int w_CharSize = MultiByteToWideChar (CP_ACP, 0, chr, -1, NULL, 0);
	buf[MAX_STRING_LEN+1];
	MultiByteToWideChar (CP_ACP, 0, chr, w_CharSize*2, buf, w_CharSize);
	buf[w_CharSize-1]='\0';
	return buf;
}
char* TcString::WcharToChar(WCHAR* chr,char* buf = NULL)
{	
	int CharSize = WideCharToMultiByte(CP_ACP,NULL,chr,-1,NULL,0,NULL,NULL);
	buf[MAX_STRING_LEN+1] ;
	WideCharToMultiByte(CP_ACP, NULL, chr, (int)wcslen(chr), buf, CharSize, NULL, NULL);
	buf[CharSize-1] = '\0';
	return buf ;
}

WCHAR* TcString::GetWideChar()
{
	#ifdef _UNICODE
		return str;
	#else
		WCHAR Buf[MAX_STRING_LEN+1];
		wcscpy_s(Buf,MAX_STRING_LEN+1,CharToWchar(str));
		/*
		int w_CharSize = MultiByteToWideChar (CP_ACP, 0, str, -1, NULL, 0);
		
		MultiByteToWideChar (CP_ACP, 0, str, w_CharSize, Buf, w_CharSize);  
		Buf[w_CharSize-1]='\0';
		*/
		return Buf;
	#endif		
}
char* TcString::GetMultiByte(char* buf = NULL)
{
	#ifdef _UNICODE
		buf[MAX_STRING_LEN+1] ;
		strcpy_s(buf,MAX_STRING_LEN+1,WcharToChar(str));
		return buf ;
		/*
		int CharSize = WideCharToMultiByte(CP_ACP,NULL,str,-1,NULL,0,NULL,NULL);
		
		WideCharToMultiByte(CP_ACP, NULL, str, wcslen(str), buf, CharSize, NULL, NULL);
		buf[CharSize-1] = '\0';
		return buf ;
		*/
	#else
		return str ;
	#endif
}

void TcString::WriteToWideChar(FILE* pFile)
{
	WCHAR buf[MAX_STRING_LEN+1] ;
	wcscpy_s(buf,MAX_STRING_LEN+1,GetWideChar());
	int CharSize = int(wcslen(buf)+1);
	fwrite (&CharSize,sizeof(int), 1, pFile) ;
	fwrite (&buf,CharSize,1,pFile) ;
}
void TcString::WriteToMultiByte(FILE* pFile)
{
	char buf[MAX_STRING_LEN+1] ;
	strcpy_s(buf,MAX_STRING_LEN+1,GetMultiByte());
	int CharSize = int(strlen(buf)+1);
	fwrite (&CharSize,sizeof(int), 1, pFile) ;
	fwrite (&buf,CharSize,1,pFile) ;
/*
	#ifdef _UNICODE
		int CharSize = WideCharToMultiByte(CP_ACP,NULL,str,-1,NULL,0,NULL,NULL);
		fwrite (&CharSize,sizeof(int), 1, pFile) ;

		char buf[MAX_STRING_LEN+1] ;

		WideCharToMultiByte(CP_ACP, NULL, str, wcslen(str), buf, CharSize, NULL, NULL);
		buf[CharSize-1] = '\0';
			
		fwrite (&buf,CharSize,1,pFile) ;
	#else
		int CharSize = strlen(str)+1;
		fwrite (&CharSize,sizeof(int), 1, pFile) ;
		fwrite (&str,CharSize,1,pFile) ;
	#endif
*/
}
void TcString::ReadFromMultiByte(FILE* pFile)
{
	#ifdef _UNICODE
		int CharSize;
		fread (&CharSize,sizeof(int), 1, pFile) ;
		char buf[MAX_STRING_LEN];
		fread (&buf,CharSize,1,pFile) ;
		buf[CharSize-1] = '\0';
			

		WCHAR Buf[MAX_STRING_LEN+1];
		wcscpy_s(Buf,MAX_STRING_LEN+1,CharToWchar(buf));
		
/*
		int w_CharSize = MultiByteToWideChar (CP_ACP, 0, buf, -1, NULL, 0);
		WCHAR Buf[MAX_STRING_LEN+1];

		MultiByteToWideChar (CP_ACP, 0, buf, w_CharSize, Buf, w_CharSize);  
		Buf[w_CharSize-1]='\0';
*/

		SetStr(Buf);
	#else
		int CharSize;
		fread (&CharSize,sizeof(int), 1, pFile) ;
		char Buf[MAX_STRING_LEN];
		fread (&Buf,CharSize, 1, pFile) ;
		Buf[CharSize-1]='\0';

		SetStr(Buf);
	#endif
}
void TcString::ReadFromWideChar(FILE* pFile)
{
	#ifdef _UNICODE
		int CharSize;
		fread (&CharSize,sizeof(int), 1, pFile) ;
		WCHAR Buf[MAX_STRING_LEN];
		fread (&Buf,CharSize, 1, pFile) ;
		Buf[CharSize-1]='\0';
		SetStr(Buf);
	#else
		int CharSize;
		fread (&CharSize,sizeof(int), 1, pFile) ;
		WCHAR buf[MAX_STRING_LEN];
		fread (&buf,CharSize,1,pFile) ;
		buf[CharSize-1] = '\0';
			

		char Buf[MAX_STRING_LEN+1];
		strcpy_s(Buf,MAX_STRING_LEN+1,WcharToChar(buf));	
		SetStr(Buf);

	#endif
}