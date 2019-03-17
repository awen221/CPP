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

	virtual void Init();
	double GetSpeed();
	void SetSpeed(double);

	void MoveToCurrentDirection();
};

