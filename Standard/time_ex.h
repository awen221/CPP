 #ifndef _TIME_EX_H_
#define _TIME_EX_H_


class TimePass
{
private:
	unsigned int preTime;

	unsigned int timePass;
	unsigned int startTime;
	unsigned int totalTimePass;
	
public:
	TimePass();
	void Reset();
	void Work();
	unsigned int GetTimePass();
	unsigned int GetStartTime();
	unsigned int GetTotalTimePass();
};

class Timer :private TimePass
{
private:
	unsigned int Length;
	unsigned int PassTime;
	bool onTimer;
	void Init();
public:
	Timer();
	Timer(unsigned int);
	void SetTimer(unsigned int);
	bool GetOnTimer();
	bool Work();
};

class FPS
{
private:
	const unsigned int msOfSec = 1000;

	unsigned int FramesCount;
	unsigned int Fps;
	Timer tr;
	void Init();
public:
	FPS();
	bool Work();
	unsigned int GetFPS();
};

#endif