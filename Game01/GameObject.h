#pragma once

#include "point_base.h"
typedef Point_Template::Point_Template_Class<double> PointBaseD;

#include "radian.h"

class GameObject :public PointBaseD, public Radian
{
protected:
	bool bDead = false;
	double Speed;

	virtual double GetDefaultSpeed();
	virtual double GetDefaultSize();

public:
	double Size;

	void Rand(double , double , double , double );
	void SetRandomPos();

	double GetSpeed();
	void SetSpeed(double );

	void StepToCharacter(const GameObject& , double );

	double GetSize();
	void SetSize(double );

	virtual void Init();

	//取得與指定座標之夾角
	double GetRadianFromPoint(PointBaseD );
	virtual bool IsDead();

	void MoveToCurrentDirection()
	{
		PointBaseD::MoveToDirection(Speed, radian);
	}
};

