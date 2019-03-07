//#ifdef Project1_EXPORTS //同專案名稱，只是後面固定為_EXPORTS
//#define FORCSHARPCALL_API __declspec(dllexport) //請注意！正確的是Export要亮起
//#else
//#define FORCSHARPCALL_API __declspec(dllimport)
//#endif

#define FORCSHARPCALL_API __declspec(dllexport) //請注意！正確的是Export要亮起

#include "Calculate.h"

//可以將class的物件宣告在外面變成全域
//Calculate cal;

extern "C" FORCSHARPCALL_API int Add(int a, int b)
{
	Calculate cal;//宣告在function內，只有該function能使用
	return cal.Addition(a, b);
}

extern "C" FORCSHARPCALL_API int Sub(int a, int b)
{
	Calculate cal;//宣告在function內，只有該function能使用
	return cal.Subtraction(a, b);
}

extern "C" FORCSHARPCALL_API int Multi(int a, int b)
{
	Calculate cal;//宣告在function內，只有該function能使用
	return cal.Multiplication(a, b);
}

extern "C" FORCSHARPCALL_API float Div(int a, int b)
{
	Calculate cal;//宣告在function內，只有該function能使用
	return cal.Division(a, b);
}