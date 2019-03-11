#pragma once
#include <string>

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
		//unsigned int length;

		tstring_base get_from(const TCHAR* val)
		{
			return tstring_base(val);
		}
		tstring_base get_from(const tstring_base val)
		{
			return tstring_base(val);
		}
		tstring_base get_from(const int val)
		{
			return to_tstring<int>(val);
		}
		tstring_base get_from(const unsigned int val)
		{
			return to_tstring<unsigned int>(val);
		}
		tstring_base get_from(const float val)
		{
			return to_tstring<float>(val);
		}


		template <class T>
		void setT(const T val)
		{
			str = get_from(val);
			//length = str.length();
		}

		void set(const TCHAR* val)
		{
			setT<const TCHAR*>(val);
		}
		void set(const tstring_base val)
		{
			setT<tstring_base>(val);
		}
		void set(const int val)
		{
			setT<int>(val);
		}
		void set(const unsigned int val)
		{
			setT<unsigned int>(val);
		}
		void set(const float val)
		{
			setT<float>(val);
		}


		tstring_base append(const TCHAR* val)
		{
			return str.append(val);
		}
		tstring_base append(const tstring_base val)
		{
			return str.append(val);
		}
		tstring_base append(const int val)
		{
			return str.append(get_from(val));
		}
		tstring_base append(const unsigned int val)
		{
			return str.append(get_from(val));
		}
		tstring_base append(const float val)
		{
			return str.append(get_from(val));
		}

	public:
		operator const tstring_base()
		{
			return str;
		}
		operator const TCHAR*()
		{
			return str.c_str();
		}

		unsigned int len()
		{
			return str.length();
		}

		tstring(const TCHAR* val)
		{
			set(val);
		}
		tstring(const tstring_base val)
		{
			set(val);
		}
		tstring(const int val)
		{
			set(val);
		}
		tstring(const unsigned int val)
		{
			set(val);
		}
		tstring(const float val)
		{
			set(val);
		}

		void operator = (const TCHAR* val)
		{
			set(val);
		}
		void operator = (const tstring_base val)
		{
			set(val);
		}
		void operator = (const int val)
		{
			set(val);
		}
		void operator = (const unsigned int val)
		{
			set(val);
		}
		void operator = (const float val)
		{
			set(val);
		}

		tstring_base operator + (const TCHAR* val)
		{
			return append(val);
		}
		tstring_base operator + (const tstring_base val)
		{
			return append(val);
		}
		tstring_base operator + (const int val)
		{
			return append(val);
		}
		tstring_base operator + (const unsigned int val)
		{
			return append(val);
		}
		tstring_base operator + (const float val)
		{
			return append(val);
		}

		void operator += (const TCHAR* val)
		{
			set(append(val));
		}
		void operator += (const tstring_base val)
		{
			set(append(val));
		}
		void operator += (const int val)
		{
			set(append(val));
		}
		void operator += (const unsigned int val)
		{
			set(append(val));
		}
		void operator += (const float val)
		{
			set(append(val));
		}
	};

}
using namespace TString;