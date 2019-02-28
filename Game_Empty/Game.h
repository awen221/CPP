#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "windows.h"

class Game
{


protected:
	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;

public:
	Game() {}
	~Game() {}

	virtual void Init()
	{
	}

	virtual void Work()
	{
	}
};

#include "GetAsyncKeyStateManger.h"

class WinGame :public Game
{
private:
	const int StartX = 40;
	const int StartY = 60;
	const int spaceWidth = 720;
	const int spaceHight = 540;

	KeyStateManager keyStateManager;
	void KeyStateManager_Init()
	{
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		keyStateManager = KeyStateManager();
	}
protected:
	bool InputLeft()final override { return keyStateManager.IsDown(VK_LEFT); }
	bool InputUp()final override { return keyStateManager.IsDown(VK_UP); }
	bool InputRight()final override { return keyStateManager.IsDown(VK_RIGHT); }
	bool InputDown()final override { return keyStateManager.IsDown(VK_DOWN); }
public:
	void Init()final override
	{
		KeyStateManager_Init();

		Game::Init();
	}
	void Work()final override
	{
		keyStateManager.Work();

		Game::Work();
	}
	void Draw(HDC hdc)
	{
		Rectangle(hdc, StartX, StartY, StartX + spaceWidth, StartY + spaceHight);
	}
};

#endif
