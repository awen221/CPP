#pragma once

#include "Point_Template.h"
#include "radian.h"
using namespace MATH;
using PointBaseD = Point_Template<double>;

class GameObject :public PointBaseD, public Radian
{
protected:
	double Size;
	virtual double GetDefaultSize();
public:
	double GetSize();
	void SetSize(double);

protected:
	bool Destroyed;
public:
	virtual bool IsDestroyed();

public:
	GameObject();
	~GameObject();
	virtual void Init();
	virtual void Work();
	void Rand(double , double , double , double );
};

