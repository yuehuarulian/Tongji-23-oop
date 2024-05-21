#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
#include <stdio.h>
#include "clock.h"
using namespace std;
//表的指针的结构体
class hand {
private:
	double hour_hand_angle;
	double minite_hand_angle;
	double second_hand_angle;
	int hour;
	int minite;
	int second;
	friend void SDF_circle(int center_x, int center_y, COLORREF color, int  radius);
	friend void SDF_line(int x1, int y1, int x2, int y2, COLORREF color, int thickness);
	void draw_hms(double len, double angle);
public:
	hand(int h, int m, int s);
	void draw();
};
/********************************
函数功能：初始化结构体，角度和时间
********************************/
hand::hand(int h, int m, int s)
{
	hour = h;
	hour_hand_angle = -PI / 2 + h * 2 * PI / 12 + m * 2 * PI / 12 / 60 + s * 2 * PI / 12 / 60 / 60;
	minite = m;
	minite_hand_angle = -PI / 2 + m * 2 * PI / 60 + s * 2 * PI / 60 / 60;
	second = s;
	second_hand_angle = -PI / 2 + s * 2 * PI / 60;
}
/********************************
函数功能：画每一根指针
形参：double len：指针长度
      double angle：指针角度
返回值：无
********************************/
void hand::draw_hms(double len, double angle)
{
	int x1 = int(CENTER_X + len * 0.85 * cos(angle));
	int y1 = int(CENTER_Y + len * 0.85 * sin(angle));
	int x2 = int(CENTER_X - len * 0.15 * cos(angle));
	int y2 = int(CENTER_Y - len * 0.15 * sin(angle));

	SDF_line(x1, y1, x2, y2, MY_PINK, 5);
	SDF_circle(x2, y2, MY_PINK, NULL, 5, NULL);
	SDF_circle(CENTER_X, CENTER_Y, MY_LIGHT_RED, NULL, 15, 0, 30);
	SDF_circle(CENTER_X, CENTER_Y, MY_WHITE_2, NULL, 5, 0, 20);
	SDF_circle(x1, y1, MY_LIGHT_RED, NULL, 10, 0, 20);
	SDF_circle(x1, y1, MY_WHITE_2, NULL, 4, 0, 10);
	
}
/********************************
函数功能：调用draw_hms画三根指针
形参：无
返回值：无
********************************/
void hand::draw()
{
	draw_hms(RADIUS_1 * 1.00, second_hand_angle);//秒针
	draw_hms(RADIUS_1 * 0.75, minite_hand_angle);//分针
	draw_hms(RADIUS_1 * 0.40, hour_hand_angle);//时针
}
/********************************
函数功能：判断是否需要重新渲染
形参：struct tm t：现在的时间
      struct tm t_copy：上一次的时间
返回值：bool类型 1：不需要渲染
                 0：需要重新渲染
********************************/
bool cmp(struct tm t, struct tm t_copy)
{
	return t.tm_sec == t_copy.tm_sec;
}
int main()
{
	// 获取当地时间
	struct tm t,t_copy;
	time_t now;
	time(&now);
	localtime_s(&t, &now);

	// 初始化绘图窗口
	initgraph(WINDOW_X, WINDOW_Y);
	IMAGE* background = new IMAGE(WINDOW_X, WINDOW_Y);//生成image指针对象
	loadimage(background, L"./bk.jpg", WINDOW_X, WINDOW_Y);
	SetWorkingImage(background);
	putimage(0, 0, background);
	// 自定义图形初始化函数，用于绘制时钟界面
	init();
	// 无键盘操作时进入循环
    while (!_kbhit()) {	
		t_copy = t;
		time(&now);
		localtime_s(&t, &now);
		if (cmp(t, t_copy))
			continue;

		//离屏渲染，储存为particle
		IMAGE* particle = new IMAGE(WINDOW_X, WINDOW_Y);//对particle_buffer进行处理
		SetWorkingImage(particle);
		putimage(0, 0, background);
		hand h(t.tm_hour, t.tm_min, t.tm_sec);
		h.draw();
		//将图片particle渲染至屏幕
		SetWorkingImage(NULL);
		putimage(0, 0, particle);
    }
    _getch();		// 按任意键准备退出时钟程序
    closegraph();		// 退出图形界面
    return 0;
}



