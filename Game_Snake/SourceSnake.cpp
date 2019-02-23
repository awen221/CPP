#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"
#include "time_ex.h"
#include "TcString.h"

#include "Game.h"

class WinGame :public GameSnake
{
private:
protected:
	KeyStateManager keyStateManager;
	bool InputLeft()final override { return keyStateManager.IsDown(VK_LEFT); }
	bool InputUp()final override { return keyStateManager.IsDown(VK_UP); }
	bool InputRight()final override { return keyStateManager.IsDown(VK_RIGHT); }
	bool InputDown()final override { return keyStateManager.IsDown(VK_DOWN); }
public:
	void Init()final override
	{
		GameSnake::Init();
	}
	void Work()final override
	{
		GameSnake::Work();
	}
	void Draw(HDC hdc)
	{
		Rectangle(hdc, HeadX, HeadY, HeadX + BodySize, HeadY + BodySize);
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
		return GameSnake::WindowsWidth;
	}
	int GetWindowsHeight()override
	{
		return GameSnake::WindowsHeight;
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