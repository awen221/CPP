#include"time_ex.h"
#include<time.h>

namespace Time_Ex
{
	#pragma region TimePass
	//public
	TimePass::TimePass()
	{
		Reset();
	}
	void TimePass::Reset()
	{
		PassTime = 0;
		TotalPassTime = 0;
		int _clock = clock();
		PreTime = _clock;

		StartTime = _clock;
	}
	void TimePass::Work()
	{
		if (PreTime == 0)
		{
			Reset();
			return;
		}

		int _clock = clock();

		PassTime = _clock - PreTime;
		TotalPassTime = _clock - StartTime;

		PreTime = _clock;
	}
	unsigned int TimePass::GetStartTime()
	{
		return StartTime;
	}
	unsigned int TimePass::GetPassTime()
	{
		return PassTime;
	}
	unsigned int TimePass::GetTotalPassTime()
	{
		return TotalPassTime;
	}
	#pragma endregion

	#pragma region Timer
	//public
	Timer::Timer()
	{
	}
	Timer::Timer(unsigned int interval)
	{
		SetTimer(interval);
	}
	void Timer::SetTimer(unsigned int interval)
	{
		Interval = 0;
		TimerPassTime = 0;
		onTimer = false;

		Interval = interval;
	}
	void Timer::Work()
	{
		if (Interval == 0)return;

		TimePass::Work();
		TimerPassTime += GetPassTime();
		if (TimerPassTime >= Interval)
		{
			if (Interval == 0)
			{
				TimerPassTime = 0;
			}
			else
			{
				TimerPassTime %= Interval;
			}

			onTimer = true;
		}
		else
			onTimer = false;
	}
	bool Timer::GetOnTimer()
	{
		return onTimer;
	}
	#pragma endregion

	#pragma region FPS
	const unsigned int msOfSec = 1000;
	//public
	FPS::FPS() :Timer(msOfSec)
	{
		FramesCount = 0;
		Fps = 0;
	}
	void FPS::Work()
	{
		FramesCount++;
		Work();
		if (GetOnTimer())
		{
			Fps = FramesCount;
			FramesCount = 0;
		}
	}
	unsigned int FPS::GetFPS()
	{
		return Fps;
	}
	#pragma endregion
}