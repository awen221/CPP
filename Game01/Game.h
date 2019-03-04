#ifndef _GAME_H_
#define _GAME_H_


#include "Character.h"

#include "GetAsyncKeyStateManger.h"
class Player : public Character
{
private:
	KeyStateManager keyStateManager;
	bool InputUp(){ return keyStateManager.IsDown(VK_UP); }
	bool InputDown(){ return keyStateManager.IsDown(VK_DOWN); }
	bool InputLeft(){ return keyStateManager.IsDown(VK_LEFT); }
	bool InputRight(){ return keyStateManager.IsDown(VK_RIGHT); }
	bool InputPlayerAttack(){ return keyStateManager.IsDown(VK_SPACE); }
	bool InputPlayerFire(){ return keyStateManager.IsDown('F'); }
	bool InputPlayerRadianForward(){ return keyStateManager.IsDown('A'); }
	bool InputPlayerRadianReverse(){ return keyStateManager.IsDown('D'); }

public:
	void Init()override final
	{
		Character::Init();

		keyStateManager = KeyStateManager();
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);
		keyStateManager.AddKeyState(VK_SPACE);
		keyStateManager.AddKeyState('F');
		keyStateManager.AddKeyState('A');
		keyStateManager.AddKeyState('D');

	}
	void Work()override final
	{
		Character::Work();
		if (action.CanMove())
		{
			if (InputLeft())
			{
				SetDirectionLeft();
				MoveToCurrentDirection<double>(*this, GetSpeed());
			}
			if (InputRight())
			{
				SetDirectionRight();
				MoveToCurrentDirection<double>(*this, GetSpeed());
			}
			if (InputUp())
			{
				SetDirectionUp();
				MoveToCurrentDirection<double>(*this, GetSpeed());
			}
			if (InputDown())
			{
				SetDirectionDown();
				MoveToCurrentDirection<double>(*this, GetSpeed());
			}
		}
	}
};
Player player = Player();

class Monster :public Character
{
private:
	double GetDefaultSpeed()override final { return 2; }
public:
	void Work(Character& player)
	{
		SetRadian(GetRadianFromPoint(player));
		StepToCharacter(player, GetSpeed());
		nearAttackAuto(player, 2);
	}
};
enum { MonsterMaxCount = 10 };
typedef std::vector<Monster> V_MONSTER;
V_MONSTER vMonster;


class Bullet :public GameObject
{
private:
	double GetDefaultSpeed()override final { return 1; }
protected:
	double GetDefaultSize()override final { return 10; }
public:
	void Init()override final
	{
		bDead = false;
		Speed = GetDefaultSpeed();
		Size = GetDefaultSize();
	}

	void Work()
	{
		MoveToCurrentDirection(*this, Speed);

		if (X < 0)bDead = true;
		if (Y < 0)bDead = true;
		if (X > 800)bDead = true;
		if (Y > 600)bDead = true;
	}

	bool IsDead()override final
	{
		return bDead;
	}

	//偵測擊中
	void CheckHit(Character& targetCharacter, int damage)
	{
		//取得是否與對象角色重疊
		if (GetDistance(targetCharacter) <= (targetCharacter.GetSize()))
		{
			targetCharacter.SubHP(damage);
			bDead = true;
		}
	}
};
enum { BulletsMaxCount = 1000 };
int bulletsCount;
Bullet bullets[BulletsMaxCount];


#include <vector>

#include "ArrayTemplate.h"
//MMO
class Game
{
protected:
	bool Pause = false;

	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
	virtual bool InputMonsterRandom() = 0;
	virtual bool InputMonsterCreate() = 0;
	virtual bool InputPlayerAttack() = 0;
	virtual bool InputPlayerFire() = 0;
	virtual bool InputPlayerRadianForward() = 0;
	virtual bool InputPlayerRadianReverse() = 0;
	virtual bool InputPause() = 0;

	void playerWork()
	{
		if (InputPlayerAttack())
		{
			V_MONSTER::iterator pi = vMonster.begin();
			while (pi != vMonster.end())
			{
				player.nearAttackAuto(*pi, 100);
				pi++;
			}

			//for (int i = 0; i < vMonster.size(); i++)
			//{
			//	player.nearAttackAuto(vMonster[i], 100);
			//}
		}

		if (InputPlayerRadianForward())
		{
			player.SetRadian(player.GetRadian() + 0.1);
		}
		if (InputPlayerRadianReverse())
		{
			player.SetRadian(player.GetRadian() - 0.1);
		}

		//if (InputLeft())
		//{
		//	player.SetDirectionLeft();
		//	player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		//}
		//if (InputRight())
		//{
		//	player.SetDirectionRight();
		//	player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		//}
		//if (InputUp())
		//{
		//	player.SetDirectionUp();
		//	player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		//}
		//if (InputDown())
		//{
		//	player.SetDirectionDown();
		//	player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		//}

		player.Work();
	}

public:
	virtual void Init()
	{
		//monstersCount = 0;

		player.Init();
	}
	virtual void Work()
	{
		if (InputPause())
		{
			Pause = !Pause;
		}
		if (Pause)return;

		playerWork();


		if (InputPlayerFire())
		{
			//生子彈
			Bullet* Bullet = ArrayTemplate::AddObj(bulletsCount, BulletsMaxCount, bullets);
			if (Bullet != NULL)
			{
				Bullet->Init();
				double r = player.GetRadian();
				Bullet->Set(player.GetX(), player.GetY());
				Bullet->SetRadian(r);
			}
		}

		for (int i = 0; i < bulletsCount; i++)
		{
			bullets[i].Work();

			V_MONSTER::iterator pi = vMonster.begin();
			while (pi != vMonster.end())
			{
				bullets[i].CheckHit(*pi, 100);
				pi++;
			}
			//for (int m = 0; m < vMonster.size(); m++)
			//{
			//	bullets[i].CheckHit(vMonster[m], 100);
			//}
		}

		for (int i = 0; i < bulletsCount; i++)
		{
			if (bullets[i].IsDead())
			{
				//移除子彈
				ArrayTemplate::RemoveObj(i, bulletsCount, bullets);
			}
		}


		if (InputMonsterCreate())
		{
			//生怪
			Monster tmp;
			tmp.Init();
			vMonster.push_back(tmp);
			
			//Monster* pMonster = ArrayTemplate::AddObj(monstersCount, MonsterMaxCount, monsters);
			//if (pMonster != NULL)
			//{
			//	pMonster->Init();
			//}
		}

		if (InputMonsterRandom())
		{
			V_MONSTER::iterator pi = vMonster.begin();
			while (pi != vMonster.end())
			{
				pi->SetRandomPos();
				pi++;
			}

			//for (int i = 0; i < vMonster.size(); i++)
			//{
			//	vMonster[i].SetRandomPos();
			//}
		}

		{
			V_MONSTER::iterator pi = vMonster.begin();
			while (pi != vMonster.end())
			{
				pi->Work(player);
				pi++;
			}
		}

		//for (int i = 0; i < vMonster.size(); i++)
		//{
		//	vMonster[i].Work(player);
		//}

		//移除怪物
		V_MONSTER::iterator pi = vMonster.begin();
		while (pi != vMonster.end())
		{
			if (pi->IsDead())
			{
				pi = vMonster.erase(pi);
			}
			else
				pi++;
		}

		//for (int i = 0; i < vMonster.size(); i++)
		//{
		//	if (vMonster[i].IsDead())
		//	{
		//		ArrayTemplate::RemoveObj(i, monstersCount, monsters);
		//	}
		//}

	}
};


#include <tchar.h>
#include "TcString.h"
#include "GetAsyncKeyStateManger.h"
class WinGame :public Game
{
private:
	KeyStateManager keyStateManager = KeyStateManager();
	bool InputUp()final override { return keyStateManager.IsDown(VK_UP); }
	bool InputDown()final override { return keyStateManager.IsDown(VK_DOWN); }
	bool InputLeft()final override { return keyStateManager.IsDown(VK_LEFT); }
	bool InputRight()final override { return keyStateManager.IsDown(VK_RIGHT); }
	bool InputPlayerAttack()final override { return keyStateManager.IsDown(VK_SPACE); }
	bool InputPlayerFire()final override { return keyStateManager.IsDown('F'); }
	bool InputPlayerRadianForward()final override { return keyStateManager.IsDown('A'); }
	bool InputPlayerRadianReverse()final override { return keyStateManager.IsDown('D'); }

	bool InputMonsterRandom()final override { return keyStateManager.IsTriggerDown(VK_F1); }
	bool InputMonsterCreate()final override { return keyStateManager.IsTriggerDown(VK_F2); }
	bool InputPause()final override { return keyStateManager.IsTriggerDown('P'); }

	void DrawGameObject(HDC hdc, GameObject gameObject)
	{
		//SIZE
		Ellipse(hdc,
			(int)(gameObject.GetX() - gameObject.GetSize()),
			(int)(gameObject.GetY() - gameObject.GetSize()),
			(int)(gameObject.GetX() + gameObject.GetSize()),
			(int)(gameObject.GetY() + gameObject.GetSize())
		);
	}

	void DrawCharacter(HDC hdc, Character character)
	{
		double characterX = character.GetX();
		double characterY = character.GetY();
		double characterSize = character.GetSize();


		//攻擊範圍
		PointBaseD pntD = character.GetAttackCenterPoint();
		double pntD_X = pntD.GetX();
		double pntD_Y = pntD.GetY();
		double AttackRadius = character.GetAttackRadius();
		Ellipse
		(
			hdc,
			(int)(pntD_X - AttackRadius),
			(int)(pntD_Y - AttackRadius),
			(int)(pntD_X + AttackRadius),
			(int)(pntD_Y + AttackRadius)
		);

		//SIZE
		Ellipse(hdc,
			(int)(characterX - characterSize),
			(int)(characterY - characterSize),
			(int)(characterX + characterSize),
			(int)(characterY + characterSize)
		);
		//HP
		TcString buf = TcString();
		buf = L"HP:";
		buf += character.GetHP();
		TextOut(hdc,
			(int)characterX,
			(int)characterY,
			buf, buf.len);
		//Direction
		POINT pnt;
		MoveToEx(hdc,
			(int)(characterX),
			(int)(characterY),
			&pnt);
		double characterRadian = character.GetRadian();
		LineTo(hdc,
			(int)(characterX + cos(characterRadian)*characterSize),
			(int)(characterY - sin(characterRadian)*characterSize)
		);
		//Action
		int CurAction = character.GetCurAction();
		if (CurAction == ActionSystem::ACT_STAND)
			TextOut(hdc, characterX, characterY + 20, _T("站立"), 2);
		if (CurAction == ActionSystem::ACT_WALK)
			TextOut(hdc, characterX, characterY + 20, _T("走路"), 2);
		if (CurAction == ActionSystem::ACT_ATTACK)
			TextOut(hdc, characterX, characterY + 20, _T("攻擊"), 2);
	}

public:

	void Init()final override
	{
		keyStateManager = KeyStateManager();
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);
		keyStateManager.AddKeyState(VK_SPACE);
		keyStateManager.AddKeyState('F');
		keyStateManager.AddKeyState('A');
		keyStateManager.AddKeyState('D');

		keyStateManager.AddKeyState(VK_F1);
		keyStateManager.AddKeyState(VK_F2);
		keyStateManager.AddKeyState('P');

		Game::Init();
	}
	void Work()final override
	{
		keyStateManager.Work();
		Game::Work();
	}
	void Draw(HDC hdc)
	{
		DrawCharacter(hdc, player);

		V_MONSTER::iterator pi = vMonster.begin();
		while (pi != vMonster.end())
		{
			DrawCharacter(hdc, *pi);
			pi++;
		}
		//for (int i = 0; i < vMonster.size(); i++)
		//	DrawCharacter(hdc, vMonster[i]);

		for (int i = 0; i < bulletsCount; i++)
			DrawGameObject(hdc, bullets[i]);
	}
};

#endif