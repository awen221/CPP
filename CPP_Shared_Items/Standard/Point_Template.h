#pragma once
#include <math.h>
///template class不能拆分.cpp,會編譯不過
namespace MATH
{
	template<class T>
	class Point_Template
	{
	protected:
		T X;
		T Y;
	public:
		Point_Template() {}
		~Point_Template(){}

		virtual void Init()
		{
			X = 0;
			Y = 0;
		}

		T GetX() { return X; }
		T GetY() { return Y; }
		void Get(T& x, T& y)
		{
			x = GetX();
			y = GetY();
		}

		void SetX(const T& x) { X = x; }
		void SetY(const T& y) { Y = y; }
		void Set(const T& x, const T& y)
		{
			SetX(x);
			SetY(y);
		}
		void ShiftX(const T& dx)
		{
			SetX(X + dx);
		}
		void ShiftY(const T& dy)
		{
			SetY(Y + dy);
		}
		void Shift(const T& dx, const T& dy)
		{
			ShiftX(dx);
			ShiftY(dy);
		}

		T GetDistance(const T& tx, const T& ty)
		{
			return sqrt((X - tx)*(X - tx) + (Y - ty)*(Y - ty));
		}
		T GetDistance(const Point_Template<T>& target)
		{
			return GetDistance(target.X, target.Y);
		}

		bool Step(const T& tx, const T& ty, const T& speed)
		{
			T distance = GetDistance(tx, ty);
			if (speed >= distance)
			{
				Set(tx, ty);
				//已到達
				return true;
			}

			T dx = (tx - X)*speed / distance;
			T dy = (ty - Y)*speed / distance;
			Shift(dx, dy);
			return false;
		}
		bool Step(const Point_Template<T>& target, const T& distance)
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
		double GetRadianFromPoint(Point_Template<T> target)
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