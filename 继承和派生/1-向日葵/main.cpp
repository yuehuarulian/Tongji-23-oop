#include <iostream>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_SUNLIGHT 500
using namespace std;

const int sunflower_cost = 50;
const int sunflower_create = 25;
time_t current = 0;  // ģ���¼ʱ�䣬��λs

class PlantBase {
private:
	int hp;				// ֲ�������ֵ

protected:
	time_t plant_time;	// ֲ�ﱻ���µ�ʱ��
	time_t interval;	// ֲ�﹥����������ʱ����

public:
	PlantBase(int hp, time_t interval);
	bool hurt(int damage);
};

/***********���������PlantBase��ʵ��***********/
PlantBase::PlantBase(int hp, time_t interval):hp(hp),interval(interval)
{
	plant_time = current;
}
/*�ӵ� $n$ �뿪ʼ����ʬ���������
ÿ�������Ҳ��ֲ����ܵ� $10*(t-n)$ ���˺������� $t$ ��ʾ��ǰʱ�䣩��
������տ�������ֵС�ڵ��� $0$�����տ������� ��λ�ñ�Ϊ��λ�á���ֵ $n$ ���û�����õ�*/
bool PlantBase::hurt(int damage)//true ���ţ�false����
{
	hp -= damage;
	return hp > 0;
}
/********************************************/


/********���������SunFlower��������ʵ��*********/
/*���տ�����ֵ hp=60����Ҫ���� cost=50 ���⣬ÿ interval=5s ���� create=25 �����⡣�����������������*/
class SunFlower :public PlantBase {
public:
	SunFlower() :PlantBase(60, 5), cost(sunflower_cost), create(sunflower_create)
	{

	}
	time_t get_interval()
	{
		return interval;
	}
	time_t get_plant_time()
	{
		return plant_time;
	}
	const int get_create()
	{
		return create;
	}
	const int get_cost()
	{
		return cost;
	}
private:
	const int cost;
	const int create;
};
/********************************************/

int main()
{
	/* �������� */
	SunFlower* lawn[LAWN_LENGTH] = {};
	int plant_num = 0; // ��¼ֲ������

	// ��������
	int sunlight;
	time_t n;
	cin >> sunlight >> n;

	while (true) {
		// 1. ������ÿ3/6/9/...s����һ��25������
		if (current % SUNLIGHT_TIME == 0 && current > 0) {
			sunlight += 25;
		}

		/* 2. ֲ������� */
		for (int i = 0; i < plant_num; i++) {
			if ((current - lawn[i]->get_plant_time()) % (lawn[i]->get_interval()) == 0 && current > 0) {
				sunlight += lawn[i]->get_create();
			}
		}

		/* 3. ��ң���ֲ�һ��ֻ�ܷ�һ�꣩*/
		if (plant_num < LAWN_LENGTH && sunlight >= sunflower_cost) {
			SunFlower* sunflower = new(nothrow) SunFlower;
			if (sunflower == NULL){
				cout << "�ڴ�����ʧ��" << endl;
				return -1;
			}
			lawn[plant_num++] = sunflower;
			sunlight -= sunflower->get_cost();
		}

		/* 4. ��ʬ���ӵ�n�뿪ʼ��ÿһ�����Ҳ�����տ����յ�10*(current-n)���˺� */
		if (int(current) > n && plant_num && !lawn[plant_num - 1]->hurt(10 * int(current - n))) {//����
			delete lawn[--plant_num];
			lawn[plant_num] = NULL;
		}

		cout << "ʱ������" << current << " ��������" << sunlight << " ֲ������" << plant_num << endl;

		// 5. ��Ϸʤ��/ʧ���ж�
		if (sunlight >= TARGET_SUNLIGHT) {
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

	// �ڴ����
	for (int i = 0; i < LAWN_LENGTH; ++i) {
		if (lawn[i])
			delete lawn[i];
	}

	return 0;
}