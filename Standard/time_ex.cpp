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
	totalTimePass = 0;
	int _clock = clock();
	preTime = _clock;

	startTime = _clock;
}
void TimePass::Work()
{
	if (preTime == 0)
	{
		Reset();
		return;
	}

	int _clock = clock();

	timePass = _clock - preTime;
	totalTimePass = _clock - startTime;
		
	preTime = _clock;
}
unsigned int TimePass::GetTimePass()
{
	return timePass;
}
unsigned int TimePass::GetStartTime()
{
	return startTime;
}
unsigned int TimePass::GetTotalTimePass()
{
	return totalTimePass;
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
		if (Length == 0)
		{
			PassTime = 0;
		}
		else
		{
			PassTime %= Length;
		}
		
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