#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "random.h"

class GameTetris
{
private:

protected:
	enum { NONE, RED, GREEN, BLUE, YELLOW, COLOR_COUNT };
	const int Puzzle_Size = 30;
	//enum { Puzzle_Size = 30 };
	enum { Puzzle_W = 10, Puzzle_H = 20 };
	enum { CurPuzzle_W = 4,CurPuzzle_H = 4};
	enum { PuzzleType_I, PuzzleType_O, PuzzleType_T, PuzzleType_Z, PuzzleType_S, PuzzleType_L, PuzzleType_J, PuzzleType_Count };

	int vvPuzzle[Puzzle_W][Puzzle_H];
	int vvCurPuzzle[CurPuzzle_W][CurPuzzle_H];

	int CurPuzzle_X, CurPuzzle_Y;
	void CurTetris_Init()
	{
		int* pCurPuzzle = &(vvCurPuzzle[0][0]);
		for (int i = 0; i < CurPuzzle_W*CurPuzzle_H; i++)
		{
			pCurPuzzle[i] = 0;
		}
	}
	void SetCurTetris_I()
	{
		CurTetris_Init();
		vvCurPuzzle[0][1] = RED;
		vvCurPuzzle[1][1] = RED;
		vvCurPuzzle[2][1] = RED;
		vvCurPuzzle[3][1] = RED;
	}

	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
public:
	enum { WindowsWidth = 800, WindowsHeight = 600 };
	GameTetris() {}
	~GameTetris() {}

	bool CheckHit()
	{
		for (int h = 0; h < CurPuzzle_H; h++)
			for (int w = 0; w < CurPuzzle_W; w++)
			{
				if (vvCurPuzzle[w][h] == 0)continue;
				int cx = w + CurPuzzle_X;
				int cy = h + CurPuzzle_Y;

				if (cx < 0)
					return true;
				if (cx >= Puzzle_W)
					return true;
				if (cy >= Puzzle_H)
					return true;

				if (vvPuzzle[cx][cy] != 0)
					return true;
			}

		return false;
	}

	void CopyPuzzle()
	{
		for (int h = 0; h < CurPuzzle_H; h++)
			for (int w = 0; w < CurPuzzle_W; w++)
			{
				if (vvCurPuzzle[w][h] == 0)continue;

				int cx = w + CurPuzzle_X;
				int cy = h + CurPuzzle_Y;

				vvPuzzle[cx][cy] = vvCurPuzzle[w][h];
			}
	}

	virtual void Init()
	{
		int* pPuzzle = &(vvPuzzle[0][0]);
		for (int i = 0; i < Puzzle_W * Puzzle_H; i++)
		{
			pPuzzle[i] = 0;
		}

		CurPuzzle_X = 0, CurPuzzle_Y = 0;
		CurTetris_Init();
		SetCurTetris_I();
	}

	virtual void Work()
	{

		if (InputLeft())
		{
			int oriX = CurPuzzle_X;
			CurPuzzle_X--;

			if(CheckHit())
				CurPuzzle_X = oriX;

		}
		if (InputRight())
		{
			int oriX = CurPuzzle_X;
			CurPuzzle_X++;

			if (CheckHit())
				CurPuzzle_X = oriX;
		}

		if (InputDown())
		{
			int oriY = CurPuzzle_Y;
			CurPuzzle_Y++;

			if (CheckHit())
			{
				CurPuzzle_Y = oriY;

				CopyPuzzle();

				CurPuzzle_Y = 0;
			}
				
		}

	}
};

#endif
