#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "point_base.h"
typedef Point_Template::Point_Template_Class<double> obj;
#include "random.h"
#include "time_ex.h"

//Rhythm
class Game
{
private:

protected:
	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;

	TimePass tp;
	int Score;


	const int PerfectScore = 1000;
	const int GoodScore = 200;
	const int BadScore = -200;

	const int PerfectRange = 500;
	const int GoodRange = 1000;

	int noteTime;
	bool noteUsed;


	const int noteStartX = 200;

	const int noteStartY = 500;
	const int noteRunDistanceY = 400;
	const int noteDestinationY = noteStartY - noteRunDistanceY;

	int noteX, noteY;

	void GameInit()
	{
		Score = 0;

		noteTime = 10 * 1000;
		noteUsed = false;
		noteX = noteStartX;
		noteY = noteStartY;
	}
	
	void GameWork()
	{
		int MusicPlayTime = tp.GetTotalTimePass();

		int CurrentY = (MusicPlayTime*noteRunDistanceY) / noteTime;
		noteY = noteStartY - CurrentY;

		if (!noteUsed)
		{
			if (InputUp())
			{
				//Perfect
				if (MusicPlayTime > (noteTime - PerfectRange))
				{
					if (MusicPlayTime <(noteTime + PerfectRange))
					{
						Score += PerfectScore;
						noteUsed = true;
					}
				}
				//Good
				if (MusicPlayTime >(noteTime - GoodRange))
				{
					if (MusicPlayTime <(noteTime - PerfectRange))
					{
						Score += GoodScore;
						noteUsed = true;
					}
				}
				if (MusicPlayTime >(noteTime + PerfectRange))
				{
					if (MusicPlayTime <(noteTime + GoodRange))
					{
						Score += GoodScore;
						noteUsed = true;
					}
				}

				//if (MusicPlayTime <(noteTime - GoodRange))
				//{
				//	Score += BadScore;
				//	noteUsed = true;
				//}

			}

			//Bad
			if (MusicPlayTime >(noteTime + GoodRange))
			{
				Score += BadScore;
				noteUsed = true;
			}

		}
	}

public:
	Game() {}
	~Game() {}

	virtual void Init()
	{
		tp = TimePass();
		GameInit();
	}

	virtual void Work()
	{
		tp.Work();
		GameWork();
	}
};

#include "windows.h"
#include "GetAsyncKeyStateManger.h"
#include "time_ex.h"
#include "TcString.h"
#include<tchar.h>
#include<string.h>

class WinGame :public Game
{
private:
	const int StartX = 40;
	const int StartY = 60;
	const int spaceWidth = 720;
	const int spaceHight = 540;

	const int noteSize = 20;

	KeyStateManager keyStateManager;
	void KeyStateManager_Init()
	{
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		keyStateManager = KeyStateManager();
	}

protected:

	bool InputLeft()final override { return keyStateManager.IsTriggerDown(VK_LEFT); }
	bool InputUp()final override { return keyStateManager.IsTriggerDown(VK_UP); }
	bool InputRight()final override { return keyStateManager.IsTriggerDown(VK_RIGHT); }
	bool InputDown()final override { return keyStateManager.IsTriggerDown(VK_DOWN); }

public:
	void Init()final override
	{
		KeyStateManager_Init();

		Game::Init();
	}
	void Work()final override
	{
		keyStateManager.Work();

		Game::Work();
	}
	void Draw(HDC hdc)
	{
		Rectangle(hdc, StartX, StartY, StartX + spaceWidth, StartY + spaceHight);

		TcString tString = TcString();

		tString = L"經過時間 : ";
		tString += ((float)tp.GetTotalTimePass()) / 1000;
		tString += L"秒";
		TextOut(hdc, 300, 0, tString, tString.len-5);

		tString = L"Score : ";
		tString += Score;
		TextOut(hdc, 300, 20, tString, tString.len);

		MoveToEx(hdc, StartX, noteDestinationY, NULL);
		LineTo(hdc, StartX + spaceWidth, noteDestinationY);

		if(!noteUsed)
			Ellipse(hdc, noteX- noteSize, noteY- noteSize, noteX + noteSize, noteY + noteSize);
	}
};

#endif
#pragma once
