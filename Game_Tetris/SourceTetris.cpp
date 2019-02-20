#include "GameTetris.h"

#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"
#include "time_ex.h"
#include "TcString.h"

class WinGame :public GameTetris
{
private:
	HBRUSH hBRUSH[COLOR_COUNT];
	HBRUSH hollowBRUSH;

	KeyStateManager keyStateManager;
	bool InputLeft()final override { return keyStateManager.IsDown(VK_LEFT); }
	bool InputUp()final override { return keyStateManager.IsDown(VK_UP); }
	bool InputRight()final override { return keyStateManager.IsDown(VK_RIGHT); }
	bool InputDown()final override { return keyStateManager.IsDown(VK_DOWN); }

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
	TimerWin tr = TimerWin(1000 / 15);
public:

	void Init()final override
	{
		hBRUSH[RED] = CreateSolidBrush(RGB(255, 0, 0));
		hBRUSH[GREEN] = CreateSolidBrush(RGB(0, 255, 0));
		hBRUSH[BLUE] = CreateSolidBrush(RGB(0, 0, 255));
		hBRUSH[YELLOW] = CreateSolidBrush(RGB(255, 255, 0));

		hollowBRUSH = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		keyStateManager = KeyStateManager();

		GameTetris::Init();
	}
	void Work()
	{
		if (!tr.Work())return;

		keyStateManager.Work();
		GameTetris::Work();
	}
	void Draw(HDC hdc)
	{
		//
		int startX = 200, startY = 0;

		//底框
		Rectangle(hdc, startX, startY, startX+Puzzle_Size*Puzzle_W, startY+Puzzle_Size*Puzzle_H);

		//正落下
		for (int h = 0; h < CurPuzzle_H; h++)
			for (int w = 0; w < CurPuzzle_W; w++)
			{
				int color = vvCurPuzzle[w][h];
				if (color >= COLOR_COUNT)color = 0;
				if (color > 0)
				{
					HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hBRUSH[color]);
					Rectangle(hdc, startX + (CurPuzzle_X + w )* Puzzle_Size, startY + (CurPuzzle_Y + h )* Puzzle_Size, startX + (CurPuzzle_X + (w + 1))*Puzzle_Size, startY + (CurPuzzle_Y + (h + 1))*Puzzle_Size);
					SelectObject(hdc, oriBrush);
				}
			}

		//已落下
		for (int h = 0; h < Puzzle_H; h++)
			for (int w = 0; w<Puzzle_W; w++)
			{
				int color = vvPuzzle[w][h];
				if (color >= COLOR_COUNT)color = 0;
				if (color > 0)
				{
					HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hBRUSH[color]);
					Rectangle(hdc, startX+w*Puzzle_Size, startY+h*Puzzle_Size, startX+(w + 1)*Puzzle_Size, startY+(h + 1)*Puzzle_Size);
					SelectObject(hdc, oriBrush);
				}
			}

		//HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hollowBRUSH);
		//Rectangle(hdc, FocusX*PUZZLE_SIZE_W, FocusY*PUZZLE_SIZE_H, (FocusX + 1)*PUZZLE_SIZE_W, (FocusY + 1)*PUZZLE_SIZE_H);
		//SelectObject(hdc, oriBrush);
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
		return GameTetris::WindowsWidth;
	}
	int GetWindowsHeight()override
	{
		return GameTetris::WindowsHeight;
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