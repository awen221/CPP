#include"radian.h"

//下面兩行一起寫 M_PI才會有效
#define _USE_MATH_DEFINES
#include <math.h>
const double PI = M_PI;

const int Degree180 = 180;

namespace MATH
{
	void Radian::Init()
	{
		radian = 0;
	}

	double Radian::GetDegreeFromRadian(const double& radian)
	{
		return radian * Degree180 / PI;
	}
	double Radian::GetRadianFromDegree(const double& degree)
	{
		return  degree / Degree180 * PI;
	}

	double Radian::GetDegree()
	{
		return GetDegreeFromRadian(radian);
	}

	double Radian::GetRadian()
	{
		return radian;
	}
	void Radian::SetRadian(const double& _radian)
	{
		radian = _radian;
	}
	void Radian::ShfitRadian(const double& _radian)
	{
		SetRadian(radian + _radian);
	}
	void Radian::SetDirectionUp()
	{
		SetRadian(PI / 2);
	}
	void Radian::SetDirectionDown()
	{
		SetRadian(-PI / 2);
	}
	void Radian::SetDirectionLeft()
	{
		SetRadian(PI);
	}
	void Radian::SetDirectionRight()
	{
		SetRadian(0);
	}
	void Radian::SetDegree(const double& degree)
	{
		double _radian = GetRadianFromDegree(degree);
		SetRadian(_radian);
	}
	void Radian::ShfitDegree(const double& degree)
	{
		double _radian = GetRadianFromDegree(degree);
		SetRadian(radian + _radian);
	}
}