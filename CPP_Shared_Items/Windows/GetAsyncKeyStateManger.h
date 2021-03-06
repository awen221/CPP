#ifndef _GETASYNCKEYSTATEMANGER_H_
#define _GETASYNCKEYSTATEMANGER_H_


class GetAsyncKeyStateBase
{
private:
	char KeyCode;
	bool PressDown = false;
	bool TriggerDown = false;
	bool TriggerUp = false;
public:
	GetAsyncKeyStateBase();
	GetAsyncKeyStateBase(const char&);
	void SetKeyCode(const char&);
	char GetKeyCode();
	bool IsDown();
	bool IsUp();
	bool IsTriggerDown();
	bool IsTriggerUp();
	virtual void Work();
};
class GetAsyncKeyStateAdvanced :public GetAsyncKeyStateBase
{
private:
	unsigned int PreTriggerDownTick = 0;
	unsigned int PreIsDoubleTick = 0;
	unsigned int DoubleTickInterval = 200;
	bool Double = false;
	bool CheckIsDouble(const unsigned int&);
public:
	GetAsyncKeyStateAdvanced();
	GetAsyncKeyStateAdvanced(const char&);
	bool IsDouble();
	void SetDoubleTickInterval(const unsigned int&);
	void Work()override final;
};

class KeyStateManager
{
public:
	void AddKeyState(char );
	void Work();
	bool IsTriggerDown(char);
	bool IsTriggerUp(char);
	bool IsDown(char);
	bool IsUp(char);
	bool IsDouble(char);
};

#endif