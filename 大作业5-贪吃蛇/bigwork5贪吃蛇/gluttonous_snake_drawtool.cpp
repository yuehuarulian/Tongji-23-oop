#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
#include <stdio.h>
#include "consta.h"
#include"gluttonous_snake.h"
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;
//SDF+alpha blending
/********************************
函数功能：混合颜色
形参：COLORREF bg：背景色
	  COLORREF color：前景色
	  double alpha：比例
返回值：无
********************************/
COLORREF mix_color(COLORREF bg, COLORREF color, double alpha)//背景色 前景色 alpha=0.5-d 返回RGB( , , )
{
	COLORREF result;
	result = RGB(GetRValue(bg) * (1 - alpha) + GetRValue(color) * alpha, GetGValue(bg) * (1 - alpha) + GetGValue(color) * alpha, GetBValue(bg) * (1 - alpha) + GetBValue(color) * alpha);
	return result;
}

/********************************
函数功能：画抗锯齿/渐变色/透明圆
形参：int center_x：圆心横坐标
	  int center_y；圆心纵坐标
	  COLORREF color_1：颜色1，大于color_2
	  COLORREF color_2：颜色2，为NULL时表示画的是纯色圆solidcircle
	  int  radius_1：半径1
	  int  radius_2：半径2，半径二是不画的，两个半径相等表示画的是circle
	  int SDF_degree：抗锯齿的程度，默认值是2，如果设置10及以上可以达到半透明的效果
返回值：无
********************************/
void SDF_circle(int center_x, int center_y, COLORREF color_1, COLORREF color_2, int  radius_1, int radius_2, int SDF_degree)
{
	for (int x = center_x - radius_1 - SDF_WIDTH_CIRCLE; x < center_x + radius_1 + SDF_WIDTH_CIRCLE; x++) {
		for (int y = center_y - radius_1 - SDF_WIDTH_CIRCLE; y < center_y + radius_1 + SDF_WIDTH_CIRCLE; y++) {
			double d;
			d = sqrt((pow(x - center_x, 2) + pow(y - center_y, 2))) - radius_1;//点到圆边的距离
			double alpha = 0.5 - d / SDF_degree;
			if (alpha >= 0 && alpha <= 1) {
				COLORREF bg = getpixel(x, y);
				COLORREF result = mix_color(bg, color_1, alpha);
				putpixel(x, y, result);
			}
		}
	}
	if (radius_1 == radius_2)//只进行抗锯齿
		;
	else if (color_2 == NULL || radius_2 == 0) { //没有渐变
		setfillcolor(color_1);
		setlinecolor(color_1);
		solidcircle(center_x, center_y, radius_1);
	}
	else {  //渐变色
		for (int i = radius_1 - 1; i > radius_2; i--) {
			COLORREF co;
			co = RGB(
				int(double(radius_1 - i) / (radius_1 - radius_2) * GetRValue(color_2) + double(i - radius_2) / (radius_1 - radius_2) * GetRValue(color_1)),
				int(double(radius_1 - i) / (radius_1 - radius_2) * GetGValue(color_2) + double(i - radius_2) / (radius_1 - radius_2) * GetGValue(color_1)),
				int(double(radius_1 - i) / (radius_1 - radius_2) * GetBValue(color_2) + double(i - radius_2) / (radius_1 - radius_2) * GetBValue(color_1))
			);
			setlinecolor(co);
			setlinestyle(PS_SOLID, 2);
			circle(center_x, center_y, i);
		}
	}
}

/********************************
函数功能：画抗锯齿直线
形参：int x1：起点横坐标
	  int y1：起点纵坐标
	  int x2：终点横坐标
	  int y2：终点纵坐标
	  COLORREF color：颜色
	  int thickness：线宽
返回值：无
********************************/
void SDF_line(int x1, int y1, int x2, int y2, COLORREF color, int thickness, int SDF_degree)
{
	for (int x = min(x1, x2) - SDF_WIDTH_LINE; x < max(x1, x2) + SDF_WIDTH_LINE; x++) {
		for (int y = min(y1, y2) - SDF_WIDTH_LINE; y < max(y1, y2) + SDF_WIDTH_LINE; y++) {
			double d;
			bool b1 = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) >= 0;
			bool b2 = ((x - x2) * (x1 - x2) + (y - y2) * (y1 - y2)) >= 0;
			if (b1 && b2)
				d = fabs(((x2 - x1) * (y - y1) - (y2 - y1) * (x - x1)) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))) - thickness / 2;
			else if (!b1)
				d = sqrt(pow(x - x1, 2) + pow(y - y1, 2)) - thickness / 2;
			else
				d = sqrt(pow(x - x2, 2) + pow(y - y2, 2)) - thickness / 2;
			double alpha = 0.5 - d / SDF_degree;
			if (alpha >= 0 && alpha <= 1) {
				COLORREF bg = getpixel(x, y);
				COLORREF result = mix_color(bg, color, alpha);
				putpixel(x, y, result);
			}
		}
	}
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, thickness);
	setlinecolor(color);
	line(x1, y1, x2, y2);
}

//x y button的位置
void button(int x, int y, const TCHAR* text)
{
	setbkmode(TRANSPARENT);
	setfillcolor(MY_PURPLE);
	fillroundrect(x, y, x + BUTTON_W, y + BUTTON_H, 10, 10);
	settextstyle(&Font);
	settextcolor(WHITE);

	int tx = x + (BUTTON_W - textwidth(text)) / 2;
	int ty = y + (BUTTON_H - textheight(text)) / 2;

	outtextxy(tx, ty, text);
}

//透明贴图
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}