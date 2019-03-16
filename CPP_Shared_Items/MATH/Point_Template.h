#pragma once

#include <math.h>
///template class不能拆分.cpp,會編譯不過
namespace MATH
{
	template<class T>
	class Point_Template
	{
	private:
	protected:
		T X;
		T Y;
	public:
		Point_Template() :X(0), Y(0) {}
		Point_Template(const T& x, const T& y) { Set(x, y); }
		Point_Template(const Point_Template<T>& p) { Set(p); }
		~Point_Template() {}

		const T& GetX()const { return X; }
		const T& GetY()const { return Y; }

		void SetX(const T& x) { X = x; }
		void SetY(const T& y) { Y = y; }
		void Set(const T& x, const T& y) 
		{
			SetX(x);
			SetY(y); 
		}
		void Set(const Point_Template<T>& p) { Set(p.X, p.Y); }

		void ShiftX(const T& dx) { SetX(X + dx); }
		void ShiftY(const T& dy) { SetY(Y + dy); }
		void Shift(const T& dx, const T& dy) 
		{ 
			ShiftX(dx); 
			ShiftY(dy); 
		}
		void Shift(const Point_Template<T>& p) { Shift(p.X, p.Y); }



		T GetDistanceFrom(const T& tx, const T& ty)const
		{
			T sx = (X - tx)*(X - tx);
			T sy = (Y - ty)*(Y - ty);
			return sqrt(sx + sy);
		}
		T GetDistanceFrom(const Point_Template<T>& target)const{ return GetDistanceFrom(target.X, target.Y); }

		//往指定座標移動
		bool MoveTo(const T& tx, const T& ty, const T& step)
		{
			T distance = GetDistanceFrom(tx, ty);
			if (step >= distance)
			{
				//已到達
				Set(tx, ty);
				return true;
			}

			T dx = (tx - X)*step / distance;
			T dy = (ty - Y)*step / distance;
			Shift(dx, dy);
			return false;
		}
		bool MoveTo(const Point_Template<T>& target, const T& step) { return MoveTo(target.X, target.Y, step); }


		//往指定角度移動
		void MoveTo(const double& radian, const T& step)
		{
			double sx = cos(radian)*step;
			double sy = -sin(radian)*step;
			Shift(sx, sy);
		}

		//取得與指定座標之夾角角度
		double GetRadianFrom(const T& tx, const T& ty)const
		{
			//笛卡兒座標系(第一象限)公式
			double _radian = atan2(ty - Y, tx - X);

			//轉成Windows座標系(第三象限)要加負號
			return -_radian;
		}
		double GetRadianFrom(const Point_Template<T>& target)const { return GetRadianFrom(target.X, target.Y); }
	};
}