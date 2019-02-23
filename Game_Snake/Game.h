#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

//Snake
class Game
{
private:

protected:
	int HeadX, HeadY;
	const int BodySize = 20;
	enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
	int Direction = DIR_RIGHT;

	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;

public:
	Game() {}
	~Game() {}

	enum { WindowsWidth = 800, WindowsHeight = 600 };

	virtual void Init()
	{
		HeadX = 3;
		HeadY = 3;
	}

	virtual void Work()
	{
		if (InputUp())
		{
			Direction = DIR_UP;
		}
		if (InputDown())
		{
			Direction = DIR_DOWN;
		}
		if (InputLeft())
		{
			Direction = DIR_LEFT;
		}
		if (InputRight())
		{
			Direction = DIR_RIGHT;
		}

		if (Direction == DIR_UP)HeadY--;
		if (Direction == DIR_DOWN)HeadY++;
		if (Direction == DIR_LEFT)HeadX--;
		if (Direction == DIR_RIGHT)HeadX++;
	}
};

#include "windows.h"
#include "GetAsyncKeyStateManger.h"

class WinGame :public Game
{
private:
protected:
	KeyStateManager keyStateManager;
	bool InputLeft()final override { return keyStateManager.IsDown(VK_LEFT); }
	bool InputUp()final override { return keyStateManager.IsDown(VK_UP); }
	bool InputRight()final override { return keyStateManager.IsDown(VK_RIGHT); }
	bool InputDown()final override { return keyStateManager.IsDown(VK_DOWN); }
	void KeyStateManager_Init()
	{
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);

		keyStateManager = KeyStateManager();
	}
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
		int x = HeadX * BodySize;
		int y = HeadY * BodySize;

		Rectangle(hdc, x, y, x + BodySize, y + BodySize);
	}
};

#endif
