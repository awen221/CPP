//#ifdef Project1_EXPORTS //�P�M�צW�١A�u�O�᭱�T�w��_EXPORTS
//#define FORCSHARPCALL_API __declspec(dllexport) //�Ъ`�N�I���T���OExport�n�G�_
//#else
//#define FORCSHARPCALL_API __declspec(dllimport)
//#endif

#define FORCSHARPCALL_API __declspec(dllexport) //�Ъ`�N�I���T���OExport�n�G�_

#include "Calculate.h"

//�i�H�Nclass������ŧi�b�~���ܦ�����
//Calculate cal;

extern "C" FORCSHARPCALL_API int Add(int a, int b)
{
	Calculate cal;//�ŧi�bfunction���A�u����function��ϥ�
	return cal.Addition(a, b);
}

extern "C" FORCSHARPCALL_API int Sub(int a, int b)
{
	Calculate cal;//�ŧi�bfunction���A�u����function��ϥ�
	return cal.Subtraction(a, b);
}

extern "C" FORCSHARPCALL_API int Multi(int a, int b)
{
	Calculate cal;//�ŧi�bfunction���A�u����function��ϥ�
	return cal.Multiplication(a, b);
}

extern "C" FORCSHARPCALL_API float Div(int a, int b)
{
	Calculate cal;//�ŧi�bfunction���A�u����function��ϥ�
	return cal.Division(a, b);
}