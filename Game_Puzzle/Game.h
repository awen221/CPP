#ifndef GAME_PUZZLE_H
#define GAME_PUZZLE_H

#include "random.h"
using RANDOM_Class = RANDOM::RANDOM_Class;
#include "time.h"

//Puzzle
class Game
{
private:

protected:
	RANDOM_Class _RANDOM = RANDOM_Class(clock());
	enum { PUZZLE_W = 10, PUZZLE_H = 10 };
	int VV_PUZZLE[PUZZLE_W][PUZZLE_H];
	enum { RED, GREEN, BLUE, YELLOW, COLOR_COUNT };
	enum { PUZZLE_SIZE_W = 50, PUZZLE_SIZE_H = 50 };
	int FocusX, FocusY;

	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
public:
	enum { WindowsWidth = 800, WindowsHeight = 600 };
	Game() {}
	~Game() {}

	virtual void Init()
	{
		FocusX = 0, FocusY = 0;

		int* pPuzzle = &(VV_PUZZLE[0][0]);
		for (int i = 0; i < PUZZLE_W*PUZZLE_H; i++)
		{
			pPuzzle[i] = _RANDOM.GetRand() % COLOR_COUNT;
		}

		//for (int i = 0; i<PUZZLE_W; i++)
		//	for (int j = 0; j < PUZZLE_H; j++)
		//	{
		//		VV_PUZZLE[i][j] = _RANDOM.GetRand() % COLOR_COUNT;
		//	}
	}
	virtual void Work()
	{
		if (InputUp())
		{
			FocusY--;
			if (FocusY < 0)FocusY = 0;
		}
		if (InputDown())
		{
			FocusY++;
			if (FocusY >= PUZZLE_H)FocusY = PUZZLE_H-1;
		}
		if (InputLeft())
		{
			FocusX--;
			if (FocusX < 0)FocusX = 0;
		}
		if (InputRight())
		{
			FocusX++;
			if (FocusX >= PUZZLE_W)FocusX = PUZZLE_W - 1;
		}
	}
};


#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"

class WinGame :public Game
{
private:
	//HPEN hPEN[COLOR_COUNT];
	HBRUSH hBRUSH[COLOR_COUNT];
	HBRUSH hollowBRUSH;

	KeyStateManager keyStateManager = KeyStateManager();
	bool InputUp()final override { return keyStateManager.IsTriggerDown(VK_UP); }
	bool InputDown()final override { return keyStateManager.IsTriggerDown(VK_DOWN); }
	bool InputLeft()final override { return keyStateManager.IsTriggerDown(VK_LEFT); }
	bool InputRight()final override { return keyStateManager.IsTriggerDown(VK_RIGHT); }
public:

	void Init()final override
	{
		//hPEN[RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		//hPEN[GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		//hPEN[BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		//hPEN[YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));

		hBRUSH[RED] = CreateSolidBrush(RGB(255, 0, 0));
		hBRUSH[GREEN] = CreateSolidBrush(RGB(0, 255, 0));
		hBRUSH[BLUE] = CreateSolidBrush(RGB(0, 0, 255));
		hBRUSH[YELLOW] = CreateSolidBrush(RGB(255, 255, 0));

		hollowBRUSH = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

		keyStateManager = KeyStateManager();
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		Game::Init();
	}
	void Work()
	{
		keyStateManager.Work();
		Game::Work();
	}
	void Draw(HDC hdc)
	{
		int StartX, StartY;
		StartX = 0;
		StartY = 60;



		for (int i = 0; i<PUZZLE_W; i++)
			for (int j = 0; j < PUZZLE_H; j++)
			{
				int color = VV_PUZZLE[i][j];
				//HPEN oriPen = (HPEN)SelectObject(hdc, hPEN[color]);
				HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hBRUSH[color]);

				int DrawPuzzleX, DrawPuzzleY;
				DrawPuzzleX = i * PUZZLE_SIZE_W + StartX;
				DrawPuzzleY = j * PUZZLE_SIZE_H + StartY;
				Ellipse(hdc, DrawPuzzleX, DrawPuzzleY, DrawPuzzleX + PUZZLE_SIZE_W, DrawPuzzleY + PUZZLE_SIZE_H);

				//SelectObject(hdc, oriPen);
				SelectObject(hdc, oriBrush);
			}

		int DrawFocusX = FocusX * PUZZLE_SIZE_W + StartX;
		int DrawFocusY = FocusY * PUZZLE_SIZE_H + StartY;
		HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hollowBRUSH);
		Rectangle(hdc, DrawFocusX, DrawFocusY, DrawFocusX + PUZZLE_SIZE_W, DrawFocusY+PUZZLE_SIZE_H);
		SelectObject(hdc, oriBrush);

	}
};

#endif#pragma once
