#ifndef _GUI_H_
#define _GUI_H_

#include<vector>
#include<tchar.h>

class baseColor:public Color
{
private:
protected:
public:
	void SetRGB(IN BYTE r,IN BYTE g,IN BYTE b)
	{
		Argb = MakeARGB(255, r, g, b);
	}
};
class baseRect:public Rect
{
private:
protected:
public:
	void SetSize(int width,int height)
	{
		Width = width ;
		Height = height ;
	}
};
/*
enum FontStyle
{
    FontStyleRegular    = 0,
    FontStyleBold       = 1,
    FontStyleItalic     = 2,
    FontStyleBoldItalic = 3,
    FontStyleUnderline  = 4,
    FontStyleStrikeout  = 8
};
*/
class baseUI:public baseRect
{
private:
	baseUI* parent;
	baseColor bgColor;
	baseColor frameColor;
	int frameWidth;
	baseColor textColor;
	baseColor textBgColor;

	Win32String fontName;
	int fontStyle;
	int fontSize;
protected:
public:
	int OffsetX;
	int OffsetY;

	baseUI()
	{
		bgColor.SetRGB(0,0,0);
		frameColor.SetRGB(255,255,255);
		frameWidth = 1 ;
		Width = 100 ;
		Height = 100 ;

		textColor.SetRGB(255,255,0);
		fontName = _T("·s²Ó©úÅé");
		fontStyle = FontStyleRegular ;
		fontSize = 12 ;

	}
	void Work()
	{
	}
	void Draw(Graphics* graphics)
	{
		SolidBrush mySolidBrush(bgColor);
		graphics->FillRectangle(&mySolidBrush, X,Y,Width,Height) ;		
		
		Pen pen(frameColor, REAL(frameWidth));
		pen.SetAlignment(PenAlignmentInset);
		graphics->DrawRectangle(&pen,X,Y,Width,Height) ;

		SolidBrush  brush(textColor);
		FontFamily  fontFamily(fontName.GetWideChar());
		Font        font(&fontFamily, REAL(fontSize), FontStyleRegular, UnitPixel);
		PointF      pointF(X, Y);

		graphics->DrawString(L"Hello World!", -1, &font, pointF, &brush);

	}

};

typedef std::vector<baseUI> V_UI;
class baseWin
{
};

class GUI_Managers
{
private:
	V_UI v_UI;
protected:
public:

	void DrawUI()
	{





	}
};

#endif