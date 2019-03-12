#include "TString.h"
#include <tchar.h>

namespace TString
{
	tstring_base tstring::get_from(const TCHAR* val)
	{
		return tstring_base(val);
	}
	tstring_base tstring::get_from(const tstring_base val)
	{
		return tstring_base(val);
	}
	tstring_base tstring::get_from(const int val)
	{
		return to_tstring<int>(val);
	}
	tstring_base tstring::get_from(const unsigned int val)
	{
		return to_tstring<unsigned int>(val);
	}
	tstring_base tstring::get_from(const float val)
	{
		return to_tstring<float>(val);
	}


	void tstring::set(const TCHAR* val)
	{
		setT<const TCHAR*>(val);
	}
	void tstring::set(const tstring_base val)
	{
		setT<tstring_base>(val);
	}
	void tstring::set(const int val)
	{
		setT<int>(val);
	}
	void tstring::set(const unsigned int val)
	{
		setT<unsigned int>(val);
	}
	void tstring::set(const float val)
	{
		setT<float>(val);
	}


	tstring_base tstring::append(const TCHAR* val)
	{
		return str.append(val);
	}
	tstring_base tstring::append(const tstring_base val)
	{
		return str.append(val);
	}
	tstring_base tstring::append(const int val)
	{
		return str.append(get_from(val));
	}
	tstring_base tstring::append(const unsigned int val)
	{
		return str.append(get_from(val));
	}
	tstring_base tstring::append(const float val)
	{
		return str.append(get_from(val));
	}

	tstring::operator const tstring_base()
	{
		return str;
	}
	tstring::operator const TCHAR*()
	{
		return str.c_str();
	}

	unsigned int tstring::length()
	{
		return str.length();
	}

	tstring::tstring(const TCHAR* val)
	{
		set(val);
	}
	tstring::tstring(const tstring_base val)
	{
		set(val);
	}
	tstring::tstring(const int val)
	{
		set(val);
	}
	tstring::tstring(const unsigned int val)
	{
		set(val);
	}
	tstring::tstring(const float val)
	{
		set(val);
	}

	void tstring::operator = (const TCHAR* val)
	{
		set(val);
	}
	void tstring::operator = (const tstring_base val)
	{
		set(val);
	}
	void tstring::operator = (const int val)
	{
		set(val);
	}
	void tstring::operator = (const unsigned int val)
	{
		set(val);
	}
	void tstring::operator = (const float val)
	{
		set(val);
	}

	tstring_base tstring::operator + (const TCHAR* val)
	{
		return append(val);
	}
	tstring_base tstring::operator + (const tstring_base val)
	{
		return append(val);
	}
	tstring_base tstring::operator + (const int val)
	{
		return append(val);
	}
	tstring_base tstring::operator + (const unsigned int val)
	{
		return append(val);
	}
	tstring_base tstring::operator + (const float val)
	{
		return append(val);
	}

	void tstring::operator += (const TCHAR* val)
	{
		set(append(val));
	}
	void tstring::operator += (const tstring_base val)
	{
		set(append(val));
	}
	void tstring::operator += (const int val)
	{
		set(append(val));
	}
	void tstring::operator += (const unsigned int val)
	{
		set(append(val));
	}
	void tstring::operator += (const float val)
	{
		set(append(val));
	}
}