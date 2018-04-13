#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"
#include "TcString.h"

#include "time_ex.h"
#include "point_base.h"
#include "random.h"
#include "radian.h"



class Character :public PointBaseD,public Radian
{
private:
	double Size;
	double Speed;
	virtual double GetDefaultSize() { return 20; }
	virtual double GetDefaultSpeed() { return 4; }

	int HP;
	virtual int GetDefaultHP() { return 1000; }

	double AttackRange;
	virtual double GetDefaultAttackRange() { return 5; }

public:
	double GetSize() { return Size; }
	void SetSize(double value) { Size = value; }
	double GetSpeed() { return Speed; }
	void SetSpeed(double value) { Speed = value; }

	//將點設置到參數座標範圍內之隨機位置
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
	//亂數座標
	void SetRandomPos() { Rand(100, 700, 100, 500); }

	//往目標角色移動
	void StepToCharacter(Character targetCharacter, double speed)
	{
		Character target = targetCharacter;

		//簡易碰撞
		double dis = GetDistance(targetCharacter);
		dis -= Size + targetCharacter.GetSize();
		target = *this;
		target.Step(targetCharacter, dis);

		Step(target, speed);
	}

	int GetHP() { return HP; }
	void SetHP(int value) { HP = value; }
	void AddHP(int value) { HP += value; }
	void SubHP(int value) { HP -= value; }

	//近身攻擊
	void nearAttackAuto(Character& targetCharacter, int damage)
	{
		if (GetDistance(targetCharacter) <= (Size * 2) + AttackRange)
		{
			targetCharacter.SubHP(damage);
		}
	}
	bool IsDead() { return HP <= 0; }

	void Init()
	{
		Size = GetDefaultSize();
		Speed = GetDefaultSpeed();
		HP = GetDefaultHP();

		SetRandomPos();

		AttackRange = GetDefaultAttackRange();
	}
};

class Monster :public Character
{
private:
	double GetDefaultSpeed()override final { return 2; }
};

class Game
{
protected:
	enum { MAX_MONSTER = 10 };
	Character player;
	int monstersCount;
	Monster monsters[MAX_MONSTER];

	bool Pause = false;

	virtual bool InputTop() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
	virtual bool InputMonsterRandom() = 0;
	virtual bool InputMonsterCreate() = 0;
	virtual bool InputPlayerAttack() = 0;
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
			//player.Shift(-player.GetSpeed(), 0);
			return;
		}
		if (InputRight())
		{
			player.SetDirectionRight();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
			//player.Shift(player.GetSpeed(), 0);
			return;
		}
		if (InputTop())
		{
			player.SetDirectionUp();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
			//player.Shift(0, -player.GetSpeed());
			return;
		}
		if (InputDown())
		{
			player.SetDirectionDown();
			player.MoveToCurrentDirection<double>(player, player.GetSpeed());
			//player.Shift(0, player.GetSpeed());
			return;
		}



	}
	void monsterWork(Monster& monster, Character& player)
	{
		monster.SetRadian(monster.GetRadianFromPoint<double>(monster,player));
		monster.StepToCharacter(player, monster.GetSpeed());
		monster.nearAttackAuto(player, 2);
	}

public:
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

		playerWork();
		for (int i = 0; i < monstersCount; i++)
		{
			monsterWork(monsters[i], player);
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
	bool InputPause()final override { return keyStateManager.IsTriggerDown('P'); }

	void DrawCharacter(HDC hdc, Character character)
	{
		//SIZE
		Ellipse(hdc, character.GetX() - character.GetSize(), character.GetY() - character.GetSize(), character.GetX() + character.GetSize(), character.GetY() + character.GetSize());

		//HP
		TcString buf = TcString();
		buf = L"HP:";
		buf += character.GetHP();
		TextOut(hdc, character.GetX(), character.GetY(), buf, buf.len);

		//Direction
		POINT pnt;
		MoveToEx(hdc, character.GetX(), character.GetY(), &pnt);
		LineTo(hdc
			, character.GetX() + cos(character.GetRadian())*character.GetSize()
			, character.GetY() - sin(character.GetRadian())*character.GetSize()
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
	}
};

class mainWindow :private BaseWindow
{
private:
	///overwrite abstract
	//標題文字
	TCHAR * GetTitle()override 
	{
		return (TCHAR *)TEXT("mainWindows"); 
	}
	//視窗類別
	TCHAR* GetWindowsClass()override 
	{
		return (TCHAR *)TEXT("mainWindows");
	}
	//視窗寬
	int GetWindowsWidth()override 
	{
		return 800; 
	}
	//視窗高
	int GetWindowsHeight()override 
	{
		return 600; 
	}

	//初始
	void Init()override 
	{
		winGame.Init();
	}
	//工作
	void Proc()override 
	{
		winGame.Work();
	}
	//繪圖
	void Draw(HDC hdc)override 
	{
		winGame.Draw(hdc);
	}

	WinGame winGame = WinGame();

public:
	mainWindow() :BaseWindow() {}
};
mainWindow win = mainWindow();