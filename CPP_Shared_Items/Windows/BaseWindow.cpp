//// Win32Project1.cpp : 定義應用程式的進入點。
////
//
//#include "stdafx.h"
//#include "Win32Project1.h"
//
//#define MAX_LOADSTRING 100
//
//// 全域變數: 
//HINSTANCE hInst;                                // 目前執行個體
//WCHAR szTitle[MAX_LOADSTRING];                  // 標題列文字
//WCHAR szWindowClass[MAX_LOADSTRING];            // 主視窗類別名稱
//
//												// 這個程式碼模組中所包含之函式的向前宣告: 
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
#include "BaseWindow.h"
#include <tchar.h>//_tcscpy_s(), _T(),TEXT(),_tWinMain(...)......
//declaration	宣告
//definition	定義
//constructor	建構
//destructor	解構

///global
//Main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	return (BaseWindow::pCurApp)->winMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

///public

//static
BaseWindow* BaseWindow::pCurApp;
//constructor
BaseWindow::BaseWindow() 
{
	pCurApp = this; 
}
//main
int BaseWindow::winMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//// TODO: 在此置入程式碼。

	//// 初始化全域字串
	//LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	_tcscpy_s(szTitle, GetTitle());
	_tcscpy_s(szWindowClass, GetWindowsClass());
	MyRegisterClass(hInstance);

	Init();

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	MSG msg;

	// 主訊息迴圈:
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//}
	
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		Proc();
		InvalidateRect(hWnd, NULL, false);

	} while (msg.message != WM_QUIT);

	ReleaseDC(hWnd, BackDrawDC);
	DeleteDC(BackDrawDC);

	DeleteObject(BackBMP);

	return (int)msg.wParam;
}

///private
//
//  函式: MyRegisterClass()
//
//  用途: 註冊視窗類別。
//
//  註解:
//
//    只有當您希望此程式碼能相容比 Windows 95 的 
//    'RegisterClassEx' 函式更早的 Win32 系統時，
//    才會需要加入及使用這個函式。
//    您必須呼叫這個函式，讓應用程式取得與它相關的 
//    「格式正確」的圖示。
//
ATOM BaseWindow::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	//wcex.hIcon		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32_00));
	wcex.hIcon			= LoadIcon(NULL, NULL);//LoadIcon(NULL, TEXT("icon.ico")) ;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);//0:gary ;1:white ;2:black
	//wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32_00);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	//wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//
//   函式: InitInstance(HINSTANCE, int)
//
//   用途: 儲存執行個體控制代碼並且建立主視窗
//
//   註解:
//
//        在這個函式中，我們會將執行個體控制代碼儲存在全域變數中，
//        並且建立和顯示主程式視窗。
//
BOOL BaseWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//HWND hWnd;

	//hInst = hInstance; // 將執行個體控制代碼儲存在全域變數中

	//hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW /*鎖定視窗大小*/& ~WS_SIZEBOX/*鎖定視窗大小*/,
	//	CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);
	
	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	Default_Width = GetWindowsWidth();
	Default_Height = GetWindowsHeight();
	int w = Default_Width;
	int h = Default_Height;
	//w += GetSystemMetrics(SM_CXDLGFRAME) * 2;
	//h += GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	int x = (ScreenWidth - w) / 2;
	int y = (ScreenHeight - h) / 2;

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, szTitle, szWindowClass, WS_OVERLAPPEDWINDOW, x, y,
		w, h, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	HDC hdc = GetDC(hWnd);
	BackBMP = CreateCompatibleBitmap(hdc, Default_Width, Default_Height);
	BackDrawDC = CreateCompatibleDC(hdc);
	SelectObject(BackDrawDC, BackBMP);

	ReleaseDC(hWnd, hdc);
	DeleteDC(hdc);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函式: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  用途:  處理主視窗的訊息。
//
//  WM_COMMAND	- 處理應用程式功能表
//  WM_PAINT	- 繪製主視窗
//  WM_DESTROY	- 顯示結束訊息然後返回
//
//
//static
LRESULT CALLBACK BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//static
{
	//int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	//case WM_COMMAND:
	//	wmId    = LOWORD(wParam);
	//	wmEvent = HIWORD(wParam);
	//	//剖析功能表選取項目:
	//	switch (wmId)
	//	{
	//	case IDM_ABOUT:
	//		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
	//		break;
	//	case IDM_EXIT:
	//		DestroyWindow(hWnd);
	//		break;
	//	default:
	//		return DefWindowProc(hWnd, message, wParam, lParam);
	//	}
	//	break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		(BaseWindow::pCurApp)->OnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//OnPaint
void BaseWindow::OnPaint(HDC hdc)
{
	//設定繪圖區底色 BackGroundColor:BLACKNESS,WHITENESS
	PatBlt(BackDrawDC, 0, 0, Default_Width, Default_Height, WHITENESS);
	//繪圖
	Draw(BackDrawDC);

	//將繪圖輸出到前景HDC 固定尺寸
	//BitBlt(hdc, 0, 0, Default_Width, Default_Height, BackDrawDC, 0, 0, SRCCOPY);

	//將繪圖輸出到前景HDC 尺寸隨視窗大小縮放
	RECT rc;
	GetClientRect(hWnd, &rc);
	StretchBlt(hdc, 0, 0, rc.right, rc.bottom, BackDrawDC, 0, 0, Default_Width, Default_Height, SRCCOPY);
}


//外框大致分為 細黑框 單層框 雙層框
//WS_OVERLAPPED	= WS_TILED		//有標題列,單層框,標題文字	//此值定義為0x00000000L,也就是為預設值
//視窗種類表示,大概分下列三種
//1.常用的標準視窗
//WS_OVERLAPPED	=> WS_OVERLAPPEDWINDOW = WS_TILEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
//2.只有工作區,沒有標準框架,後者多了細黑框跟可叫出SYSMENU
//WS_POPUP => WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)
//3.子視窗,無法單獨建立,WS_POPUP無法共用,細節還沒試過
//WS_CHILD = WS_CHILDWINDOW																															
//
//以下都是外觀
//WS_SYSMENU					//同預設,多了右上關閉鈕跟可以叫出SYSMENU
//WS_THICKFRAME	= WS_SIZEBOX	//同預設但是多一層框,可拉伸視窗大小
//WS_MINIMIZEBOX				//最小化按鈕,需有WS_SYSMENU
//WS_MAXIMIZEBOX				//最大化按鈕,需有WS_SYSMENU
//WS_VSCROLL					//有垂直捲軸
//WS_HSCROLL					//有水平捲軸
//
//以下是比較特別的
//WS_DISABLED					//起始為停用的視窗,應該是用在控件
//
//以下是一堆不知道殺小跟沒試出來的
//WS_CLIPSIBLINGS							//用在父視窗,有加此WS時,子類視窗區域在重繪時不繪(沒試過,應該是擁有許多子視窗時,節省重繪底部父視窗增加繪圖效率)
//WS_CLIPCHILDREN							//用在子視窗,有加此WS時,同級視窗區域在重繪時不繪(沒試過,應該是擁有許多子視窗時,若子視窗有重疊,底層的子視窗節省重繪)
//WS_MINIMIZE	= WS_ICONIC					//說起始時最小化,試了沒反應
//WS_MAXIMIZE								//說起始時最大化,試了沒反應
//WS_CAPTION ( WS_BORDER | WS_DLGFRAME )	//看起來跟預設一樣...
//WS_BORDER									//看起來跟預設一樣...
//WS_DLGFRAME								//看起來跟預設一樣...
//WS_VISIBLE								//看起來跟預設一樣...
//WS_GROUP									//說是tab會停在此視窗中的控件群裡第一個控件,不知道怎麼試
//WS_TABSTOP								//說是tab會停在此視窗,應該是用在控件,不知道怎麼試
//
//
//EX的樣式
//
//WS_EX_TOPMOST			//視窗固定在最上層
//WS_EX_TOOLWINDOW		//創建一個特別的工具視窗,工作列無按鈕圖示,ALT+TAB也選不到,視窗樣式也是特別的
//WS_EX_TRANSPARENT		//窗體部分為半透明
//WS_EX_LEFTSCROLLBAR	//如有WS_VSCROLL的STYLE時,滾動軸顯示在視窗左側
//WS_EX_RIGHTSCROLLBAR  //如有WS_VSCROLL的STYLE時,滾動軸顯示在視窗右側(此為預設值)
//
//WS_EX_RIGHT			//標題列的文字會靠右,不確定是否有其他效果												,還沒試
//WS_EX_LEFT			//標題列的文字會靠左,不確定是否有其他效果(但預設就是靠左,所以看不出來)					,還沒試
//WS_EX_CONTEXTHELP		//右上增加一個問號按鈕,按了問號後滑鼠會多一個問號,再點子視窗會對子視窗送WM_HELP訊息		,還沒試
//WS_EX_DLGMODALFRAME	//配上WS_POPUP會多一層框,其他不知道														,還沒試
//WS_EX_ACCEPTFILES		//可接受拖拉檔案到視窗																	,還沒試
//
//WS_EX_NOPARENTNOTIFY	//子視窗創建或銷毀時不傳送給父視窗WM_PARENTNOTIFY訊息									,還沒試
//WS_EX_MDICHILD		//創建一個MDI子視窗,看不懂																,還沒試
//WS_EX_WINDOWEDGE		//指定窗口外框有凸起的邊緣,似乎預設就是凸起,看不出來									,還沒試
//WS_EX_CLIENTEDGE		//指定窗口外框有凹陷的邊緣,看起來跟預設不同												,還沒試
//WS_EX_RTLREADING		//顯示文件資料時,使用由右到左閱讀方式													,還沒試
//WS_EX_LTRREADING		//顯示文件資料時,使用由左到右閱讀方式(此為預設值)										,還沒試
//WS_EX_CONTROLPARENT	//允許使用TAB鍵瀏覽各子視窗																,還沒試
//WS_EX_STATICEDGE		//一個不可輸入的樣式(應該是使用在控件)													,還沒試
//
//WS_EX_APPWINDOW
//#define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
//#define WS_EX_PALETTEWINDOW     (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
//#define WS_EX_LAYERED           0x00080000
//#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
//#define WS_EX_LAYOUTRTL         0x00400000L // Right to left mirroring
//#define WS_EX_COMPOSITED        0x02000000L
//#define WS_EX_NOACTIVATE        0x08000000L
HWND hWnd;
CursorManger::CursorManger()
{
	POINT mpnt;
	GetCursorPos(&mpnt);
	ScreenToClient(hWnd, &mpnt);

	CursorX = mpnt.x;
	CursorY = mpnt.y;
}
void CursorManger::Work()
{
	POINT mpnt;
	GetCursorPos(&mpnt);
	ScreenToClient(hWnd, &mpnt);

	if (CursorX != mpnt.x)
		CursorX_Chang = true;
	else
		CursorX_Chang = false;

	if (CursorY != mpnt.y)
		CursorY_Chang = true;
	else
		CursorY_Chang = false;

	CursorX_Shift = CursorX - mpnt.x;
	CursorY_Shift = CursorY - mpnt.y;

	CursorX = mpnt.x;
	CursorY = mpnt.y;
}
long CursorManger::GetCursorX() { return CursorX; }
long CursorManger::GetCursorY() { return CursorY; }
long CursorManger::GetCursorX_Shift() { return CursorX_Shift; }
long CursorManger::GetCursorY_Shift() { return CursorY_Shift; }
bool CursorManger::GetCursorX_Chang() { return CursorX_Chang; }
bool CursorManger::GetCursorY_Chang() { return CursorY_Chang; }