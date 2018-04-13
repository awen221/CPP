#include "BaseWindow.h"
#include "GetAsyncKeyStateManger.h"
#include "TcString.h"
#include "time_ex.h"


class WinGame
{
private:
	KeyStateManager keyStateManager = KeyStateManager();

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
public:

	void Init()
	{
		keyStateManager = KeyStateManager();
		keyStateManager.AddKeyState(VK_UP);
		keyStateManager.AddKeyState(VK_DOWN);
		keyStateManager.AddKeyState(VK_LEFT);
		keyStateManager.AddKeyState(VK_RIGHT);
		keyStateManager.AddKeyState(VK_F1);
		keyStateManager.AddKeyState(VK_F2);
		keyStateManager.AddKeyState(VK_SPACE);
		keyStateManager.AddKeyState('P');
	}
	void Work()
	{
		if (!tr.Work())return;
		tw.Work();
		fw.Work();

		keyStateManager.Work();
	}
	void Draw(HDC hdc)
	{
		tw.Draw(hdc);
		tr.Draw(hdc);
		fw.Draw(hdc);
	}
};

class mainWindow :private BaseWindow
{
private:
	///overwrite abstract
	//���D��r
	TCHAR * GetTitle()override 
	{
		return (TCHAR *)TEXT("mainWindows"); 
	}
	//�������O
	TCHAR* GetWindowsClass()override 
	{
		return (TCHAR *)TEXT("mainWindows");
	}
	//�����e
	int GetWindowsWidth()override 
	{
		return 800; 
	}
	//������
	int GetWindowsHeight()override 
	{
		return 600; 
	}

	//��l
	void Init()override 
	{
		winGame.Init();
	}
	//�u�@
	void Proc()override 
	{
		winGame.Work();
	}
	//ø��
	void Draw(HDC hdc)override 
	{
		winGame.Draw(hdc);
	}

	WinGame winGame = WinGame();

public:
	mainWindow() :BaseWindow() {}
};
mainWindow win = mainWindow();