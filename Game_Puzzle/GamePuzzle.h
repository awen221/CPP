#ifndef _GAME_PUZZLE_H_
#define _GAME_PUZZLE_H_

#include "random.h"

class GamePuzzle
{
private:

protected:
	RANDOM _RANDOM = RANDOM();
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
	GamePuzzle() {}
	~GamePuzzle() {}

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

#endif#pragma once
