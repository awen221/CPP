#ifndef _POINT_BASE_H_
#define _POINT_BASE_H_

///template class不能拆分.cpp,會編譯不過
template<class P>
class PointBase
{
private:

protected:
	//座標
	P X;
	P Y;

public:
	PointBase()
	{
	}
	~PointBase()
	{
	}

	virtual void Init()
	{
		X = 0;
		Y = 0;
	}

	//XY 存取
	void SetX(const P x) { X = x; }
	P GetX() { return X; }
	void SetY(const P y) { Y = y; }
	P GetY() { return Y; }
	void Set(const P x, const P y) { X=x; Y=y; }
	void Get(P& x, P& y) { x = X; y = Y; }

	//Point 存取
	PointBase<P> Get() { return this; }
	void Set(const PointBase<P> pos) { this = pos; }

	//ShiftXY
	void ShiftX(const P& dx) { X += dx; }
	void ShiftY(const P& dy) { Y += dy; }
	void Shift(const P& dx, const P& dy) { ShiftX(dx); ShiftY(dy); }

	//Distance
	P GetDistance(const P& tx, const P& ty) { return sqrt((X - tx)*(X - tx) + (Y - ty)*(Y - ty)); }
	P GetDistance(const PointBase<P>& target) { return GetDistance(target.X, target.Y); }

	//Step 往目標步進
	bool Step(const P& tx,const P& ty, const P& speed)
	{
		P distance = GetDistance(tx, ty);
		if (speed >= distance)
		{
			Set(tx, ty);
			//已到達
			return true;
		}

		P dx = (tx - X)*speed / distance;
		P dy = (ty - Y)*speed / distance;
		Shift(dx, dy);
		return false;
	}
	bool Step(const PointBase<P>& target, const P& speed) { return Step(target.X, target.Y, speed); }

};
typedef PointBase<double> PointBaseD;

#endif