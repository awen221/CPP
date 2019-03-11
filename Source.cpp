#include "Game.h"

//#include "TcString.h"
#include "BaseWindow.h"
#include "time_ex.h"
using namespace Time_Ex;
#include "TString.h"



class mainWindow :private BaseWindow
{
private:
	enum { WindowsWidth = 800, WindowsHeight = 600, };
	///overwrite abstract
	TCHAR * GetTitle()final override
	{
		return L"mainWindows";
	}
	TCHAR* GetWindowsClass()final override
	{
		return L"mainWindows";
	}
	int GetWindowsWidth()final override
	{
		return WindowsWidth;
	}
	int GetWindowsHeight()final override
	{
		return WindowsHeight;
	}

	class TimePassWin : public TimePass
	{
	public:
		void Draw(HDC hdc)
		{
			tstring str = L"TimePass : ";
			unsigned int tp = GetPassTime();
			str += tp;
			TextOut(hdc, 0, 0, str, str.len());
		}
	};
	class TimerWin : public Timer
	{
	public:
		TimerWin(unsigned int len) :Timer(len) {};

		void Draw(HDC hdc)
		{
			tstring str = L"Timer : ";

			static bool OnTimerPluse = false;
			if (GetOnTimer())
			{
				OnTimerPluse = !OnTimerPluse;
			}

			if (OnTimerPluse)
			{
				str += L"O";
			}
			else
			{
				str += L"X";
			}

			TextOut(hdc, 0, 20, str, str.len());
		}
	};
	class FpsWin : public FPS
	{
	public:
		void Draw(HDC hdc)
		{
			tstring str = L"FPS : ";
			unsigned int fps = GetFPS();
			str += fps;

			TextOut(hdc, 0, 40, str, str.len());
		}
	};
	TimePassWin tw = TimePassWin();
	TimerWin tr = TimerWin(1000 / 30);
	FpsWin fw = FpsWin();

	WinGame winGame = WinGame();

	void Init()final override
	{
		winGame.Init();
	}
	void Proc()final override
	{
		tr.Work();

		if (!tr.GetOnTimer())return;
		tw.Work();
		fw.Work();

		winGame.Work();
	}
	void Draw(HDC hdc)final override
	{
		winGame.Draw(hdc);

		tw.Draw(hdc);
		tr.Draw(hdc);
		fw.Draw(hdc);
	}

	

public:
	mainWindow() :BaseWindow() {}
} win = mainWindow();