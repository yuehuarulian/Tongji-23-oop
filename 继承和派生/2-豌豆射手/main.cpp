#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 500
using namespace std;

//const int sunflower_cost = 50;
//const int sunflower_create = 25;
/*�㶹��������ֵ 60����Ҫ���� 100 �����⣬ÿ 2s ����һ�ι�������� 10 ���˺���*/
const int peashooter_life = 60;
const int peashooter_cost = 100;
const int peashooter_hurt = 10;
const int peashooter_interval = 2;
//const char* NUM[9] = { char* ("һ"),char* ("��"),const char* ("��"),const char* ("��"),const char* ("��") ,const char* ("��") ,const char* ("��"),const char* ("��"),const char* ("��") };
time_t current = 0;  // ģ���¼ʱ�䣬��λs

/*************�������������������**************/
class PlantBase {
private:
	int hp;			// ֲ�������ֵ
	char* name;		// ֲ������֣����Ȳ�����20��

protected:
	int cost;		// ��ֲ���ѵ�����
	time_t plant_time;	// ֲ�ﱻ���µ�ʱ��

public:
	PlantBase(int hp, int cost);
	~PlantBase();
	bool hurt(int damage);
	char* get_name();
};
/********************************************/


/*************��������������ʵ��**************/
PlantBase::PlantBase(int hp, int cost) :hp(hp), cost(cost)
{
	plant_time = current;
	name = new char[50];//��Ϊ��֤������
	cin >> name;
}
PlantBase::~PlantBase()
{
	delete[] name;
}
bool PlantBase::hurt(int damage)//true ���ţ�false����
{
	hp -= damage;
	return hp > 0;
}
char* PlantBase::get_name()
{
	return name;
}
/********************************************/


/**********����������������������ʵ��***********/
class PeaShooter :public PlantBase {
public:
	PeaShooter() :PlantBase(peashooter_life, peashooter_cost), hurtpoint(peashooter_hurt), interval(peashooter_interval) {}
	time_t get_interval()
	{
		return interval;
	}
	time_t get_plant_time()
	{
		return plant_time;
	}
	const int get_hurtpoint()
	{
		return hurtpoint;
	}
	const int get_cost()
	{
		return cost;
	}
private:
	const int hurtpoint;
	const int interval;
};
/******************************************/


int main()
{
	/* �������� */
	PeaShooter* lawn[LAWN_LENGTH] = {};
	int plant_num = 0; // ��¼ֲ������
	vector<time_t>plant_time;

	// ��������
	int sunlight, damage = 0;
	time_t n;
	cin >> sunlight >> n;

	while (true) {
		// 1. ������ÿ3/6/9/...s����һ��25������
		if (current % SUNLIGHT_TIME == 0 && current > 0) {
			sunlight += 25;
		}

		/* 2. ֲ��������� */
		for (int i = 0; i < plant_num; i++) {
			if ((current - lawn[i]->get_plant_time()) % (lawn[i]->get_interval()) == 0 && current > 0) {
				damage += lawn[i]->get_hurtpoint();
			}
		}

		/* 3. ��ң���ֲ�һ��ֻ�ܷ�һ�꣩*/
		if (plant_num < LAWN_LENGTH && sunlight >= peashooter_cost) {
			PeaShooter* pea = new(nothrow) PeaShooter;
			if (pea == NULL) {
				cout << "�ڴ�����ʧ��" << endl;
				return -1;
			}
			lawn[plant_num++] = pea;
			sunlight -= pea->get_cost();
			plant_time.push_back(current);
		}

		/* 4. ��ʬ���ӵ�n�뿪ʼ��ÿһ�����Ҳ��ֲ����յ�10*(current-n)���˺� */
		if (int(current) > n && !lawn[plant_num - 1]->hurt(10 * int(current - n))) {//����
			delete lawn[--plant_num];
			lawn[plant_num] = NULL;
		}

		//cout << "ʱ������" << current << " ��������" << sunlight << " ֲ������" << plant_num << endl;
		// 5. ��Ϸʤ��/ʧ���ж�
		if (damage >= TARGET_DAMAGE) {
			cout << "��Ϸʤ��" << endl;
			break;
		}
		else if (current >= n && plant_num == 0) {  // ��ǰ�ж�ʧ��
			cout << "��Ϸʧ��" << endl;
			break;
		}
		else if (current >= 100) {  // �����100���ȥ��δ�����㹻���⣬���и�
			cout << "��Ϸʧ��" << endl;
			break;
		}
		current++;
	}

	cout << "ʱ������" << current << " ��������" << sunlight << " ֲ������" << plant_num << endl;

	/* ����������ڴ���� */
	cout << "ÿһ��ֲ�����µ�ʱ�̣�" << endl;
	for (auto i : plant_time) {
		cout << i << ' ';
	}
	cout << endl;
	cout << "�Ҵ�ֲ������֣�" << endl;
	for (int i = 0; i < plant_num; ++i) {
		cout << lawn[i]->get_name() << endl;
	}
	for (int i = 0; i < LAWN_LENGTH; ++i) {
		if (lawn[i])
			delete lawn[i];
	}

	return 0;
}


/*
��Ϸʤ��

ʱ������16 ��������225 ֲ������9

ÿһ��ֲ�����µ�ʱ�̣�
0 1 2 3 4 5 6 7 8

�Ҵ�ֲ������֣�
��һ���㶹
�ڶ����㶹
�������㶹
�������㶹
�������㶹
�������㶹
�������㶹
�ڰ����㶹
�ھ����㶹
*/