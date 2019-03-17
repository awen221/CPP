#ifndef GAME_H
#define GAME_H

#include <vector>
#include <windows.h>

#include "GetAsyncKeyStateManger.h"
#include "Character.h"


#include "ActiveObject.h"
#include "GameObject.h"

enum RandomPos { xMin = 0, xMax = 800, yMin = 0, yMax = 600, };
enum Speed
{
	Default = 4,
};
enum Size
{
	SizeDefault = 20,
};

class Player : public Character
{
private:
	double GetDefaultSpeed()override final { return 4; }
	double GetDefaultRadius()override final { return 20; }
	
	
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

		Rand(xMin, xMax, yMin, yMax);

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
		action.Work();
		if (action.CanMove())
		{
			if (InputLeft())
			{
				SetDirectionLeft();
				MoveToCurrentDirection();
			}
			if (InputRight())
			{
				SetDirectionRight();
				MoveToCurrentDirection();
			}
			if (InputUp())
			{
				SetDirectionUp();
				MoveToCurrentDirection();
			}
			if (InputDown())
			{
				SetDirectionDown();
				MoveToCurrentDirection();
			}
		}
	}
};
Player player = Player();

class Monster :public Character
{
private:
	double GetDefaultSpeed()override final { return 2; }
	double GetDefaultRadius()override final { return 20; }
public:
	Monster() {}
	~Monster() {}

	void Init()
	{
		Character::Init();
	}
	void Work(Character& player)
	{
		Character::Work();

		SetRadian(GetRadianFrom(player));
		StepToCharacter(player);
		nearAttackAuto(player, 2);
	}
};
enum { MonsterMaxCount = 10 };
typedef std::vector<Monster> V_MONSTER;
V_MONSTER vMonster;


class Bullet :public ActiveObject
{
private:
protected:
	double GetDefaultRadius()override final { return 5; }
	double GetDefaultSpeed()override final { return 1; }
public:
	Bullet(){}
	~Bullet() {}
	void Init()override final
	{
		ActiveObject::Init();
	}

	void Work()
	{
		MoveToCurrentDirection();
		if (X < 0)
			Destroyed = true;
		if (Y < 0)
			Destroyed = true;
		if (X > 800)
			Destroyed = true;
		if (Y > 600)
			Destroyed = true;
	}

	bool IsDead()
	{
		return Destroyed;
	}

	//偵測擊中
	void CheckHit(Character& targetCharacter, int damage)
	{
		//取得是否與對象角色重疊
		if (GetDistanceFrom(targetCharacter) <= (targetCharacter.GetRadius()))
		{
			targetCharacter.SubHP(damage);
			Destroyed = true;
		}
	}
};
typedef std::vector<Bullet> V_BULLET;
V_BULLET v_BULLET;




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
		}

		if (InputPlayerRadianForward())
		{
			player.SetRadian(player.GetRadian() + 0.1);
		}
		if (InputPlayerRadianReverse())
		{
			player.SetRadian(player.GetRadian() - 0.1);
		}

		player.Work();
	}

public:
	virtual void Init()
	{
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


		//生子彈
		if (InputPlayerFire())
		{
			Bullet bullet = Bullet();
			bullet.Init();
			double r = player.GetRadian();
			bullet.Set(player);
			bullet.SetRadian(r);

			v_BULLET.push_back(bullet);
		}
		//檢查子彈碰撞
		V_BULLET::iterator piB = v_BULLET.begin();
		while (piB != v_BULLET.end())
		{
			piB->Work();
			V_MONSTER::iterator pi = vMonster.begin();
			while (pi != vMonster.end())
			{
				piB->CheckHit(*pi, 100);
				pi++;
			}
			piB++;
		}
		//檢查子彈消滅
		V_BULLET::iterator piBm = v_BULLET.begin();
		while (piBm != v_BULLET.end())
		{
			if (piBm->IsDead())
			{
				//移除子彈
				piBm = v_BULLET.erase(piBm);
			}
			else
				piBm++;
		}

		//生怪
		if (InputMonsterCreate())
		{
			Monster tmp;
			tmp.Init();

			vMonster.push_back(tmp);
		}

		//設定怪物隨機座標
		if (InputMonsterRandom())
		{
			V_MONSTER::iterator pi = vMonster.begin();
			while (pi != vMonster.end())
			{
				pi->Rand(xMin, xMax, yMin, yMax);
				pi++;
			}
		}

		//怪物工作
		{
			V_MONSTER::iterator pi = vMonster.begin();
			while (pi != vMonster.end())
			{
				pi->Work(player);
				pi++;
			}
		}

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

	}
};



#include <windows.h>
#include <tchar.h>
#include "GetAsyncKeyStateManger.h"
#include "TString.h"
using namespace TString;

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
			(int)(gameObject.GetX() - gameObject.GetRadius()),
			(int)(gameObject.GetY() - gameObject.GetRadius()),
			(int)(gameObject.GetX() + gameObject.GetRadius()),
			(int)(gameObject.GetY() + gameObject.GetRadius())
		);
	}

	void DrawCharacter(HDC hdc, Character character)
	{
		double characterX = character.GetX();
		double characterY = character.GetY();
		double characterSize = character.GetRadius();


		//攻擊範圍
		PointBaseD pntD = character.GetAttackCenter();
		double pntD_X = pntD.GetX();
		double pntD_Y = pntD.GetY();
		double Radian = character.GetRadian();
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
		tstring hp = tstring(L"HP:");
		hp += character.GetHP();
		TextOut(hdc,
			(int)characterX,
			(int)characterY,
			hp, hp.length());

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
			TextOut(hdc, (int)characterX, (int)characterY + 20, _T("站立"), 2);
		if (CurAction == ActionSystem::ACT_WALK)
			TextOut(hdc, (int)characterX, (int)characterY + 20, _T("走路"), 2);
		if (CurAction == ActionSystem::ACT_ATTACK)
			TextOut(hdc, (int)characterX, (int)characterY + 20, _T("攻擊"), 2);
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

		V_BULLET::iterator piB = v_BULLET.begin();
		while (piB != v_BULLET.end())
		{
			DrawGameObject(hdc, *piB);
			piB++;
		}

	}
};

#endif