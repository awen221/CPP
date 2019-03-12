#include "BaseWindow.h"
#include "time_ex.h"
using namespace Time_Ex;

#include "Game.h"
#include "TString.h"
using namespace TString;

//#include "TcString.h"

class mainWindow :private BaseWindow
{
private:
	enum { WindowsWidth = 800, WindowsHeight = 600, };
	///overwrite abstract
	TCHAR * GetTitle()final override
	{
		return (TCHAR *)L"mainWindows";
	}
	TCHAR* GetWindowsClass()final override
	{
		return (TCHAR *)TEXT("mainWindows");
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
			tstring tString = L"TimePass : ";
			unsigned int tp = GetPassTime();
			tString += tp;
			TextOut(hdc, 0, 0, tString, tString.length());
		}
	};
	class TimerWin : public Timer
	{
	public:
		TimerWin(unsigned int len) :Timer(len) {};

		void Draw(HDC hdc)
		{
			tstring tString = L"Timer : ";
			static bool OnTimerPluse = false;
			if (GetOnTimer())
			{
				OnTimerPluse = !OnTimerPluse;
			}

			if (OnTimerPluse)
			{
				tString += L"O";
			}
			else
			{
				tString += L"X";
			}

			TextOut(hdc, 0, 20, tString, tString.length());
		}
	};
	class FpsWin : public FPS
	{
	public:
		void Draw(HDC hdc)
		{
			tstring tString = L"FPS : ";
			tString += GetFPS();
			TextOut(hdc, 0, 40, tString, tString.length());
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