#pragma once

#include "windows.h"
#include "GetAsyncKeyStateManger.h"

class ActionSystem
{
private:
	int CurAction;

	int AttackTime = 2000;
	int AttackEndTime;

	KeyStateManager keyStateManager = KeyStateManager();
	bool InputUp() { return keyStateManager.IsDown(VK_UP); }
	bool InputDown() { return keyStateManager.IsDown(VK_DOWN); }
	bool InputLeft() { return keyStateManager.IsDown(VK_LEFT); }
	bool InputRight() { return keyStateManager.IsDown(VK_RIGHT); }

	bool InputPlayerAttack() { return keyStateManager.IsDown(VK_SPACE); }

public:
	enum { ACT_STAND, ACT_WALK, ACT_ATTACK };
	int GetCurAction()
	{
		return CurAction;
	}
	bool CanMove()
	{
		return CurAction == ACT_WALK;
	}
	void Init()
	{
		CurAction = ACT_STAND;
		keyStateManager = KeyStateManager();
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		keyStateManager.AddKeyState(VK_SPACE);


	}
	void Work()
	{
		if (CurAction == ACT_ATTACK)
		{
			int nowTime = GetTickCount();
			if (nowTime > AttackEndTime)
			{
				CurAction = ACT_STAND;
			}

			return;
		}

		if (CurAction == ACT_STAND)
		{
			if (InputUp())
				CurAction = ACT_WALK;
			if (InputDown())
				CurAction = ACT_WALK;
			if (InputLeft())
				CurAction = ACT_WALK;
			if (InputRight())
				CurAction = ACT_WALK;

			if (InputPlayerAttack())
			{
				CurAction = ACT_ATTACK;
				AttackEndTime = GetTickCount() + AttackTime;
			}
		}

		if (CurAction == ACT_WALK)
		{
			bool bMove = false;

			if (InputUp())
				bMove = true;
			if (InputDown())
				bMove = true;
			if (InputLeft())
				bMove = true;
			if (InputRight())
				bMove = true;

			if (!bMove)
			{
				CurAction = ACT_STAND;
			}
		}
	}
};
