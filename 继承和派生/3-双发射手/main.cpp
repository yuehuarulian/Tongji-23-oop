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

/*双发豌豆生命值 60，需要消耗 150 阳光，每 2s 进行一次攻击（20 点伤害）。
请自行设计派生类 Repeater，将其属性和操作封装为数据成员和成员函数。*/
const int repeater_life = 60;
const int repeater_cost = 150;
const int repeater_interval = 2;
const int repeater_hurt = 20;
/*机枪豌豆生命值 60，需要消耗 150 阳光，每 2s 进行一次攻击（40 点伤害）。
请自行设计派生类 GatlingPea，将其属性和操作封装为数据成员和成员函数。
请注意：机枪豌豆只能种在双发豌豆上，并且会保留原本双发豌豆的姓名和当前生命值。*/
const int gatlingpea_life = 60;
const int gatlingpea_cost = 150;
const int gatlingpea_interval = 2;
const int gatlingpea_hurt = 40;

time_t current = 0;  // 模拟记录时间，单位s

/*************将基类的声明拷贝至此**************/
class PlantBase {
private:
	int hp;			// 植物的生命值
	char* name;		// 植物的名字（长度不超过20）

protected:
	int cost;		// 种植花费的阳光
	time_t plant_time;	// 植物被种下的时间

public:
	PlantBase(int hp, int cost);
	PlantBase(PlantBase& base);	// 复制构造函数
	~PlantBase();
	bool hurt(int damage);
	char* get_name();
};
/********************************************/


/*************在这里给出基类的实现**************/
PlantBase::PlantBase(int hp, int cost) :hp(hp), cost(cost)
{
	plant_time = current;
	name = new char[50];//人为保证不出界
	cin >> name;
}
PlantBase::PlantBase(PlantBase& base)
{
	//plant_time = base.plant_time;
	hp = base.hp;
	//cost = base.cost;
	name = new char[50];//人为保证不出界
	strcpy(name, base.name);
}
PlantBase::~PlantBase()
{
	delete[] name;
}
bool PlantBase::hurt(int damage)//true 活着，false死了
{
	hp -= damage;
	return hp > 0;
}
char* PlantBase::get_name()
{
	return name;
}
/********************************************/


/**********在这里给出派生类的声明和实现***********/
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
	/* 变量声明 */
	Repeater* lawn1[LAWN_LENGTH] = {};//记录双发豌豆
	GatlingPea* lawn2[LAWN_LENGTH] = {};//记录机枪豌豆
	int plant_num = 0; // 记录植物总数
	int repeater_num = 0; 
	int gatlingpea_num = 0;
	vector<time_t>plant_time;

	// 输入数据
	int sunlight, damage = 0;
	time_t n;
	cin >> sunlight >> n;

	while (true) {
		// 1. 环境：每3/6/9/...s掉落一个25的阳光
		if (current % SUNLIGHT_TIME == 0 && current > 0) {
			sunlight += 25;
		}

		/* 2. 植物：发动攻击 */
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

		/* 3. 玩家：放植物（一次只能放一株）*/
		if (repeater_num < LAWN_LENGTH && sunlight >= repeater_cost) {
			Repeater* rep = new(nothrow) Repeater;
			if (rep == NULL) {
				cout << "内存申请失败" << endl;
				return -1;
			}
			lawn1[repeater_num++] = rep;
			sunlight -= rep->get_cost();
			plant_time.push_back(current);
		}
		else if (gatlingpea_num < LAWN_LENGTH && sunlight >= gatlingpea_cost) {
			GatlingPea* gat = new(nothrow) GatlingPea(*lawn1[gatlingpea_num]);
			if (gat == NULL) {
				cout << "内存申请失败" << endl;
				return -1;
			}
			delete lawn1[gatlingpea_num];
			lawn1[gatlingpea_num] = NULL;
			lawn2[gatlingpea_num++] = gat;

			sunlight -= gat->get_cost();
			plant_time.push_back(current);
		}
		/* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current-n)的伤害 */
		if (int(current) >= n && repeater_num) {
			if (repeater_num > gatlingpea_num && !lawn1[repeater_num - 1]->hurt(10 * int(current - n))) {//死亡
				delete lawn1[--repeater_num];
				lawn1[repeater_num] = NULL;
			}
			else if (repeater_num == gatlingpea_num && !lawn2[gatlingpea_num - 1]->hurt(10 * int(current - n))) {//死亡
				delete lawn2[--gatlingpea_num];
				--repeater_num;
				lawn2[gatlingpea_num] = NULL;
			}
		}

		plant_num = repeater_num;
		//cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << "伤害  " << damage << endl;
		// 5. 游戏胜利/失败判断
		if (damage >= TARGET_DAMAGE) {
			cout << "游戏胜利" << endl;
			break;
		}
		else if (current >= n && plant_num == 0) {  // 提前判定失败
			cout << "游戏失败" << endl;
			break;
		}
		else if (current >= 100) {  // 如果第100秒过去仍未积累足够，则判负
			cout << "游戏失败" << endl;
			break;
		}
		current++;
	}

	cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;

	/* 其他输出与内存回收 */
	cout << "每一株植物种下的时刻：" << endl;
	for (auto i : plant_time) {
		cout << i << ' ';
	}
	cout << endl;
	cout << "幸存植物的名字：" << endl;
	int i = 0;
	for (; i < gatlingpea_num; ++i) {
		cout << "Gatling: " << lawn2[i]->get_name() << endl;
	}
	for (; i < repeater_num; ++i) {
		cout << "Repeater: " << lawn1[i]->get_name() << endl;
	}


	//内存回收
	for (int i = 0; i < LAWN_LENGTH; ++i) {
		if (lawn1[i])
			delete lawn1[i];
		if (lawn2[i])
			delete lawn2[i];
	}

	return 0;
}