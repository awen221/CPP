#ifndef _RADIAN_H_
#define _RADIAN_H_

//下面兩行一起寫 M_PI才會有效
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
	//目前方向不變往目前方向的偏移方向移動
	template<class T>
	void MoveToShiftDirection(PointBase<T>& self, double speed, double shift_radian)
	{
		MoveToDirection<T>(self,speed, radian + shift_radian);
	}

	//往目前方向之右側平移
	template<class T>
	void DirRightMove(PointBase<T>& self, double speed)
	{
		MoveToShiftDirection<T>(self, speed, PI / 2);
	}
	//往目前方向之左側平移
	template<class T>
	void DirLeftMove(PointBase<T>& self, double speed)
	{
		MoveToShiftDirection<T>(self, speed, -PI / 2);
	}
	//取得與指定座標之夾角
	template<class T>
	double GetRadianFromPoint(PointBase<T> self, PointBase<T> target)
	{
		double _radian;

		//笛卡兒座標系(第一象限)公式
		_radian = atan2(target.GetY() - self.GetY(), target.GetX() - self.GetX());
		//轉成Windows座標系(第三象限)要加負號
		_radian = -_radian;

		return _radian;
	}


	//角度轉弧度
	static double GetDegreeFromRadian(const double&);
	//弧度轉角度
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