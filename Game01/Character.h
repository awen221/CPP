#pragma once

#include "GameObject.h"
#include "ActionSystem.h"

class Character :public GameObject
{
private:
protected:
	int HP;
	double Speed;
	double AttackCenterDistance;
	double AttackRadius;

	virtual int GetDefaultHP();
	virtual double GetDefaultSpeed();
	virtual double GetDefaultAttackCenterDistance();
	virtual double GetDefaultAttackRadius();

	bool bDead;

	ActionSystem action;

public:
	int GetHP();
	void SetHP(int);
	void AddHP(int);
	void SubHP(int);
	bool IsDead();
	
	double GetSpeed();
	void SetSpeed(double);

	void StepToCharacter(GameObject&);

	void MoveToCurrentDirection()
	{
		PointBaseD::MoveToDirection(Speed, radian);
	}

	PointBaseD GetAttackCenter();
	double GetAttackRadius();

	void nearAttackAuto(Character&, int);

	int GetCurAction();

	virtual void Init();

	virtual void Work();
};

