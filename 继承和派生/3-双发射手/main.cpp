#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 3000
using namespace std;

//const int sunflower_cost = 50;
//const int sunflower_create = 25;
//const int peashooter_life = 60;
//const int peashooter_cost = 100;
//const int peashooter_hurt = 10;
//const int peashooter_interval = 2;

/*˫���㶹����ֵ 60����Ҫ���� 150 ���⣬ÿ 2s ����һ�ι�����20 ���˺�����
��������������� Repeater���������ԺͲ�����װΪ���ݳ�Ա�ͳ�Ա������*/
const int repeater_life = 60;
const int repeater_cost = 150;
const int repeater_interval = 2;
const int repeater_hurt = 20;
/*��ǹ�㶹����ֵ 60����Ҫ���� 150 ���⣬ÿ 2s ����һ�ι�����40 ���˺�����
��������������� GatlingPea���������ԺͲ�����װΪ���ݳ�Ա�ͳ�Ա������
��ע�⣺��ǹ�㶹ֻ������˫���㶹�ϣ����һᱣ��ԭ��˫���㶹�������͵�ǰ����ֵ��*/
const int gatlingpea_life = 60;
const int gatlingpea_cost = 150;
const int gatlingpea_interval = 2;
const int gatlingpea_hurt = 40;

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
	PlantBase(PlantBase& base);	// ���ƹ��캯��
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
PlantBase::PlantBase(PlantBase& base)
{
	//plant_time = base.plant_time;
	hp = base.hp;
	//cost = base.cost;
	name = new char[50];//��Ϊ��֤������
	strcpy(name, base.name);
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
class Repeater :public PlantBase {
public:
	Repeater() :PlantBase(repeater_life, repeater_cost), hurtpoint(repeater_hurt), interval(repeater_interval) {}
	Repeater(Repeater& repeater) :PlantBase(repeater), hurtpoint(repeater_hurt), interval(repeater_interval)
	{
		plant_time = current;
		cost = gatlingpea_cost;
	}
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
protected:
	int hurtpoint;
	const int interval;
};

class GatlingPea :public Repeater {
public:
	GatlingPea(Repeater& repeater) :Repeater(repeater)
	{
		hurtpoint = gatlingpea_hurt;
	}
};

/******************************************/


int main()
{
	/* �������� */
	Repeater* lawn1[LAWN_LENGTH] = {};//��¼˫���㶹
	GatlingPea* lawn2[LAWN_LENGTH] = {};//��¼��ǹ�㶹
	int plant_num = 0; // ��¼ֲ������
	int repeater_num = 0; 
	int gatlingpea_num = 0;
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
		int i = 0;
		for (; i < gatlingpea_num; i++) {
			if (lawn2[i] && (current - lawn2[i]->get_plant_time()) % (lawn2[i]->get_interval()) == 0 && current > 0) {
				damage += lawn2[i]->get_hurtpoint();
			}
		}
		for (; i < repeater_num; i++) {
			if (lawn1[i] && (current - lawn1[i]->get_plant_time()) % (lawn1[i]->get_interval()) == 0 && current > 0) {
				damage += lawn1[i]->get_hurtpoint();
			}
		}

		/* 3. ��ң���ֲ�һ��ֻ�ܷ�һ�꣩*/
		if (repeater_num < LAWN_LENGTH && sunlight >= repeater_cost) {
			Repeater* rep = new(nothrow) Repeater;
			if (rep == NULL) {
				cout << "�ڴ�����ʧ��" << endl;
				return -1;
			}
			lawn1[repeater_num++] = rep;
			sunlight -= rep->get_cost();
			plant_time.push_back(current);
		}
		else if (gatlingpea_num < LAWN_LENGTH && sunlight >= gatlingpea_cost) {
			GatlingPea* gat = new(nothrow) GatlingPea(*lawn1[gatlingpea_num]);
			if (gat == NULL) {
				cout << "�ڴ�����ʧ��" << endl;
				return -1;
			}
			delete lawn1[gatlingpea_num];
			lawn1[gatlingpea_num] = NULL;
			lawn2[gatlingpea_num++] = gat;

			sunlight -= gat->get_cost();
			plant_time.push_back(current);
		}
		/* 4. ��ʬ���ӵ�n�뿪ʼ��ÿһ�����Ҳ��ֲ����յ�10*(current-n)���˺� */
		if (int(current) >= n && repeater_num) {
			if (repeater_num > gatlingpea_num && !lawn1[repeater_num - 1]->hurt(10 * int(current - n))) {//����
				delete lawn1[--repeater_num];
				lawn1[repeater_num] = NULL;
			}
			else if (repeater_num == gatlingpea_num && !lawn2[gatlingpea_num - 1]->hurt(10 * int(current - n))) {//����
				delete lawn2[--gatlingpea_num];
				--repeater_num;
				lawn2[gatlingpea_num] = NULL;
			}
		}

		plant_num = repeater_num;
		//cout << "ʱ������" << current << " ��������" << sunlight << " ֲ������" << plant_num << "�˺�  " << damage << endl;
		// 5. ��Ϸʤ��/ʧ���ж�
		if (damage >= TARGET_DAMAGE) {
			cout << "��Ϸʤ��" << endl;
			break;
		}
		else if (current >= n && plant_num == 0) {  // ��ǰ�ж�ʧ��
			cout << "��Ϸʧ��" << endl;
			break;
		}
		else if (current >= 100) {  // �����100���ȥ��δ�����㹻�����и�
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
	int i = 0;
	for (; i < gatlingpea_num; ++i) {
		cout << "Gatling: " << lawn2[i]->get_name() << endl;
	}
	for (; i < repeater_num; ++i) {
		cout << "Repeater: " << lawn1[i]->get_name() << endl;
	}


	//�ڴ����
	for (int i = 0; i < LAWN_LENGTH; ++i) {
		if (lawn1[i])
			delete lawn1[i];
		if (lawn2[i])
			delete lawn2[i];
	}

	return 0;
}