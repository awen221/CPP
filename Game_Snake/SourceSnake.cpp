#include "Snake.h"

#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"
#include "time_ex.h"
#include "TcString.h"

class WinGame :public GameSnake
{
private:


public:

	void Init()final override
	{
		GameSnake::Init();
	}
	void Work()
	{
		GameSnake::Work();
	}
	void Draw(HDC hdc)
	{

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