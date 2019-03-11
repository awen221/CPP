#ifndef _GDI_PLUS_DRAW_H_
#define _GDI_PLUS_DRAW_H_

#include<GdiPlus.h>
#pragma comment( lib, "gdiplus.lib" )
using namespace Gdiplus;


class GdiPlusDraw
{
private:
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Graphics* GdiPlusGraphics;

public:
	GdiPlusDraw(HDC dc)
	{
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		GdiPlusGraphics = new Graphics(dc);
	}
	~GdiPlusDraw()
	{
		GdiplusShutdown(gdiplusToken);
	}

protected:
};


//#include"BaseWindow.h"
//#include"Win32String.h"
//#include"InputManager.h"

//#include<stdio.h>
#include<vector>



class UV
{
private:
	
public:
	int X,Y,Width,Height;

	UV(int x = 0,int y = 0,int width = 0,int height = 0):X(x),Y(y),Width(width),Height(height){}
	void SetX(int x)
	{
		X = x ;
	}
	void SetY(int y)
	{
		Y = y ;
	}
	void SetWidth(int width)
	{
		Width = width ;
	}
	void SetHeight(int height)
	{
		Height = height ;
	}
	void SetPos(int x,int y)
	{
		SetX(x) ;
		SetY(y) ;
	}
	void SetSize(int width,int height)
	{
		SetWidth(width) ;
		SetHeight(height) ;
	}
	void Set(int x,int y,int width,int height)
	{
		SetPos(x,y);
		SetSize(width,height) ;
	}
};
typedef std::vector<UV> V_UV;
class ImageObj
{
private:
protected:
public:
	Bitmap* pBitmap;
	Bitmap* pOutBitmap;

	int Width,Height ;

	void loadIamge(const TCHAR* ImageFileName)
	{
		if (pBitmap != NULL)
			delete pBitmap ;
		#ifdef _UNICODE
			pBitmap = new Bitmap(ImageFileName);
		#else
			
			enum{MAX_STRING_LEN=1024};
			int w_CharSize = MultiByteToWideChar (CP_ACP, 0, ImageFileName, -1, NULL, 0);
			WCHAR Buf[MAX_STRING_LEN+1];

			MultiByteToWideChar (CP_ACP, 0, ImageFileName, w_CharSize, Buf, w_CharSize);  
			Buf[w_CharSize-1]='\0';
			pBitmap = new Bitmap(Buf);
			
		
//			pBitmap = new Bitmap(ToWChar(ImageFileName));

		#endif
		if (pBitmap!= NULL)
		{
			Width = pBitmap->GetWidth() ;
			Height = pBitmap->GetHeight() ;
		}
		SetUV(0,0,Width,Height);
	}
	void SetUV(int x,int y,int width,int height)
	{
		if (pBitmap!= NULL)
			pOutBitmap = pBitmap->Clone(x,y,width,height,PixelFormatDontCare);
	}
	void Draw(Graphics* graphics,int PosX,int PosY)
	{
		SetUV(0,0,Width,Height);
		if (pOutBitmap!= NULL)
			graphics->DrawImage(pOutBitmap, PosX, PosY);

		if(pOutBitmap != NULL)
			delete pOutBitmap ;
	}
};

//
//#include"GdiPlusDrawEngine_GUI\GUI.h"
//#include"GdiPlusDrawEngine_OBJ\OBJ.h"


#endif