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
		//目標為雙方接觸點
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

	//取得與指定座標之夾角
	double GetRadianFromPoint(PointBaseD target)
	{
		double radian;

		//笛卡兒座標系(第一象限)公式
		radian = atan2(target.GetY() - Y, target.GetX() - X);
		//轉成Windows座標系(第三象限)要加負號
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
	//近身攻擊
	void nearAttackAuto(Character& targetCharacter, int damage)
	{
		PointBaseD pnt = GetAttackCenterPoint();
		//取得攻擊範圍是否與對象角色重疊
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
			for (int m = 0; m < monstersCount; m++)
			{
				bullets[i].CheckHit(monsters[m], 100);
			}
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
				//移除怪物
				ArrayTemplate::RemoveObj(i, monstersCount, monsters);
			}
		}

	}
};

#endif