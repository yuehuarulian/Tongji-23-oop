#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
#include <stdio.h>
#include "clock.h"
using namespace std;
/********************************
函数功能：文字输出抗锯齿以及设计格式
形参：int x：文字输出横坐标
      int y：文字输出纵坐标
	  TCHAR s[]：字符串
	  COLORREF color：颜色
	  int Height：文字高度，宽度自适应
返回值：无
********************************/
void text(int x,int y, TCHAR s[],COLORREF color, int Height)
{
	// 设置输出效果为抗锯齿
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = Height;						// 设置字体高度
	setbkmode(TRANSPARENT);//背景透明字体
	settextcolor(color);
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	outtextxy(x, y, s);
}
/********************************
函数功能：初始化界面
形参：无
返回值：无
********************************/
void init()
{
	SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, NULL, RADIUS_1, RADIUS_1, 60);//透明
	//SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, NULL, RADIUS_1 + 5, RADIUS_1 + 5, 10);
	SDF_circle(CENTER_X, CENTER_Y, MY_BLUE, NULL, RADIUS_2, RADIUS_2, 150);
	SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, MY_BLUE, RADIUS_1, RADIUS_2);//画圆
	SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, NULL, RADIUS_1, RADIUS_1);//抗锯齿
	SDF_circle(CENTER_X, CENTER_Y, MY_BLUE, NULL, RADIUS_2, RADIUS_2);

	//画线和数字
	for (int i = 1; i <= 60; i++) {
		double sita = 2 * PI / 60 * i - PI / 2;
		int x1 = int(CENTER_X + RADIUS_1 * 0.95 * cos(sita));//线的起点
		int y1 = int(CENTER_Y + RADIUS_1 * 0.95 * sin(sita));
		int x2;//线的终点
		int y2;
		int x3;//外圈数字的位置
		int y3;
		int x4;//内圈数字位置
		int y4;
		if (i % 5) {
			x2 = int(CENTER_X + RADIUS_1 * 0.9 * cos(sita));
			y2 = int(CENTER_Y + RADIUS_1 * 0.9 * sin(sita));
		}
		else {
			x2 = int(CENTER_X + RADIUS_1 * 0.85 * cos(sita));
			y2 = int(CENTER_Y + RADIUS_1 * 0.85 * sin(sita));
			x3 = int(CENTER_X + RADIUS_1 * 0.75 * cos(sita) - 13);
			y3 = int(CENTER_Y + RADIUS_1 * 0.75 * sin(sita) - 13);
			x4 = int(CENTER_X + RADIUS_2 * 0.75 * cos(sita) - 13);
			y4 = int(CENTER_Y + RADIUS_2 * 0.75 * sin(sita) - 17);
			TCHAR s[5];
			_stprintf(s, _T("%d"), i);
			text(x3, y3, s, WHITE, 35);//外圈数字
			_stprintf(s, _T("%d"), i/5);
			text(x4, y4, s, MY_PURPLE, 40);//内圈数字
		}
		SDF_line(x1, y1, x2, y2, WHITE, 4, 10);
		SDF_line(x1, y1, x2, y2, WHITE, 4);
	}
}

