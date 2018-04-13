 #ifndef _TIME_EX_H_
#define _TIME_EX_H_


class TimePass
{
private:
	unsigned int PreTime;
	unsigned int timePass;
public:
	TimePass();
	void Reset();
	unsigned int GetTimePass();
	unsigned int Work();
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