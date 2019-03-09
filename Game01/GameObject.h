#pragma once

#include "point_base.h"
using PointBaseD = Point_Template::Point_Template_Class<double>;
#include "radian.h"
using Radian_Class = Radian::Radian_Class;

class GameObject :public PointBaseD, public Radian_Class
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

	

	//���o�P���w�y�Ф�����
	double GetRadianFromPoint(PointBaseD );
	virtual bool IsDead();

	void MoveToCurrentDirection()
	{
		PointBaseD::MoveToDirection(Speed, radian);
	}
};

