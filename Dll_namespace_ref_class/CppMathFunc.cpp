#include "CppMathFunc.h"




namespace CppMathFunc {

	Arithmetics::Arithmetics()
	{
	}

	Arithmetics::~Arithmetics()
	{
	}

	double Arithmetics::Add(double x, double y)
	{
		return x + y;
	}
	double Arithmetics::Subtract(double a, double b)
	{
		return a - b;
	}
	double Arithmetics::Multiply(double x, double y)
	{
		return x * y;
	}
	double Arithmetics::Divide(double a, double b)
	{
		if (b == 0)
		{
			return -1;
		}

		return a / b;
	}

}
