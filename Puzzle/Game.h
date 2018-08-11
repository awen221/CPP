#ifndef _GAME_H_
#define _GAME_H_

#include "random.h"

class Game
{
private:

protected:
	RANDOM _RANDOM = RANDOM();
	enum { PUZZLE_W = 10, PUZZLE_H = 10 };
	int VV_PUZZLE[PUZZLE_W][PUZZLE_H];
	enum { RED, GREEN, BLUE, YELLOW, COLOR_COUNT };
	enum { PUZZLE_SIZE_W = 50, PUZZLE_SIZE_H = 50 };
public:
	enum { WindowsWidth = 800, WindowsHeight = 600 };
	Game() {}
	~Game() {}

	virtual void Init()
	{
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
	}
};

#endif#pragma once
