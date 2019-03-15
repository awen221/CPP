#pragma once
#include "GameObject.h"

class ActiveObject :public GameObject
{
protected:
	double Speed;
	virtual double GetDefaultSpeed();
public:
	ActiveObject();
	~ActiveObject();
	double GetSpeed();
	void SetSpeed(double);

	void MoveToCurrentDirection();
};

