#include "Game.h"

#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"
#include "TcString.h"
#include "time_ex.h"


class WinGame:public Game
{
private:
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
		//§ðÀ»½d³ò
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
		keyStateManager.AddKeyState('A');
		keyStateManager.AddKeyState('D');
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