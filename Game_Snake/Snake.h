#ifndef _GAME_TETRIS_H_
#define _GAME_TETRIS_H_

#include "random.h"

class GameSnake
{
private:

protected:


public:
	GameSnake() {}
	~GameSnake() {}
	enum { WindowsWidth = 800, WindowsHeight = 600 };

	virtual void Init()
	{
	}

	virtual void Work()
	{
	}
};

#endif
