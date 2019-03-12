#pragma once
#include <string>
#include <tchar.h>

namespace TString
{
#if defined _UNICODE || defined UNICODE
	using tstring_base = std::wstring;
	template <class T>
	tstring_base to_tstring(T val) { return std::to_wstring(val); }
#else
	using tstring_base = std::string;
	template <class T>
	tstring_base to_tstring(T val) { return std::to_string(val); }
#endif

	class tstring
	{
	private:
		tstring_base str;

		tstring_base get_from(const TCHAR*);
		tstring_base get_from(const tstring_base);
		tstring_base get_from(const int);
		tstring_base get_from(const unsigned int);
		tstring_base get_from(const float);


		template <class T>
		void setT(const T val)
		{
			str = get_from(val);
		}

		void set(const TCHAR*);
		void set(const tstring_base);
		void set(const int);
		void set(const unsigned int);
		void set(const float);


		tstring_base append(const TCHAR*);
		tstring_base append(const tstring_base);
		tstring_base append(const int);
		tstring_base append(const unsigned int);
		tstring_base append(const float);

	public:
		operator const tstring_base();
		operator const TCHAR*();

		unsigned int length();

		tstring(const TCHAR* );
		tstring(const tstring_base);
		tstring(const int);
		tstring(const unsigned int);
		tstring(const float);

		void operator = (const TCHAR*);
		void operator = (const tstring_base);
		void operator = (const int);
		void operator = (const unsigned int);
		void operator = (const float);

		tstring_base operator + (const TCHAR*);
		tstring_base operator + (const tstring_base);
		tstring_base operator + (const int);
		tstring_base operator + (const unsigned int);
		tstring_base operator + (const float);

		void operator += (const TCHAR*);
		void operator += (const tstring_base);
		void operator += (const int);
		void operator += (const unsigned int);
		void operator += (const float);
	};

}