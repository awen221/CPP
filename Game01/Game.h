#ifndef _GAME_H_
#define _GAME_H_

#include "point_base.h"
#include "radian.h"
#include "random.h"
#include "ArrayTemplate.h"

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

private:
	int HP;
	virtual int GetDefaultHP() { return defaultHP; }
public:
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

private:
	double AttackDistance;
	virtual double GetDefaultAttackDistance() { return defaultAttackDistance; }
	double AttackRadius;
	virtual double GetDefaultAttackRadius() { return defaultAttackRadius; }
public:
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

public:
	void Init()
	{
		GameObject::Init();

		HP = GetDefaultHP();
		AttackDistance = GetDefaultAttackDistance();
		AttackRadius = GetDefaultAttackRadius();
	}
};

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

	Character player;

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

		if (InputLeft())
		{
			player.SetDirectionLeft();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		}
		if (InputRight())
		{
			player.SetDirectionRight();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		}
		if (InputUp())
		{
			player.SetDirectionUp();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		}
		if (InputDown())
		{
			player.SetDirectionDown();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		}
	}

public:
	enum {
		WindowsWidth = 800,
		WindowsHeight = 600,
	};
	virtual void Init()
	{
		player = Character();
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
	bool InputMonsterRandom()final override { return keyStateManager.IsTriggerDown(VK_F1); }
	bool InputMonsterCreate()final override { return keyStateManager.IsTriggerDown(VK_F2); }
	bool InputPlayerAttack()final override { return keyStateManager.IsDown(VK_SPACE); }
	bool InputPlayerFire()final override { return keyStateManager.IsDown('F'); }
	bool InputPlayerRadianForward()final override { return keyStateManager.IsDown('A'); }
	bool InputPlayerRadianReverse()final override { return keyStateManager.IsDown('D'); }
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
		//�����d��
		PointBaseD pntD = character.GetAttackCenterPoint();
		Ellipse(hdc,
			(int)(pntD.GetX() - character.GetAttackRadius()),
			(int)(pntD.GetY() - character.GetAttackRadius()),
			(int)(pntD.GetX() + character.GetAttackRadius()),
			(int)(pntD.GetY() + character.GetAttackRadius())
		);


		//SIZE
		Ellipse(hdc,
			(int)(character.GetX() - character.GetSize()),
			(int)(character.GetY() - character.GetSize()),
			(int)(character.GetX() + character.GetSize()),
			(int)(character.GetY() + character.GetSize())
		);

		//HP
		TcString buf = TcString();
		buf = L"HP:";
		buf += character.GetHP();
		TextOut(hdc,
			(int)(character.GetX()),
			(int)(character.GetY()),
			buf, buf.len);

		//Direction
		POINT pnt;
		MoveToEx(hdc,
			(int)(character.GetX()),
			(int)(character.GetY()),
			&pnt);

		LineTo(hdc,
			(int)(character.GetX() + cos(character.GetRadian())*character.GetSize()),
			(int)(character.GetY() - sin(character.GetRadian())*character.GetSize())
		);

		//Ellipse(hdc, character.GetX() - character.GetSize(), character.GetY() - character.GetSize(), character.GetX() + character.GetSize(), character.GetY() + character.GetSize());
	}

public:

	void Init()final override
	{
		keyStateManager = KeyStateManager();
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);
		keyStateManager.AddKeyState(VK_F1);
		keyStateManager.AddKeyState(VK_F2);
		keyStateManager.AddKeyState(VK_SPACE);
		keyStateManager.AddKeyState('F');
		keyStateManager.AddKeyState('A');
		keyStateManager.AddKeyState('D');
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