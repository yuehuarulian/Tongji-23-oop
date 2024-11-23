#pragma once
#define PI 3.1415926
//画图窗口大小
#define WINDOW_X 800
#define WINDOW_Y 600
//圆心坐标
#define CENTER_X WINDOW_X / 2
#define CENTER_Y WINDOW_Y / 2
//两个圆的半径
#define RADIUS_1 int(min(WINDOW_X,WINDOW_Y)/2*0.9)
#define RADIUS_2 int(min(WINDOW_X,WINDOW_Y)/2*0.55)
// 抗锯齿
#define SDF_WIDTH_CIRCLE 30//抗锯齿处理像素宽度 circle
#define SDF_WIDTH_LINE 10//抗锯齿处理像素宽度 line
//各种color
#define MY_PURPLE RGB(150,142,185)
#define MY_WHITE RGB(248, 241, 248)
#define MY_LIGHT_RED RGB(255, 186, 201)
#define MY_PINK RGB(249,218,228)
#define MY_WHITE_2 RGB(249, 236, 243)
#define MY_BLUE RGB(239,239,246)
//初始界面
void init();
//画抗锯齿 / 渐变色 / 透明圆
void SDF_circle(int center_x, int center_y, COLORREF color_1, COLORREF color_2, int  radius_1, int radius_2, int SDF_degree = 2);

//line抗锯齿
void SDF_line(int x1, int y1, int x2, int y2, COLORREF color, int thickness, int SDF_degree = 2);