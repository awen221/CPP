#pragma once
#include <math.h>
///template class不能拆分.cpp,會編譯不過
namespace MATH
{
	template<class ValueType>
	class Point_Template
	{
	protected:
		ValueType X;
		ValueType Y;
	public:
		Point_Template() {}
		~Point_Template(){}

		virtual void Init()
		{
			X = 0;
			Y = 0;
		}

		ValueType GetX() { return X; }
		ValueType GetY() { return Y; }
		void Get(ValueType& x, ValueType& y)
		{
			x = GetX();
			y = GetY();
		}

		void SetX(const ValueType& x) { X = x; }
		void SetY(const ValueType& y) { Y = y; }
		void Set(const ValueType& x, const ValueType& y)
		{
			SetX(x);
			SetY(y);
		}
		void ShiftX(const ValueType& dx)
		{
			SetX(X + dx);
		}
		void ShiftY(const ValueType& dy)
		{
			SetY(Y + dy);
		}
		void Shift(const ValueType& dx, const ValueType& dy)
		{
			ShiftX(dx);
			ShiftY(dy);
		}

		ValueType GetDistance(const ValueType& tx, const ValueType& ty)
		{
			return sqrt((X - tx)*(X - tx) + (Y - ty)*(Y - ty));
		}
		ValueType GetDistance(const Point_Template<ValueType>& target)
		{
			return GetDistance(target.X, target.Y);
		}

		bool Step(const ValueType& tx, const ValueType& ty, const ValueType& speed)
		{
			ValueType distance = GetDistance(tx, ty);
			if (speed >= distance)
			{
				Set(tx, ty);
				//已到達
				return true;
			}

			ValueType dx = (tx - X)*speed / distance;
			ValueType dy = (ty - Y)*speed / distance;
			Shift(dx, dy);
			return false;
		}
		bool Step(const Point_Template<ValueType>& target, const ValueType& distance)
		{
			return Step(target.X, target.Y, distance);
		}


		//指定方向速度移動
		void MoveToDirection(double speed, const double& radian)
		{
			double shiftX = cos(radian)*speed;
			double shiftY = -sin(radian)*speed;
			Shift(shiftX, shiftY);
		}
		//取得與指定座標之夾角
		double GetRadianFromPoint(Point_Template<ValueType> target)
		{
			double _radian;

			//笛卡兒座標系(第一象限)公式
			_radian = atan2(target.GetY() - GetY(), target.GetX() - GetX());
			//轉成Windows座標系(第三象限)要加負號
			_radian = -_radian;

			return _radian;
		}

	};
}