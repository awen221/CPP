#pragma once

#include "Point_Template.h"
using PointBaseD = MATH::Point_Template<double>;
#include "radian.h"
using Radian = MATH::Radian;

class GameObject :public PointBaseD, public Radian
{
protected:
	bool bDead = false;

	double Speed;
	double Size;

	virtual double GetDefaultSpeed();
	virtual double GetDefaultSize();
public:
	virtual void Init();

	void Rand(double , double , double , double );

	double GetSpeed();
	void SetSpeed(double );

	void StepToCharacter(const GameObject&);

	double GetSize();
	void SetSize(double );

	

	//取得與指定座標之夾角
	double GetRadianFromPoint(PointBaseD );
	virtual bool IsDead();

	void MoveToCurrentDirection()
	{
		PointBaseD::MoveToDirection(Speed, radian);
	}
};

