#include "BaseWindow.h"

class mainWindow :private BaseWindow
{
private:
	///overwrite abstract
	//���D��r
	TCHAR * GetTitle()override {
		return (TCHAR *)TEXT("mainWindows");
	};
	//�������O
	TCHAR* GetWindowsClass()override {
		return (TCHAR *)TEXT("mainWindows");
	};
	//�����e
	int GetWindowsWidth()override { return 800; };
	//������
	int GetWindowsHeight()override { return 600; };

	//��l
	void Init()override {}
	//�u�@
	void Proc()override {}
	//ø��
	void Draw(HDC hdc)override {}

public:
	mainWindow() :BaseWindow() {}
};
mainWindow win = mainWindow();