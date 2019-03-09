#include"radian.h"

//下面兩行一起寫 M_PI才會有效
#define _USE_MATH_DEFINES
#include <math.h>
const double PI = M_PI;

static const int Degree180 = 180;

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

double Radian::GetRadian()
{
	return radian;
}
double Radian::GetDegree()
{
	return GetDegreeFromRadian(radian);
}

void Radian::SetRadian(const double& _radian)
{
	radian = _radian;
}
void Radian::SetDegree(const double& degree)
{
	radian = GetRadianFromDegree(degree);
}
void Radian::ShfitRadian(const double& _radian)
{
	radian += _radian;
}
void Radian::ShfitDegree(const double& degree)
{
	radian += GetRadianFromDegree(degree);
}

void Radian::SetDirectionUp()
{
	radian = PI / 2;
}
void Radian::SetDirectionDown()
{
	radian = -PI / 2;
}
void Radian::SetDirectionLeft()
{
	radian = PI;
}
void Radian::SetDirectionRight()
{
	radian = 0;
}