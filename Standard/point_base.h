#ifndef POINT_BASE_H
#define POINT_BASE_H

#include <math.h>

///template class������.cpp,�|�sĶ���L
namespace Point_Template
{
	template<class ValueType>
	class Point_Template_Class
	{
	protected:
		ValueType X;
		ValueType Y;
	public:
		Point_Template_Class() {}
		~Point_Template_Class(){}

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
		ValueType GetDistance(const Point_Template_Class<ValueType>& target)
		{
			return GetDistance(target.X, target.Y);
		}

		bool Step(const ValueType& tx, const ValueType& ty, const ValueType& speed)
		{
			ValueType distance = GetDistance(tx, ty);
			if (speed >= distance)
			{
				Set(tx, ty);
				//�w��F
				return true;
			}

			ValueType dx = (tx - X)*speed / distance;
			ValueType dy = (ty - Y)*speed / distance;
			Shift(dx, dy);
			return false;
		}
		bool Step(const Point_Template_Class<ValueType>& target, const ValueType& distance)
		{
			return Step(target.X, target.Y, distance);
		}


		//���w��V�t�ײ���
		void MoveToDirection(double speed, const double& radian)
		{
			double shiftX = cos(radian)*speed;
			double shiftY = -sin(radian)*speed;
			Shift(shiftX, shiftY);
		}
		//���o�P���w�y�Ф�����
		double GetRadianFromPoint(Point_Template_Class<ValueType> target)
		{
			double _radian;

			//�åd��y�Шt(�Ĥ@�H��)����
			_radian = atan2(target.GetY() - self.GetY(), target.GetX() - self.GetX());
			//�নWindows�y�Шt(�ĤT�H��)�n�[�t��
			_radian = -_radian;

			return _radian;
		}

	};
}

#endif