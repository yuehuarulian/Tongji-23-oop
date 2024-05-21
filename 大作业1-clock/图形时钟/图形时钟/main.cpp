#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  
#include <time.h>  
#include <stdio.h>
#include "clock.h"
using namespace std;
//���ָ��Ľṹ��
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
�������ܣ���ʼ���ṹ�壬�ǶȺ�ʱ��
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
�������ܣ���ÿһ��ָ��
�βΣ�double len��ָ�볤��
      double angle��ָ��Ƕ�
����ֵ����
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
�������ܣ�����draw_hms������ָ��
�βΣ���
����ֵ����
********************************/
void hand::draw()
{
	draw_hms(RADIUS_1 * 1.00, second_hand_angle);//����
	draw_hms(RADIUS_1 * 0.75, minite_hand_angle);//����
	draw_hms(RADIUS_1 * 0.40, hour_hand_angle);//ʱ��
}
/********************************
�������ܣ��ж��Ƿ���Ҫ������Ⱦ
�βΣ�struct tm t�����ڵ�ʱ��
      struct tm t_copy����һ�ε�ʱ��
����ֵ��bool���� 1������Ҫ��Ⱦ
                 0����Ҫ������Ⱦ
********************************/
bool cmp(struct tm t, struct tm t_copy)
{
	return t.tm_sec == t_copy.tm_sec;
}
int main()
{
	// ��ȡ����ʱ��
	struct tm t,t_copy;
	time_t now;
	time(&now);
	localtime_s(&t, &now);

	// ��ʼ����ͼ����
	initgraph(WINDOW_X, WINDOW_Y);
	IMAGE* background = new IMAGE(WINDOW_X, WINDOW_Y);//����imageָ�����
	loadimage(background, L"./bk.jpg", WINDOW_X, WINDOW_Y);
	SetWorkingImage(background);
	putimage(0, 0, background);
	// �Զ���ͼ�γ�ʼ�����������ڻ���ʱ�ӽ���
	init();
	// �޼��̲���ʱ����ѭ��
    while (!_kbhit()) {	
		t_copy = t;
		time(&now);
		localtime_s(&t, &now);
		if (cmp(t, t_copy))
			continue;

		//������Ⱦ������Ϊparticle
		IMAGE* particle = new IMAGE(WINDOW_X, WINDOW_Y);//��particle_buffer���д���
		SetWorkingImage(particle);
		putimage(0, 0, background);
		hand h(t.tm_hour, t.tm_min, t.tm_sec);
		h.draw();
		//��ͼƬparticle��Ⱦ����Ļ
		SetWorkingImage(NULL);
		putimage(0, 0, particle);
    }
    _getch();		// �������׼���˳�ʱ�ӳ���
    closegraph();		// �˳�ͼ�ν���
    return 0;
}



