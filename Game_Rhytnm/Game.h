#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "point_base.h"
typedef PointBase<double> obj;
#include "random.h"

//Rhythm
class Game
{
private:


protected:
	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
public:
	Game() {}
	~Game() {}

	virtual void Init()
	{

	}

	virtual void Work()
	{

	}
};

#include "windows.h"
#include "GetAsyncKeyStateManger.h"
#include "time_ex.h"
#include "TcString.h"

class WinGame :public Game
{
private:
	const int StartX = 40;
	const int StartY = 60;
	const int spaceWidth = 720;
	const int spaceHight = 540;

	KeyStateManager keyStateManager;
	void KeyStateManager_Init()
	{
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		keyStateManager = KeyStateManager();
	}

	//class TimerWin : public Timer
	//{
	//public:
	//	TimerWin(unsigned int len) :Timer(len) {};

	//	void Draw(HDC hdc)
	//	{
	//		TcString tString = TcString();
	//		tString = L"Timer : ";
	//		static bool OnTimerPluse = false;
	//		if (GetOnTimer())
	//		{
	//			OnTimerPluse = !OnTimerPluse;
	//		}

	//		if (OnTimerPluse)
	//		{
	//			tString += L"O";
	//		}
	//		else
	//		{
	//			tString += L"X";
	//		}

	//		TextOut(hdc, 0, 20, tString, tString.len);
	//	}
	//};
	//TimerWin gtr = TimerWin(1000 / 10);
protected:

	bool InputLeft()final override { return keyStateManager.IsDown(VK_LEFT); }
	bool InputUp()final override { return keyStateManager.IsDown(VK_UP); }
	bool InputRight()final override { return keyStateManager.IsDown(VK_RIGHT); }
	bool InputDown()final override { return keyStateManager.IsDown(VK_DOWN); }

public:
	void Init()final override
	{
		KeyStateManager_Init();

		Game::Init();
	}
	void Work()final override
	{
		//if (!gtr.Work())return;

		keyStateManager.Work();

		Game::Work();
	}
	void Draw(HDC hdc)
	{
		Rectangle(hdc, StartX, StartY, StartX + spaceWidth, StartY + spaceHight);

		TcString tString = TcString();
		tString = L"BodyCurrentCount : ";
		TextOut(hdc, 300, 0, tString, tString.len);



		//Ellipse(hdc, foodX, foodY, foodX + BodySize, foodY + BodySize);
	}
};

#endif
#pragma once
