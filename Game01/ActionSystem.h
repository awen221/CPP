#ifndef _ACTION_SYSTEM_H_
#define _ACTION_SYSTEM_H_

#pragma once


class ActionSystem
{
private:
	int CurAction;
	int AttackEndTime;

	bool InputUp();
	bool InputDown();
	bool InputLeft();
	bool InputRight();

	bool InputPlayerAttack();

public:
	enum { ACT_STAND, ACT_WALK, ACT_ATTACK };
	int GetCurAction();
	bool CanMove();

	void Init();
	void Work();
};

#endif