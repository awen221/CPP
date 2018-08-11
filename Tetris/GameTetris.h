#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "random.h"

class GameTetris
{
private:

protected:
	enum { Tetris_W = 10, Tetris_H = 20 , Tetris_Size = 50};
	int vvTetris[Tetris_W][Tetris_H];

	enum { NONE,RED, GREEN, BLUE, YELLOW, COLOR_COUNT=4	};

	virtual bool InputUp() = 0;
	virtual bool InputDown() = 0;
	virtual bool InputLeft() = 0;
	virtual bool InputRight() = 0;
public:
	enum { WindowsWidth = 800, WindowsHeight = 600 };
	GameTetris() {}
	~GameTetris() {}

	virtual void Init()
	{
	}
	virtual void Work()
	{
		if (InputUp())
		{
		}
		if (InputDown())
		{
		}
		if (InputLeft())
		{
		}
		if (InputRight())
		{
		}
	}
};

#endif
