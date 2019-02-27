#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "point_base.h"
typedef PointBase<double> obj;
#include "random.h"

//Snake
class Game
{
private:
	enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
	int HeadDirection;

	const int defultHeadX = 3;
	const int defultHeadY = 3;
	const int defultDirection = DIR_RIGHT;
	const int BodyCountMin = 1;
	static const int BodyCountMax = 40;

	const double Speed = 1;

	obj* Head;
	void FoodRand()
	{
		static RANDOM random = RANDOM();
		int randX = random.GetRand();
		int randY = random.GetRand();

		int X_rand = randX % (SpaceWidth - 1);
		int Y_rand = randY % (SpaceHeight - 1);

		Food.SetX(X_rand);
		Food.SetY(Y_rand);
	}
protected:
	obj SnakeBodyArray[BodyCountMax];
	int BodyCurrentCount;
	const int BodySize = 20;

	obj Food;

	const int SpaceWidth = 36;
	const int SpaceHeight = 27;

	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
public:
	Game() {}
	~Game() {}

	virtual void Init()
	{
		HeadDirection = defultDirection;
		BodyCurrentCount = BodyCountMin;

		for (int i = 0; i < BodyCountMax; i++)
		{
			SnakeBodyArray[i].SetX(defultHeadX);
			SnakeBodyArray[i].SetY(defultHeadY);
		}

		Head = &SnakeBodyArray[0];

		void FoodRand();
	}

	virtual void Work()
	{
		if (InputUp())
		{
			if (HeadDirection != DIR_DOWN)
				HeadDirection = DIR_UP;
		}
		else if (InputDown())
		{
			if (HeadDirection != DIR_UP)
				HeadDirection = DIR_DOWN;
		}
		else if (InputLeft())
		{
			if (HeadDirection != DIR_RIGHT)
				HeadDirection = DIR_LEFT;
		}
		else if (InputRight())
		{
			if (HeadDirection != DIR_LEFT)
				HeadDirection = DIR_RIGHT;
		}

		//身體跟著頭
		for (int i = BodyCountMax - 1; i > 0; i--)
		{
			SnakeBodyArray[i] = SnakeBodyArray[i - 1];
		}

		if (HeadDirection == DIR_UP)
			Head->ShiftY(-Speed);
		if (HeadDirection == DIR_DOWN)
			Head->ShiftY(Speed);
		if (HeadDirection == DIR_LEFT)
			Head->ShiftX(-Speed);
		if (HeadDirection == DIR_RIGHT)
			Head->ShiftX(Speed);

		if (Head->GetX() >= SpaceWidth)
			Head->SetX(0);
		if (Head->GetX() < 0)
			Head->SetX(SpaceWidth-1);
		if (Head->GetY() >= SpaceHeight)
			Head->SetY(0);
		if (Head->GetY() < 0)
			Head->SetY(SpaceHeight-1);
		
		//吃到身體減一節
		for (int i = 1; i < BodyCurrentCount; i++)
		{
			if ((SnakeBodyArray[i].GetX() == Head->GetX()) && (SnakeBodyArray[i].GetY() == Head->GetY()))
			{
				if (BodyCurrentCount > BodyCountMin)
				{
					BodyCurrentCount--;
					break;
				}
			}
		}

		//吃到食物多一節
		if (
			(Head->GetX() == Food.GetX())
			&& 
			(Head->GetY() == Food.GetY())
			)
		{
			FoodRand();

			if (BodyCurrentCount < BodyCountMax)
			{
				BodyCurrentCount++;
			}
		}
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
	const int spaceWidth = SpaceWidth * BodySize;
	const int spaceHight = SpaceHeight * BodySize;

	KeyStateManager keyStateManager;
	void KeyStateManager_Init()
	{
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		keyStateManager = KeyStateManager();
	}

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
	TimerWin gtr = TimerWin(1000/10);
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
		if (!gtr.Work())return;

		keyStateManager.Work();

		Game::Work();
	}
	void Draw(HDC hdc)
	{
		Rectangle(hdc, StartX, StartY, StartX + spaceWidth, StartY + spaceHight);

		TcString tString = TcString();
		tString = L"BodyCurrentCount : ";
		tString += BodyCurrentCount;
		TextOut(hdc, 300, 0, tString, tString.len);

		for (int i = 0; i < BodyCurrentCount; i++)
		{
			int x = StartX + (int)SnakeBodyArray[i].GetX() * BodySize;
			int y = StartY + (int)SnakeBodyArray[i].GetY() * BodySize;

			Rectangle(hdc, x, y, x + BodySize, y + BodySize);
		}

		int foodX = StartX + Food.GetX() * BodySize;
		int foodY = StartY + Food.GetY() * BodySize;
		Ellipse(hdc, foodX, foodY, foodX + BodySize, foodY + BodySize);
	}
};

#endif
