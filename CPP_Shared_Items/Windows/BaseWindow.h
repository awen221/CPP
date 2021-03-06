#ifndef _BASE_WINDOW_H_
#define _BASE_WINDOW_H_

#include <windows.h>


//定義標題列文字長度
#define MAX_LOADSTRING 100

class BaseWindow
{
public:
	//視窗指標
	static BaseWindow* pCurApp;
	//建構式
	BaseWindow();
	//主程式進入點
	int winMain(HINSTANCE, HINSTANCE, LPTSTR, int);

private:
	//標題列文字
	TCHAR szTitle[MAX_LOADSTRING];
	//視窗類別名稱
	TCHAR szWindowClass[MAX_LOADSTRING];

	//註冊類別
	ATOM MyRegisterClass(HINSTANCE hInstance);
	//初始化
	BOOL InitInstance(HINSTANCE, int);
	//基底視窗訊息處理
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

	//視窗Handle
	HWND hWnd;
	//緩衝DC
	HDC BackDrawDC;
	//預設繪圖區寬,高
	int Default_Width, Default_Height;
	//緩衝
	HBITMAP BackBMP;
	//雙緩衝繪圖
	void OnPaint(HDC);

	///abstract
	//標題文字
	virtual TCHAR* GetTitle() = 0;
	//視窗類別
	virtual TCHAR* GetWindowsClass() = 0;
	//視窗寬
	virtual int GetWindowsWidth() = 0;
	//視窗高
	virtual int GetWindowsHeight() = 0;
	//初始
	virtual void Init() = 0;
	//工作
	virtual void Proc() = 0;
	//繪圖
	virtual void Draw(HDC) = 0;
} ;
///example
//class mainWindow :private BaseWindow
//{
//private:
//	///overwrite abstract
//	//標題文字
//	TCHAR * GetTitle()override {
//		return (TCHAR *)TEXT("mainWindows");
//	};
//	//視窗類別
//	TCHAR* GetWindowsClass()override {
//		return (TCHAR *)TEXT("mainWindows");
//	};
//	//視窗寬
//	int GetWindowsWidth()override { return 800; };
//	//視窗高
//	int GetWindowsHeight()override { return 600; };
//
//	//初始
//	void Init()override
//	{
//
//	}
//	//工作
//	void Proc()override
//	{
//
//	}
//	//繪圖
//	void Draw(HDC hdc)override
//	{
//
//	}
//
//public:
//	mainWindow() :BaseWindow() {}
//};
//mainWindow win = mainWindow();

class CursorManger
{
private:
	long CursorX = 0;
	long CursorY = 0;
	long CursorX_Shift = 0;
	long CursorY_Shift = 0;
	bool CursorX_Chang = false;
	bool CursorY_Chang = false;
public:
	CursorManger();
	void Work();

	long GetCursorX();
	long GetCursorY();
	long GetCursorX_Shift();
	long GetCursorY_Shift();
	bool GetCursorX_Chang();
	bool GetCursorY_Chang();
};

////{{NO_DEPENDENCIES}}
//// Microsoft Visual C++ generated include file.
//// Used by Win32Project.rc
////
//#define IDS_APP_TITLE			103
//#define IDR_MAINFRAME			128
//#define IDD_WIN32PROJECT_DIALOG	102
//#define IDD_ABOUTBOX			103
//#define IDM_ABOUT				104
//#define IDM_EXIT				105
//#define IDI_WIN32PROJECT			107
//#define IDI_SMALL				108
//#define IDC_WIN32PROJECT			109
//#define IDC_MYICON				2
//#ifndef IDC_STATIC
//#define IDC_STATIC				-1
//#endif
//// 下一個新增物件的預設值
////
//#ifdef APSTUDIO_INVOKED
//#ifndef APSTUDIO_READONLY_SYMBOLS
//
//#define _APS_NO_MFC					130
//#define _APS_NEXT_RESOURCE_VALUE	129
//#define _APS_NEXT_COMMAND_VALUE		32771
//#define _APS_NEXT_CONTROL_VALUE		1000
//#define _APS_NEXT_SYMED_VALUE		110
//#endif

#endif