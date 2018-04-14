#ifndef _RADIAN_H_
#define _RADIAN_H_

//下面兩行一起寫 M_PI才會有效
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
	//往指定方向移動
	template<class T>
	static void MoveToDirection(PointBase<T>& self, double speed, const double& radian)
	{
		double shiftX = cos(radian)*speed;
		double shiftY = -sin(radian)*speed;
		self.Shift(shiftX, shiftY);
	}

	//往目前方向移動
	template<class T>
	void MoveToCurrentDirection(PointBase<T>& self,double speed)
	{
		MoveToDirection<T>(self, speed, radian);
	}
	//目前方向不變往目前方向的偏移方向移動
	template<class T>
	void MoveToShiftDirection(double speed, double radian)
	{
		MoveToDirection<T>(speed, radian + radian);
	}
	//往目前方向之右側平移
	template<class T>
	void DirRightMove(double speed)
	{
		MoveToShiftDirection<T>(speed, PI / 2);
	}
	//往目前方向之左側平移
	template<class T>
	void DirLeftMove(double speed)
	{
		MoveToShiftDirection<T>(speed, -PI / 2);
	}
	//取得與指定座標之夾角
	template<class T>
	double GetRadianFromPoint(PointBase<T> self, PointBase<T> target)
	{
		double radian;

		//笛卡兒座標系(第一象限)公式
		radian = atan2(target.GetY() - self.GetY(), target.GetX() - self.GetX());
		//轉成Windows座標系(第三象限)要加負號
		radian = -radian;

		return radian;
	}


	//角度轉弧度
	static double GetDegreeFromRadian(const double& radian)
	{
		return radian * Degree180 / PI;
	}
	//弧度轉角度
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