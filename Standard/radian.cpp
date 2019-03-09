#include"radian.h"

//下面兩行一起寫 M_PI才會有效
#define _USE_MATH_DEFINES
#include <math.h>
const double PI = M_PI;

const int Degree180 = 180;

namespace Radian
{
	void Radian_Class::Init()
	{
		radian = 0;
	}

	double Radian_Class::GetDegreeFromRadian(const double& radian)
	{
		return radian * Degree180 / PI;
	}
	double Radian_Class::GetRadianFromDegree(const double& degree)
	{
		return  degree / Degree180 * PI;
	}

	double Radian_Class::GetDegree()
	{
		return GetDegreeFromRadian(radian);
	}

	double Radian_Class::GetRadian()
	{
		return radian;
	}
	void Radian_Class::SetRadian(const double& _radian)
	{
		radian = _radian;
	}
	void Radian_Class::ShfitRadian(const double& _radian)
	{
		SetRadian(radian + _radian);
	}
	void Radian_Class::SetDirectionUp()
	{
		SetRadian(PI / 2);
	}
	void Radian_Class::SetDirectionDown()
	{
		SetRadian(-PI / 2);
	}
	void Radian_Class::SetDirectionLeft()
	{
		SetRadian(PI);
	}
	void Radian_Class::SetDirectionRight()
	{
		SetRadian(0);
	}
	void Radian_Class::SetDegree(const double& degree)
	{
		double _radian = GetRadianFromDegree(degree);
		SetRadian(_radian);
	}
	void Radian_Class::ShfitDegree(const double& degree)
	{
		double _radian = GetRadianFromDegree(degree);
		SetRadian(radian + _radian);
	}
}