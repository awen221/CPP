#include"time_ex.h"
#include<time.h>


#pragma region TimePass
//public
TimePass::TimePass()
{
	Reset();
}
void TimePass::Reset()
{
	timePass = 0 ;
	PreTime = clock();
}
unsigned int TimePass::Work()
{
	if (PreTime == 0)
		timePass = 0;
	else
		timePass = clock() - PreTime;
	PreTime = clock();

	return timePass;
}
unsigned int TimePass::GetTimePass()
{
	return timePass;
}
#pragma endregion

#pragma region Timer
//private
void Timer::Init()
{
	Length = 0;
	PassTime = 0;
	onTimer = false;
}
//public
Timer::Timer()
{
	Init();
}
Timer::Timer(unsigned int length)
{
	Timer::Timer();
	SetTimer(length);
}
void Timer::SetTimer(unsigned int length)
{
	Length = length;
}
bool Timer::GetOnTimer()
{
	return onTimer;
}
bool Timer::Work()
{
	TimePass::Work();
	PassTime += GetTimePass();
	if (PassTime >= Length)
	{
		onTimer = true;
		PassTime %= Length;
	}
	else
		onTimer = false;

	return onTimer;
}
#pragma endregion

#pragma region FPS
//private
void FPS::Init()
{
	FramesCount = 0;
	Fps = 0;
	tr = Timer(msOfSec);
}
//public
FPS::FPS()
{
	Init();
}
bool FPS::Work()
{
	FramesCount++;
	if (tr.Work())
	{
		Fps = FramesCount;
		FramesCount = 0;
		return true;
	}
	return false;
}
unsigned int FPS::GetFPS()
{
	return Fps;
}
#pragma endregion