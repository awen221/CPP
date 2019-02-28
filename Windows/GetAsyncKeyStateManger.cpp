#include "GetAsyncKeyStateManger.h"
#include<map>
#include<windows.h>

//GetAsyncKeyStateBase
GetAsyncKeyStateBase::GetAsyncKeyStateBase() { }
GetAsyncKeyStateBase::GetAsyncKeyStateBase(const char& key_code) { KeyCode = key_code; }
void GetAsyncKeyStateBase::SetKeyCode(const char& key_code) { KeyCode = key_code; }
char GetAsyncKeyStateBase::GetKeyCode() { return KeyCode; }
bool GetAsyncKeyStateBase::IsDown() { return PressDown; }
bool GetAsyncKeyStateBase::IsUp() { return !PressDown; }
bool GetAsyncKeyStateBase::IsTriggerDown() 
{
	return TriggerDown; 
}
bool GetAsyncKeyStateBase::IsTriggerUp() { return TriggerUp; }
void GetAsyncKeyStateBase::Work()
{
	//¨ú±o²{¦b«öÁä«öÀ£ª¬ºA
	bool NowPressDown = GetAsyncKeyState(KeyCode) < 0;

	if (NowPressDown)
	{
		TriggerUp = false;
		TriggerDown = !PressDown;
	}
	else
	{
		TriggerDown = false;
		TriggerUp = PressDown;
	}

	//¬ö¿ý«öÁä«öÀ£ª¬ºA
	PressDown = NowPressDown;
}

//GetAsyncKeyStateAdvanced
bool GetAsyncKeyStateAdvanced::CheckIsDouble(const unsigned int& tick)
{
	if (PreTriggerDownTick == 0)return false;

	unsigned int TickInterval = tick - PreTriggerDownTick;

	if (TickInterval > DoubleTickInterval)return false;
	if (PreIsDoubleTick == PreTriggerDownTick)return false;

	PreIsDoubleTick = tick;

	return true;
}
GetAsyncKeyStateAdvanced::GetAsyncKeyStateAdvanced() {}
GetAsyncKeyStateAdvanced::GetAsyncKeyStateAdvanced(const char& key_code) :GetAsyncKeyStateBase(key_code) {}
bool GetAsyncKeyStateAdvanced::IsDouble() { return Double; }
void GetAsyncKeyStateAdvanced::SetDoubleTickInterval(const unsigned int& doubleTickInterval) { DoubleTickInterval = doubleTickInterval; }
void GetAsyncKeyStateAdvanced::Work()
{
	Double = false;

	GetAsyncKeyStateBase::Work();

	if (GetAsyncKeyStateBase::IsTriggerDown())
	{
		unsigned int tick = GetTickCount();

		Double = CheckIsDouble(tick);

		PreTriggerDownTick = tick;
	}
}
	
//KeyStateManager
typedef std::map<char, GetAsyncKeyStateAdvanced> Map_KeyState;
Map_KeyState map_KeyState = Map_KeyState();
void KeyStateManager::AddKeyState(char key_code)
{
	if (map_KeyState.count(key_code) == 0)
	{
		map_KeyState[key_code] = GetAsyncKeyStateAdvanced(key_code);
	}
}
void KeyStateManager::Work()
{
	for (Map_KeyState::iterator _iterator = map_KeyState.begin(); _iterator != map_KeyState.end(); _iterator++)
	{
		_iterator->second.Work();
	}
}
bool KeyStateManager::IsTriggerDown(char key_code) 
{
	return map_KeyState[key_code].IsTriggerDown(); 
}
bool KeyStateManager::IsTriggerUp(char key_code) { return map_KeyState[key_code].IsTriggerUp(); }
bool KeyStateManager::IsDown(char key_code) { return map_KeyState[key_code].IsDown(); }
bool KeyStateManager::IsUp(char key_code) { return map_KeyState[key_code].IsUp(); }
bool KeyStateManager::IsDouble(char key_code) { return map_KeyState[key_code].IsDouble(); }