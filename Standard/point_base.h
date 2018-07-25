#ifndef _POINT_BASE_H_
#define _POINT_BASE_H_

///template class不能拆分.cpp,會編譯不過
template<class ValueType>
class PointBase
{

public:
	PointBase()
	{
	}
	~PointBase()
	{
	}

protected:
	ValueType X;
	ValueType Y;
public:
	virtual void Init()
	{
		X = 0;
		Y = 0;
	}

	void SetX(const ValueType& x) 
	{
		X = x; 
	}
	ValueType GetX() 
	{
		return X; 
	}
	void SetY(const ValueType& y) 
	{
		Y = y; 
	}
	ValueType GetY() 
	{
		return Y; 
	}
	void Set(const ValueType& x, const ValueType& y) 
	{
		X = x;
		Y = y; 
	}
	void Get(ValueType& x, ValueType& y) 
	{
		x = X;
		y = Y;
	}
	void ShiftX(const ValueType& dx) 
	{
		X += dx; 
	}
	void ShiftY(const ValueType& dy) 
	{ 
		Y += dy; 
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
	ValueType GetDistance(const PointBase<ValueType>& target) 
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
	bool Step(const PointBase<ValueType>& target, const ValueType& distance) 
	{
		return Step(target.X, target.Y, distance); 
	}
};

typedef PointBase<double> PointBaseD;

#endif