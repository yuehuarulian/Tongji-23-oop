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
�������ܣ��������������Լ���Ƹ�ʽ
�βΣ�int x���������������
      int y���������������
	  TCHAR s[]���ַ���
	  COLORREF color����ɫ
	  int Height�����ָ߶ȣ��������Ӧ
����ֵ����
********************************/
void text(int x,int y, TCHAR s[],COLORREF color, int Height)
{
	// �������Ч��Ϊ�����
	LOGFONT f;
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = Height;						// ��������߶�
	setbkmode(TRANSPARENT);//����͸������
	settextcolor(color);
	_tcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	outtextxy(x, y, s);
}
/********************************
�������ܣ���ʼ������
�βΣ���
����ֵ����
********************************/
void init()
{
	SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, NULL, RADIUS_1, RADIUS_1, 60);//͸��
	//SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, NULL, RADIUS_1 + 5, RADIUS_1 + 5, 10);
	SDF_circle(CENTER_X, CENTER_Y, MY_BLUE, NULL, RADIUS_2, RADIUS_2, 150);
	SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, MY_BLUE, RADIUS_1, RADIUS_2);//��Բ
	SDF_circle(CENTER_X, CENTER_Y, MY_PURPLE, NULL, RADIUS_1, RADIUS_1);//�����
	SDF_circle(CENTER_X, CENTER_Y, MY_BLUE, NULL, RADIUS_2, RADIUS_2);

	//���ߺ�����
	for (int i = 1; i <= 60; i++) {
		double sita = 2 * PI / 60 * i - PI / 2;
		int x1 = int(CENTER_X + RADIUS_1 * 0.95 * cos(sita));//�ߵ����
		int y1 = int(CENTER_Y + RADIUS_1 * 0.95 * sin(sita));
		int x2;//�ߵ��յ�
		int y2;
		int x3;//��Ȧ���ֵ�λ��
		int y3;
		int x4;//��Ȧ����λ��
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
			text(x3, y3, s, WHITE, 35);//��Ȧ����
			_stprintf(s, _T("%d"), i/5);
			text(x4, y4, s, MY_PURPLE, 40);//��Ȧ����
		}
		SDF_line(x1, y1, x2, y2, WHITE, 4, 10);
		SDF_line(x1, y1, x2, y2, WHITE, 4);
	}
}

