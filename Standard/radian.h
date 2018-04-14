#ifndef _RADIAN_H_
#define _RADIAN_H_

//�U�����@�_�g M_PI�~�|����
#define _USE_MATH_DEFINES
#include <math.h>
const double PI = M_PI;

#include "point_base.h"

class Radian
{
private:
	//PI*0 ~ PI*2
	double radian;
	static const int Degree180 = 180;
protected:
	virtual void Init()
	{
		radian = 0;
	}
public:
	//�����w��V����
	template<class T>
	static void MoveToDirection(PointBase<T>& self, double speed, const double& radian)
	{
		double shiftX = cos(radian)*speed;
		double shiftY = -sin(radian)*speed;
		self.Shift(shiftX, shiftY);
	}

	//���ثe��V����
	template<class T>
	void MoveToCurrentDirection(PointBase<T>& self,double speed)
	{
		MoveToDirection<T>(self, speed, radian);
	}
	//�ثe��V���ܩ��ثe��V��������V����
	template<class T>
	void MoveToShiftDirection(double speed, double radian)
	{
		MoveToDirection<T>(speed, radian + radian);
	}
	//���ثe��V���k������
	template<class T>
	void DirRightMove(double speed)
	{
		MoveToShiftDirection<T>(speed, PI / 2);
	}
	//���ثe��V����������
	template<class T>
	void DirLeftMove(double speed)
	{
		MoveToShiftDirection<T>(speed, -PI / 2);
	}
	//���o�P���w�y�Ф�����
	template<class T>
	double GetRadianFromPoint(PointBase<T> self, PointBase<T> target)
	{
		double radian;

		//�åd��y�Шt(�Ĥ@�H��)����
		radian = atan2(target.GetY() - self.GetY(), target.GetX() - self.GetX());
		//�নWindows�y�Шt(�ĤT�H��)�n�[�t��
		radian = -radian;

		return radian;
	}


	//�����੷��
	static double GetDegreeFromRadian(const double& radian)
	{
		return radian * Degree180 / PI;
	}
	//�����ਤ��
	static double GetRadianFromDegree(const double& degree)
	{
		return  degree / Degree180 * PI;
	}

	double GetRadian() 
	{
		return radian; 
	}
	double GetDegree() 
	{ 
		return GetDegreeFromRadian(radian); 
	}
	void SetRadian(const double& _radian) 
	{ 
		radian = _radian;
	}
	void SetDegree(const double& degree) 
	{ 
		radian = GetRadianFromDegree(degree); 
	}
	void ShfitRadian(const double& _radian)
	{ 
		radian += _radian;
	}
	void ShfitDegree(const double& degree) 
	{ 
		radian += GetRadianFromDegree(degree); 
	}

	void SetDirectionRight()
	{
		radian = 0; 
	}
	void SetDirectionUp() 
	{ 
		radian = PI / 2; 
	}
	void SetDirectionLeft()
	{
		radian = PI; 
	}
	void SetDirectionDown()
	{
		radian = - PI / 2; 
	}

};


#endif