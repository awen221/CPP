#pragma once

#include "GameObject.h"
#include "ActionSystem.h"

class Character :public GameObject
{
private:
	int HP;
	double AttackDistance;
	//double AttackRadius;

	virtual int GetDefaultHP();
	double GetDefaultAttackDistance();
	//double GetDefaultAttackRadius();

	
protected:
	ActionSystem action;

public:
	int GetHP();
	void SetHP(int);
	void AddHP(int);
	void SubHP(int);
	bool IsDead()override final;
	
	double GetAttackDistance();
	PointBaseD GetAttackCenterPoint();
	//double GetAttackRadius();
	//ªñ¨­§ðÀ»
	void nearAttackAuto(Character&, int);

	int GetCurAction();

	virtual void Init();

	virtual void Work();
};

