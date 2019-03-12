#ifndef TCHAR_STR_H
#define TCHAR_STR_H

#include <tchar.h>


class TCHAR_STR
{
private:
	TCHAR* str;	//pointer

	void DelStr();
	void SetStr(const TCHAR*);
	bool CmpStr(const TCHAR*);
	const TCHAR* StrAppend(const TCHAR*);

public:
	TCHAR_STR();
	TCHAR_STR(const TCHAR*);
	~TCHAR_STR();

	int len;	//size of tchar
	operator const TCHAR*();

	void operator = (const TCHAR*);
	void operator = (const TCHAR_STR&);
	void operator = (const int);
	void operator = (const float);
	
	bool operator == (const TCHAR*);
	bool operator == (const TCHAR_STR&);
	bool operator == (const int);
	bool operator == (const float);

	const TCHAR* operator + (const TCHAR*);
	const TCHAR* operator + (const TCHAR_STR&);
	const TCHAR* operator + (const int);
	const TCHAR* operator + (const float);

	void operator += (const TCHAR*);
	void operator += (const TCHAR_STR&);
	void operator += (const int);
	void operator += (const float);

	void operator += (const unsigned int);
	void operator += (const bool);
};

#endif