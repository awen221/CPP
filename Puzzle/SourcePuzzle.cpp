#include "GamePuzzle.h"

#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"

class WinGame :public GamePuzzle
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

		GamePuzzle::Init();
	}
	void Work()
	{
		keyStateManager.Work();
		GamePuzzle::Work();
	}
	void Draw(HDC hdc)
	{
		for (int i = 0; i<PUZZLE_W; i++)
			for (int j = 0; j < PUZZLE_H; j++)
			{
				int color = VV_PUZZLE[i][j];
				//HPEN oriPen = (HPEN)SelectObject(hdc, hPEN[color]);
				HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hBRUSH[color]);

				Ellipse(hdc, i*PUZZLE_SIZE_W, j*PUZZLE_SIZE_H, (i + 1)*PUZZLE_SIZE_W, (j + 1)*PUZZLE_SIZE_H);

				//SelectObject(hdc, oriPen);
				SelectObject(hdc, oriBrush);
			}

		HBRUSH oriBrush = (HBRUSH)SelectObject(hdc, hollowBRUSH);
		Rectangle(hdc, FocusX*PUZZLE_SIZE_W, FocusY*PUZZLE_SIZE_H, (FocusX + 1)*PUZZLE_SIZE_W, (FocusY + 1)*PUZZLE_SIZE_H);
		SelectObject(hdc, oriBrush);
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
		return GamePuzzle::WindowsWidth;
	}
	int GetWindowsHeight()override
	{
		return GamePuzzle::WindowsHeight;
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