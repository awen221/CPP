#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"
#include "TcString.h"
#include "time_ex.h"
#include "random.h"
#include "radian.h"
#include "point_base.h"


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
public :
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
	double GetDefaultSpeed()override final { return 10; }
protected:
	double GetDefaultSize()override final { return 5; }
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

	enum { MAX_MONSTER = 10 };
	int monstersCount;
	Monster monsters[MAX_MONSTER];

	enum { MAX_Bullet = 20 };
	int bulletsCount;
	Bullet bullets[MAX_Bullet];

	bool Pause = false;

	virtual bool InputTop() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
	virtual bool InputMonsterRandom() = 0;
	virtual bool InputMonsterCreate() = 0;
	virtual bool InputPlayerAttack() = 0;
	virtual bool InputPlayerFire() = 0;
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

		if (InputLeft())
		{
			player.SetDirectionLeft();
			player.MoveToCurrentDirection<double>(player,player.GetSpeed());
		}
		if (InputRight())
		{
			player.SetDirectionRight();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
		}
		if (InputTop())
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
			if (bulletsCount < MAX_Bullet)
			{
				bullets[bulletsCount].Init();
				double r = player.GetRadian();
				bullets[bulletsCount].Set(player.GetX(), player.GetY());
				bullets[bulletsCount].SetRadian(r);
				bulletsCount++;
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
				bulletsCount--;
				for (int m = i; m < bulletsCount; m++)
				{
					bullets[m] = bullets[m + 1];
				}
			}
		}


		if (InputMonsterCreate())
		{
			if (monstersCount < MAX_MONSTER)
			{
				monsters[monstersCount].Init();
				monstersCount++;
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
				monstersCount--;
				for (int m = i; m < monstersCount; m++)
				{
					monsters[m] = monsters[m + 1];
				}
			}
		}
		
	}
};

class WinGame:public Game
{
private:
	bool InputTop()final override { return keyStateManager.IsDown(VK_UP); }
	bool InputDown()final override { return keyStateManager.IsDown(VK_DOWN); }
	bool InputLeft()final override { return keyStateManager.IsDown(VK_LEFT); }
	bool InputRight()final override { return keyStateManager.IsDown(VK_RIGHT); }
	bool InputMonsterRandom()final override { return keyStateManager.IsTriggerDown(VK_F1); }
	bool InputMonsterCreate()final override { return keyStateManager.IsTriggerDown(VK_F2); }
	bool InputPlayerAttack()final override { return keyStateManager.IsDown(VK_SPACE); }
	bool InputPlayerFire()final override { return keyStateManager.IsTriggerDown('F'); }
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
		//攻擊範圍
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


	KeyStateManager keyStateManager = KeyStateManager();

	class TimePassWin : public TimePass
	{
	public:
		void Draw(HDC hdc)
		{
			TcString tString = TcString();
			tString = L"TimePass : ";
			unsigned int tp = GetTimePass();
			tString += tp;
			TextOut(hdc, 0, 0, tString, tString.len);
		}
	};
	class TimerWin : public Timer
	{
	public:
		TimerWin(unsigned int len) :Timer(len) {};

		void Draw(HDC hdc)
		{
			TcString tString = TcString();
			tString = L"Timer : ";
			static bool OnTimerPluse = false;
			if (GetOnTimer())
			{
				OnTimerPluse = !OnTimerPluse;
			}

			if (OnTimerPluse)
			{
				tString += L"O";
			}
			else
			{
				tString += L"X";
			}

			TextOut(hdc, 0, 20, tString, tString.len);
		}
	};
	class FpsWin : public FPS
	{
	public:
		void Draw(HDC hdc)
		{
			TcString tString = TcString();
			tString = L"FPS : ";
			tString += GetFPS();

			TextOut(hdc, 0, 40, tString, tString.len);
		}
	};
	TimePassWin tw = TimePassWin();
	TimerWin tr = TimerWin(1000 / 30);
	FpsWin fw = FpsWin();

	
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
		keyStateManager.AddKeyState('P');

		Game::Init();
	}
	void Work()
	{
		if (!tr.Work())return;
		tw.Work();
		fw.Work();

		keyStateManager.Work();

		Game::Work();
	}
	void Draw(HDC hdc)
	{
		tw.Draw(hdc);
		tr.Draw(hdc);
		fw.Draw(hdc);

		DrawCharacter(hdc, player);
		for (int i = 0; i < monstersCount; i++)DrawCharacter(hdc, monsters[i]);
		for (int i = 0; i < bulletsCount; i++)
			DrawGameObject(hdc, bullets[i]);
	}
};

class mainWindow :private BaseWindow
{
private:
	///overwrite abstract
	TCHAR * GetTitle()override 
	{
		return (TCHAR *)TEXT("mainWindows"); 
	}
	TCHAR* GetWindowsClass()override 
	{
		return (TCHAR *)TEXT("mainWindows");
	}
	int GetWindowsWidth()override 
	{
		return Game::WindowsWidth; 
	}
	int GetWindowsHeight()override 
	{
		return Game::WindowsHeight; 
	}

	void Init()override 
	{
		winGame.Init();
	}
	void Proc()override 
	{
		winGame.Work();
	}
	void Draw(HDC hdc)override 
	{
		winGame.Draw(hdc);
	}

	WinGame winGame = WinGame();

public:
	mainWindow() :BaseWindow() {}
};
mainWindow win = mainWindow();