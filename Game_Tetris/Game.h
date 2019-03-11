#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include <stdio.h>
//Tetris
//class Puzzle
//{
//	int Width;
//	int* pPuzzle;
//public:
//	Puzzle() {}
//	~Puzzle() {}
//};

#include "TcString.h"

class Game
{
private:

protected:

	enum { NONE, RED, GREEN, BLUE, YELLOW, COLOR_COUNT };
	enum { PuzzleType_I, PuzzleType_O, PuzzleType_T, PuzzleType_Z, PuzzleType_S, PuzzleType_L, PuzzleType_J, PuzzleType_Count };

	
	static const int Puzzle_W = 10;
	static const int Puzzle_H = 20;
	static const int CurPuzzle_Width = 4;

	const int Puzzle_I[CurPuzzle_Width][CurPuzzle_Width] =
	{
		{ 0,	0,		0,		0},
		{ RED,	RED,	RED,	RED},
		{ 0,	0,		0,		0},
		{ 0,	0,		0,		0}
	};
	//const int Puzzle_O[CurPuzzle_Width][CurPuzzle_Width] =
	//{
	//	{ 0,	0,		0,		0 },
	//	{ 0,	BLUE,	BLUE,	0 },
	//	{ 0,	BLUE,	BLUE,	0 },
	//	{ 0,	0,		0,		0 }
	//};

	int vvPuzzle[Puzzle_H][Puzzle_W];
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

		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
			{
				vvCurPuzzle[h][w] = Puzzle_I[h][w];
			}
	}

	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;

	virtual bool InputRotate() = 0;

	virtual bool InputSaveGame() = 0;
	virtual bool InputLoadGame() = 0;


	void SaveGame()
	{
		FILE* pFile = fopen("save.sav", "wb");
		if (pFile == NULL)
			return;
		int version = 0;
		fwrite(&version, sizeof(version), 1, pFile);

		fwrite(&(vvPuzzle[0][0]), sizeof(vvPuzzle), 1, pFile);
		fwrite(&(vvCurPuzzle[0][0]), sizeof(vvCurPuzzle), 1, pFile);
		fwrite(&CurPuzzle_X, sizeof(CurPuzzle_X), 1, pFile);
		fwrite(&CurPuzzle_Y, sizeof(CurPuzzle_Y), 1, pFile);

		fclose(pFile);
	}
	void LoadGame()
	{
		FILE* pFile = fopen("save.sav", "rb");
		if (pFile == NULL)
			return;
		int version = 0;
		fread(&version, sizeof(version), 1, pFile);

		fread(&(vvPuzzle[0][0]), sizeof(vvPuzzle), 1, pFile);
		fread(&(vvCurPuzzle[0][0]), sizeof(vvCurPuzzle), 1, pFile);
		fread(&CurPuzzle_X, sizeof(CurPuzzle_X), 1, pFile);
		fread(&CurPuzzle_Y, sizeof(CurPuzzle_Y), 1, pFile);

		fclose(pFile);
	}
public:

	Game() {}
	~Game() {}

	bool CheckHit(int puzzle[CurPuzzle_Width][CurPuzzle_Width])
	{
		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
			{
				if (puzzle[h][w] == 0)continue;
				int cx = w + CurPuzzle_X;
				int cy = h + CurPuzzle_Y;

				if (cx < 0)
 					return true;
				if (cx >= Puzzle_W)
					return true;

				if (cy >= Puzzle_H)
					return true;

				if (vvPuzzle[cy][cx] != 0)
					return true;
			}

		return false;
	}

	void CopyPuzzle()
	{
		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
			{
				if (vvCurPuzzle[h][w] == 0)continue;

				int cx = w + CurPuzzle_X;
				int cy = h + CurPuzzle_Y;

				vvPuzzle[cy][cx] = vvCurPuzzle[h][w];
			}
	}

	void Rotate()
	{
		int tmpV[CurPuzzle_Width][CurPuzzle_Width];

		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
				tmpV[h][(CurPuzzle_Width-1)-w] = vvCurPuzzle[w][h];

		if (CheckHit(tmpV))return;

		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
				vvCurPuzzle[w][h] = tmpV[w][h];
	}

	bool CheckLine(int index)
	{
		for (int w = 0; w < Puzzle_W; w++)
			if (vvPuzzle[index][w] == 0)
				return false;
		return true;
	}

	void CheckAllLine()
	{
		for (int h = 0; h < Puzzle_H; h++)
			if (CheckLine(h))
			{
				CutLine(h);
			}
	}

	void CutLine(int index)
	{

	}

	virtual void Init()
	{
		TcString str = TcString();
		str = L"LLLL";
		str += L"MMMM";

		for (int h = 0; h < Puzzle_H; h++)
			for (int w = 0; w < Puzzle_W; w++)
				vvPuzzle[h][w] = 0;

		CurPuzzle_X = 0, CurPuzzle_Y = 0;
		CurTetris_Init();
		SetCurTetris_I();
	}

	virtual void Work()
	{
		if (InputRotate())
		{
			Rotate();
		}
		if (InputLeft())
		{
			int oriX = CurPuzzle_X;
			CurPuzzle_X--;

			if(CheckHit(vvCurPuzzle))
				CurPuzzle_X = oriX;

		}
		if (InputRight())
		{
			int oriX = CurPuzzle_X;
			CurPuzzle_X++;

			if (CheckHit(vvCurPuzzle))
				CurPuzzle_X = oriX;
		}

		if (InputDown())
		{
			int oriY = CurPuzzle_Y;
			CurPuzzle_Y++;

			if (CheckHit(vvCurPuzzle))
			{
				CurPuzzle_Y = oriY;

				CopyPuzzle();

				CheckAllLine();

				CurPuzzle_Y = 0;
			}
		}

		if (InputSaveGame())
		{
			SaveGame();
		}
		if (InputLoadGame())
		{
			LoadGame();
		}
	}
};

#include "GetAsyncKeyStateManger.h"
#include <windows.h>
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

	bool InputRotate()final override
	{
		return keyStateManager.IsTriggerDown(VK_SPACE);
	}

	bool InputSaveGame()override final
	{
		return keyStateManager.IsTriggerDown('S');
	}
	bool InputLoadGame()override final
	{
		return keyStateManager.IsTriggerDown('L');
	}
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
		keyStateManager.AddKeyState(VK_SPACE);
		keyStateManager.AddKeyState('S');
		keyStateManager.AddKeyState('L');

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

		//底框
		Rectangle(hdc, startX, startY, startX + Puzzle_Size * Puzzle_W, startY + Puzzle_Size * Puzzle_H);

		//正落下
		for (int h = 0; h < CurPuzzle_Width; h++)
			for (int w = 0; w < CurPuzzle_Width; w++)
			{
				int color = vvCurPuzzle[h][w];
				if (color >= COLOR_COUNT)color = 0;
				if (color > 0)
				{
					HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hBRUSH[color]);
					Rectangle(hdc, startX + (CurPuzzle_X + w)* Puzzle_Size, startY + (CurPuzzle_Y + h)* Puzzle_Size, startX + (CurPuzzle_X + (w + 1))*Puzzle_Size, startY + (CurPuzzle_Y + (h + 1))*Puzzle_Size);
					SelectObject(hdc, oriBrush);
				}
			}

		//已落下
		for (int h = 0; h<Puzzle_H; h++)
			for (int w = 0; w<Puzzle_W; w++)
			{
				int color = vvPuzzle[h][w];
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
