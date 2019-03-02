#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

//Tetris
//class Puzzle
//{
//	int Width;
//	int* pPuzzle;
//public:
//	Puzzle() {}
//	~Puzzle() {}
//};
class Game
{
private:

protected:

	enum { NONE, RED, GREEN, BLUE, YELLOW, COLOR_COUNT };
	enum { PuzzleType_I, PuzzleType_O, PuzzleType_T, PuzzleType_Z, PuzzleType_S, PuzzleType_L, PuzzleType_J, PuzzleType_Count };

	
	static const int Puzzle_W = 10;
	static const int Puzzle_H = 20;
	static const int CurPuzzle_Width = 4;

	//const int Puzzle_I[CurPuzzle_Width][CurPuzzle_Width] =
	//{
	//	{ 0,	0,		0,		0},
	//	{ RED,	RED,	RED,	RED},
	//	{ 0,	0,		0,		0},
	//	{ 0,	0,		0,		0}
	//};
	//const int Puzzle_O[CurPuzzle_Width][CurPuzzle_Width] =
	//{
	//	{ 0,	0,		0,		0 },
	//	{ 0,	BLUE,	BLUE,	0 },
	//	{ 0,	BLUE,	BLUE,	0 },
	//	{ 0,	0,		0,		0 }
	//};

	int vvPuzzle[Puzzle_W][Puzzle_H];
	int vvCurPuzzle[CurPuzzle_Width][CurPuzzle_Width];

	int CurPuzzle_X, CurPuzzle_Y;
	void CurTetris_Init()
	{
		int* pCurPuzzle = &(vvCurPuzzle[0][0]);
		for (int i = 0; i < CurPuzzle_Width*CurPuzzle_Width; i++)
		{
			pCurPuzzle[i] = 0;
		}
	}
	void SetCurTetris_I()
	{
		CurTetris_Init();

		//for (int h = 0; h < CurPuzzle_Width; h++)
		//	for (int w = 0; w < CurPuzzle_Width; w++)
		//	{
		//		vvCurPuzzle[w][h] = Puzzle_I[w][h];
		//	}

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

	Game() {}
	~Game() {}

	bool CheckHit()
	{
		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
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
		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
			{
				if (vvCurPuzzle[w][h] == 0)continue;

				int cx = w + CurPuzzle_X;
				int cy = h + CurPuzzle_Y;

				vvPuzzle[cx][cy] = vvCurPuzzle[w][h];
			}
	}

	virtual void Init()
	{
		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
				vvPuzzle[w][h] = 0;

		//int* pPuzzle = &(vvPuzzle[0][0]);
		//for (int i = 0; i < Puzzle_W * Puzzle_H; i++)
		//{
		//	pPuzzle[i] = 0;
		//}

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

#include "GetAsyncKeyStateManger.h"

class WinGame :public Game
{
private:
	const int Puzzle_Size = 30;

	HBRUSH hBRUSH[COLOR_COUNT];
	HBRUSH hollowBRUSH;

	KeyStateManager keyStateManager = KeyStateManager();
	bool InputUp()final override 
	{ 
		return keyStateManager.IsDown(VK_UP); 
	}
	bool InputDown()final override 
	{ 
		return keyStateManager.IsDown(VK_DOWN); 
	}
	bool InputLeft()final override 
	{
		return keyStateManager.IsDown(VK_LEFT); 
	}
	bool InputRight()final override 
	{
		return keyStateManager.IsDown(VK_RIGHT); 
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
	//TimerWin tr = TimerWin(1000 / 30);
public:

	void Init()final override
	{
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
	void Work()final override
	{
		keyStateManager.Work();
		Game::Work();
	}
	void Draw(HDC hdc)
	{
		//
		int startX = 200, startY = 0;

		//����
		Rectangle(hdc, startX, startY, startX + Puzzle_Size * Puzzle_W, startY + Puzzle_Size * Puzzle_H);

		//�����U
		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
			{
				int color = vvCurPuzzle[w][h];
				if (color >= COLOR_COUNT)color = 0;
				if (color > 0)
				{
					HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hBRUSH[color]);
					Rectangle(hdc, startX + (CurPuzzle_X + w)* Puzzle_Size, startY + (CurPuzzle_Y + h)* Puzzle_Size, startX + (CurPuzzle_X + (w + 1))*Puzzle_Size, startY + (CurPuzzle_Y + (h + 1))*Puzzle_Size);
					SelectObject(hdc, oriBrush);
				}
			}

		//�w���U
		for (int h = 0; h < Puzzle_H; h++)
			for (int w = 0; w<Puzzle_W; w++)
			{
				int color = vvPuzzle[w][h];
				if (color >= COLOR_COUNT)color = 0;
				if (color > 0)
				{
					HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hBRUSH[color]);
					Rectangle(hdc, startX + w * Puzzle_Size, startY + h * Puzzle_Size, startX + (w + 1)*Puzzle_Size, startY + (h + 1)*Puzzle_Size);
					SelectObject(hdc, oriBrush);
				}
			}

		//HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hollowBRUSH);
		//Rectangle(hdc, FocusX*PUZZLE_SIZE_W, FocusY*PUZZLE_SIZE_H, (FocusX + 1)*PUZZLE_SIZE_W, (FocusY + 1)*PUZZLE_SIZE_H);
		//SelectObject(hdc, oriBrush);
	}
};




#endif
