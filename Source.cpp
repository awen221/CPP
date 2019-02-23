#include "BaseWindow.h"
#include "Game.h"
#include "time_ex.h"
#include "TcString.h"

class mainWindow :private BaseWindow
{
private:
	///overwrite abstract
	TCHAR * GetTitle()final override
	{
		return (TCHAR *)TEXT("mainWindows");
	}
	TCHAR* GetWindowsClass()final override
	{
		return (TCHAR *)TEXT("mainWindows");
	}
	int GetWindowsWidth()final override
	{
		return Game::WindowsWidth;
	}
	int GetWindowsHeight()final override
	{
		return Game::WindowsHeight;
	}

	class TimePassWin : public TimePass
	{
	public:
		void Draw(HDC hdc)
		{
			TcString tString = TcString();
			tString = L"TimePass : ";
			unsigned int tp = GetTimePass();
			tString += tp;
			TextOut(hdc, 0, 0, tString, tString.len);
		}
	};
	class TimerWin : public Timer
	{
	public:
		TimerWin(unsigned int len) :Timer(len) {};

		void Draw(HDC hdc)
		{
			TcString tString = TcString();
			tString = L"Timer : ";
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

			TextOut(hdc, 0, 20, tString, tString.len);
		}
	};
	class FpsWin : public FPS
	{
	public:
		void Draw(HDC hdc)
		{
			TcString tString = TcString();
			tString = L"FPS : ";
			tString += GetFPS();

			TextOut(hdc, 0, 40, tString, tString.len);
		}
	};
	TimePassWin tw = TimePassWin();
	TimerWin tr = TimerWin(1000 / 30);
	FpsWin fw = FpsWin();

	void Init()final override
	{
		winGame.Init();
	}
	void Proc()final override
	{
		if (!tr.Work())return;
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

	WinGame winGame = WinGame();

public:
	mainWindow() :BaseWindow() {}
} win = mainWindow();