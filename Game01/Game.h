#ifndef _GAME_H_
#define _GAME_H_

#include "point_base.h"
typedef PointBase<double> PointBaseD;
#include "radian.h"
#include "random.h"
#include "ArrayTemplate.h"
#include <tchar.h>
#include "Action.h"

class GameObject :public PointBaseD, public Radian
{
private:
	enum RandomPos
	{
		xMin = 0,
		xMax = 800,
		yMin = 0,
		yMax = 600,
	};
	enum Speed
	{
		Default = 4,
	};
	enum Size
	{
		SizeDefault = 20,
	};
public:
	void Rand(double xMin, double xMax, double yMin, double yMax)
	{
		static RANDOM random = RANDOM();
		int randX = random.GetRand();
		int randY = random.GetRand();

		double X_rand = xMin + randX % (int)(xMax - xMin);
		double Y_rand = yMin + randY % (int)(yMax - yMin);

		X = X_rand;
		Y = Y_rand;
	}
	void SetRandomPos()
	{
		Rand(RandomPos::xMin, RandomPos::xMax, RandomPos::yMin, RandomPos::yMax);
	}

protected:
	double Speed;
	virtual double GetDefaultSpeed() { return Speed::Default; }
public:
	double GetSpeed() { return Speed; }
	void SetSpeed(double value) { Speed = value; }

	void StepToCharacter(const GameObject& targetCharacter, double speed)
	{
		GameObject target = targetCharacter;
		//�ؼЬ����豵Ĳ�I
		target.Step(*this, Size + targetCharacter.Size);
		Step(target, speed);
	}

protected:
	double Size;
	virtual double GetDefaultSize() { return Size::SizeDefault; }
public:
	double GetSize() { return Size; }
	void SetSize(double value) { Size = value; }

public:
	virtual void Init()
	{
		SetRandomPos();
		Speed = GetDefaultSpeed();
		Size = GetDefaultSize();
	}

	//���o�P���w�y�Ф�����
	double GetRadianFromPoint(PointBaseD target)
	{
		double radian;

		//�åd��y�Шt(�Ĥ@�H��)����
		radian = atan2(target.GetY() - Y, target.GetX() - X);
		//�নWindows�y�Шt(�ĤT�H��)�n�[�t��
		radian = -radian;

		return radian;
	}

protected:
	bool bDead = false;
public:
	virtual bool IsDead() { return bDead; }
};

class Character :public GameObject
{
private:
	enum
	{
		defaultHP = 1000,
		defaultAttackDistance = 20,
		defaultAttackRadius = 25,
	};
	int HP;
	virtual int GetDefaultHP() { return defaultHP; }
	double AttackDistance;
	double GetDefaultAttackDistance() { return defaultAttackDistance; }
	double AttackRadius;
	double GetDefaultAttackRadius() { return defaultAttackRadius; }
protected:
	ActionSystem action;

public:
	Character() {};
	int GetHP()
	{
		return HP;
	}
	void SetHP(int value)
	{
		HP = value;
	}
	void AddHP(int value)
	{
		SetHP(HP + value);
	}
	void SubHP(int value)
	{
		SetHP(HP - value);
	}
	bool IsDead()override final
	{
		return HP <= 0;
	}
	PointBaseD GetAttackCenterPoint()
	{
		Character pnt = *this;

		pnt.MoveToCurrentDirection(pnt, AttackDistance);

		return pnt;
	}
	double GetAttackRadius() { return AttackRadius; }
	//�񨭧���
	void nearAttackAuto(Character& targetCharacter, int damage)
	{
		PointBaseD pnt = GetAttackCenterPoint();
		//���o�����d��O�_�P��H���⭫�|
		if (pnt.GetDistance(targetCharacter) <= (targetCharacter.GetSize() + AttackRadius))
		{
			targetCharacter.SubHP(damage);
		}
	}

	int GetCurAction()
	{
		return action.GetCurAction();
	}

	virtual void Init()
	{
		GameObject::Init();

		HP = GetDefaultHP();
		AttackDistance = GetDefaultAttackDistance();
		AttackRadius = GetDefaultAttackRadius();

		action = ActionSystem();
		action.Init();
	}

	virtual void Work()
	{
		action.Work();
	}
};

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

class Monster :public Character
{
private:
	double GetDefaultSpeed()override final { return 2; }
public:
	Monster() {}
	void Work(Character& player)
	{
		SetRadian(GetRadianFromPoint(player));
		StepToCharacter(player, GetSpeed());
		nearAttackAuto(player, 2);
	}
};

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

	//��������
	void CheckHit(Character& targetCharacter, int damage)
	{
		//���o�O�_�P��H���⭫�|
		if (GetDistance(targetCharacter) <= (targetCharacter.GetSize()))
		{
			targetCharacter.SubHP(damage);
			bDead = true;
		}
	}
};
//MMO
class Game
{
protected:

	Player player = Player();

	enum { MonsterMaxCount = 10 };
	int monstersCount;
	Monster monsters[MonsterMaxCount];

	enum { BulletsMaxCount = 1000 };
	int bulletsCount;
	Bullet bullets[BulletsMaxCount];

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
			for (int i = 0; i < monstersCount; i++)
			{
				player.nearAttackAuto(monsters[i], 100);
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
		monstersCount = 0;

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
			//�ͤl�u
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
			for (int m = 0; m < monstersCount; m++)
			{
				bullets[i].CheckHit(monsters[m], 100);
			}
		}

		for (int i = 0; i < bulletsCount; i++)
		{
			if (bullets[i].IsDead())
			{
				//�����l�u
				ArrayTemplate::RemoveObj(i, bulletsCount, bullets);
			}
		}


		if (InputMonsterCreate())
		{
			//�ͩ�
			Monster* pMonster = ArrayTemplate::AddObj(monstersCount, MonsterMaxCount, monsters);
			if (pMonster != NULL)
			{
				pMonster->Init();
			}
		}

		if (InputMonsterRandom())
		{
			for (int i = 0; i < monstersCount; i++)
			{
				monsters[i].SetRandomPos();
			}
		}

		for (int i = 0; i < monstersCount; i++)
		{
			monsters[i].Work(player);
		}

		for (int i = 0; i < monstersCount; i++)
		{
			if (monsters[i].IsDead())
			{
				//�����Ǫ�
				ArrayTemplate::RemoveObj(i, monstersCount, monsters);
			}
		}

	}
};


#include "windows.h"
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


		//�����d��
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
			TextOut(hdc, characterX, characterY + 20, _T("����"), 2);
		if (CurAction == ActionSystem::ACT_WALK)
			TextOut(hdc, characterX, characterY + 20, _T("����"), 2);
		if (CurAction == ActionSystem::ACT_ATTACK)
			TextOut(hdc, characterX, characterY + 20, _T("����"), 2);
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
		for (int i = 0; i < monstersCount; i++)DrawCharacter(hdc, monsters[i]);
		for (int i = 0; i < bulletsCount; i++)
			DrawGameObject(hdc, bullets[i]);
	}
};

#endif