// CppMathFunc.h
#pragma once
namespace CppMathFunc 
{
	public ref class TEST
	{
	public:
		TEST() {}
		int T = 10;

	};

	public ref class Arithmetics:TEST
	{
	public:
		// TODO: �b���[�J�o�����O����k�C
		Arithmetics();
		~Arithmetics();
		double Add(double , double );
		double Subtract(double , double );
		double Multiply(double , double );
		double Divide(double , double );
		int i;


		TEST TTT;
	};



}