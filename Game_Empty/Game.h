#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "windows.h"

class Game
{
private:

protected:


public:
	Game() {}
	~Game() {}

	enum { WindowsWidth = 800, WindowsHeight = 600 };

	virtual void Init()
	{
	}

	virtual void Work()
	{
	}
};

class WinGame :public Game
{
public:
	void Init()final override
	{
		Game::Init();
	}
	void Work()final override
	{
		Game::Work();
	}
	void Draw(HDC hdc)
	{

	}
};

#endif
