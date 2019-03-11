#ifndef TIME_EX_H
#define TIME_EX_H

namespace Time_Ex
{

	class TimePass
	{
	private:
		unsigned int PreTime;

		unsigned int StartTime;
		unsigned int PassTime;
		unsigned int TotalPassTime;
	public:
		TimePass();
		void Reset();
		void Work();
		unsigned int GetStartTime();
		unsigned int GetPassTime();
		unsigned int GetTotalPassTime();
	};

	class Timer :private TimePass
	{
	private:
		unsigned int Interval;
		unsigned int TimerPassTime;
		bool onTimer;
	public:
		Timer();
		Timer(unsigned int);
		void SetTimer(unsigned int);
		void Work();
		bool GetOnTimer();
	};

	class FPS :public Timer
	{
	private:
		unsigned int FramesCount;
		unsigned int Fps;
	public:
		FPS();
		void Work();
		unsigned int GetFPS();
	};

}

#endif