#ifndef _GDI_PLUS_WINDOW_H_
#define _GDI_PLUS_WINDOW_H_


#include"BaseWindow.h"


class GdiPlusWindow:private BaseWindow
{
public:
	GdiPlusWindow(const TCHAR* title,int w,int h):BaseWindow(title,w,h){}
	void Init(){}
	void Work(){}
	void Draw(HDC hdc){}
};





#endif