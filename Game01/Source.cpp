#include "BaseWindow.h"

class mainWindow :private BaseWindow
{
private:
	///overwrite abstract
	//標題文字
	TCHAR * GetTitle()override {
		return (TCHAR *)TEXT("mainWindows");
	};
	//視窗類別
	TCHAR* GetWindowsClass()override {
		return (TCHAR *)TEXT("mainWindows");
	};
	//視窗寬
	int GetWindowsWidth()override { return 800; };
	//視窗高
	int GetWindowsHeight()override { return 600; };

	//初始
	void Init()override {}
	//工作
	void Proc()override {}
	//繪圖
	void Draw(HDC hdc)override {}

public:
	mainWindow() :BaseWindow() {}
};
mainWindow win = mainWindow();