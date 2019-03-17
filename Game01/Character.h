#pragma once

#include "ActiveObject.h"
#include "ActionSystem.h"

class Character :public ActiveObject
{
private:
	int HP;
protected:

	double AttackCenterDistance;
	double AttackRadius;

	virtual int GetDefaultHP();
	virtual double GetDefaultAttackCenterDistance();
	virtual double GetDefaultAttackRadius();

	bool bDead;

	ActionSystem action;

public:
	Character();
	~Character();


	int GetHP();
	void SetHP(int);
	void AddHP(int);
	void SubHP(int);
	bool IsDead();
	


	void StepToCharacter(Character&);



	PointBaseD GetAttackCenter();
	double GetAttackRadius();

	void nearAttackAuto(Character&, int);

	int GetCurAction();

	virtual void Init();

	virtual void Work();

	void Rand(double, double, double, double);
};

