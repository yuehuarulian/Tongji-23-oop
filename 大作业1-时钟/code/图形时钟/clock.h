#pragma once
#define PI 3.1415926
//��ͼ���ڴ�С
#define WINDOW_X 800
#define WINDOW_Y 600
//Բ������
#define CENTER_X WINDOW_X / 2
#define CENTER_Y WINDOW_Y / 2
//����Բ�İ뾶
#define RADIUS_1 int(min(WINDOW_X,WINDOW_Y)/2*0.9)
#define RADIUS_2 int(min(WINDOW_X,WINDOW_Y)/2*0.55)
// �����
#define SDF_WIDTH_CIRCLE 30//����ݴ������ؿ�� circle
#define SDF_WIDTH_LINE 10//����ݴ������ؿ�� line
//����color
#define MY_PURPLE RGB(150,142,185)
#define MY_WHITE RGB(248, 241, 248)
#define MY_LIGHT_RED RGB(255, 186, 201)
#define MY_PINK RGB(249,218,228)
#define MY_WHITE_2 RGB(249, 236, 243)
#define MY_BLUE RGB(239,239,246)
//��ʼ����
void init();
//������� / ����ɫ / ͸��Բ
void SDF_circle(int center_x, int center_y, COLORREF color_1, COLORREF color_2, int  radius_1, int radius_2, int SDF_degree = 2);

//line�����
void SDF_line(int x1, int y1, int x2, int y2, COLORREF color, int thickness, int SDF_degree = 2);