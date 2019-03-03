#include "ActionSystem.h"

#include "windows.h"

#include "GetAsyncKeyStateManger.h"

int AttackTime = 2000;
KeyStateManager keyStateManager;

bool ActionSystem::InputUp() { return keyStateManager.IsDown(VK_UP); }
bool ActionSystem::InputDown() { return keyStateManager.IsDown(VK_DOWN); }
bool ActionSystem::InputLeft() { return keyStateManager.IsDown(VK_LEFT); }
bool ActionSystem::InputRight() { return keyStateManager.IsDown(VK_RIGHT); }

bool ActionSystem::InputPlayerAttack() { return keyStateManager.IsDown(VK_SPACE); }

int ActionSystem::GetCurAction()
{
	return CurAction;
}
bool ActionSystem::CanMove()
{
	return CurAction == ACT_WALK;
}
void ActionSystem::Init()
{
	CurAction = ACT_STAND;
	keyStateManager = KeyStateManager();
	keyStateManager.AddKeyState(VK_UP);
	keyStateManager.AddKeyState(VK_DOWN);
	keyStateManager.AddKeyState(VK_LEFT);
	keyStateManager.AddKeyState(VK_RIGHT);
	keyStateManager.AddKeyState(VK_SPACE);
}
void ActionSystem::Work()
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
