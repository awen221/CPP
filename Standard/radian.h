#ifndef _RADIAN_H_
#define _RADIAN_H_

//�U�����@�_�g M_PI�~�|����
#define _USE_MATH_DEFINES
#include <math.h>
const double PI = M_PI;

//#include "point_base.h"
template<class ValueType>
class PointBase;

class Radian
{
private:
	//PI*0 ~ PI*2
	double radian;
protected:
	virtual void Init();
public:
	template<class T>
	static void MoveToDirection(PointBase<T>& self, double speed, const double& radian)
	{
		double shiftX = cos(radian)*speed;
		double shiftY = -sin(radian)*speed;
		self.Shift(shiftX, shiftY);
	}

	template<class T>
	void MoveToCurrentDirection(PointBase<T>& self, double speed)
	{
		MoveToDirection<T>(self, speed, radian);
	}
	//�ثe��V���ܩ��ثe��V��������V����
	template<class T>
	void MoveToShiftDirection(PointBase<T>& self, double speed, double shift_radian)
	{
		MoveToDirection<T>(self,speed, radian + shift_radian);
	}

	//���ثe��V���k������
	template<class T>
	void DirRightMove(PointBase<T>& self, double speed)
	{
		MoveToShiftDirection<T>(self, speed, PI / 2);
	}
	//���ثe��V����������
	template<class T>
	void DirLeftMove(PointBase<T>& self, double speed)
	{
		MoveToShiftDirection<T>(self, speed, -PI / 2);
	}
	//���o�P���w�y�Ф�����
	template<class T>
	double GetRadianFromPoint(PointBase<T> self, PointBase<T> target)
	{
		double _radian;

		//�åd��y�Шt(�Ĥ@�H��)����
		_radian = atan2(target.GetY() - self.GetY(), target.GetX() - self.GetX());
		//�নWindows�y�Шt(�ĤT�H��)�n�[�t��
		_radian = -_radian;

		return _radian;
	}


	//�����੷��
	static double GetDegreeFromRadian(const double&);
	//�����ਤ��
	static double GetRadianFromDegree(const double&);

	double GetRadian();
	double GetDegree();
	void SetRadian(const double& );
	void SetDegree(const double& );
	void ShfitRadian(const double& );
	void ShfitDegree(const double& );

	void SetDirectionRight();
	void SetDirectionUp();
	void SetDirectionLeft();
	void SetDirectionDown();

};

#endif