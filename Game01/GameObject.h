#pragma once

#include "Point_Template.h"
#include "radian.h"
using PointBaseD = MATH::Point_Template<double>;
using Radian = MATH::Radian;

class GameObject :public PointBaseD, public Radian
{
private:
protected:
	double Radius;
	virtual double GetDefaultRadius();
public:
	double GetRadius();
	void SetRadius(double);

protected:
	bool Destroyed;
public:
	virtual bool IsDestroyed();

public:
	GameObject();
	~GameObject();
	virtual void Init();
};

