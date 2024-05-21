#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_DAMAGE 1000
using namespace std;

const int sunflower_life = 60;
const int sunflower_cost = 50;
const int sunflower_interval = 5;
const int sunflower_create = 25;
/*豌豆射手生命值 60，需要消耗 100 点阳光，每 2s 进行一次攻击，造成 10 点伤害。*/
const int peashooter_life = 60;
const int peashooter_cost = 100;
const int peashooter_hurt = 10;
const int peashooter_interval = 2;
/*阳光豌豆生命值 60，需要消耗 125 点阳光，每 2s 进行一次攻击，造成 10 点伤害；
另外，其每 5s 还会生产 25 点阳光*/
const int sunneypea_life = 60;
const int sunneypea_cost = 125;
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
/*向日葵生命值 hp=60，需要消耗 cost=50 阳光，每 interval=5s 生产 create=25 点阳光。请你自行设计派生类*/
class SunFlower :virtual public PlantBase {
public:
	SunFlower() :PlantBase(sunflower_life, sunflower_cost), create(sunflower_create), interval(sunflower_interval) {};
	//SunFlower(const int life, const int cost) :PlantBase(life, cost), create(sunflower_create), interval(sunflower_interval) {};
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
protected:
	const int create;
	const int interval;
};

class PeaShooter :virtual public PlantBase {
public:
	PeaShooter() :PlantBase(peashooter_life, peashooter_cost), hurtpoint(peashooter_hurt), interval(peashooter_interval) {}
	//PeaShooter(const int life, const int cost) :PlantBase(life, cost), hurtpoint(peashooter_hurt), interval(peashooter_interval) {}
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
	const int hurtpoint;
	const int interval;
};

class SunnyPea :public SunFlower, public PeaShooter {
public:
	SunnyPea() :PlantBase(sunneypea_life, sunneypea_cost), SunFlower(), PeaShooter() {}
	time_t get_suninterval()
	{
		return SunFlower::interval;
	}
	time_t get_damageinterval()
	{
		return PeaShooter::interval;
	}
	time_t get_plant_time()
	{
		return plant_time;
	}
	const int get_create()
	{
		return create;
	}
	const int get_hurtpoint()
	{
		return hurtpoint;
	}
	const int get_cost()
	{
		return cost;
	}
};
/******************************************/


int main()
{
	/* 变量声明 */
	SunnyPea* lawn[LAWN_LENGTH] = {};
	int plant_num = 0; // 记录植物总数
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

		/* 2. 植物：产阳光 */
		for (int i = 0; i < plant_num; i++) {
			if ((current - lawn[i]->get_plant_time()) % (lawn[i]->get_suninterval()) == 0 && current > 0) {
				sunlight += lawn[i]->get_create();
			}
		}
		   /* 植物：发动攻击 */
		for (int i = 0; i < plant_num; i++) {
			if ((current - lawn[i]->get_plant_time()) % (lawn[i]->get_damageinterval()) == 0 && current > 0) {
				damage += lawn[i]->get_hurtpoint();
			}
		}

		/* 3. 玩家：放植物（一次只能放一株）*/
		if (plant_num < LAWN_LENGTH && sunlight >= sunneypea_cost) {
			SunnyPea* pea = new(nothrow) SunnyPea;
			if (pea == NULL) {
				cout << "内存申请失败" << endl;
				return -1;
			}
			lawn[plant_num++] = pea;
			sunlight -= pea->get_cost();
			plant_time.push_back(current);
		}

		/* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current-n)的伤害 */
		if (int(current) > n && plant_num && !lawn[plant_num - 1]->hurt(10 * int(current - n))) {//死亡
			delete lawn[--plant_num];
			lawn[plant_num] = NULL;
		}

		//cout << "时刻数：" << current << " 阳光数：" << sunlight << "伤害数： " <<damage<< " 植物数：" << plant_num << endl;
		// 5. 游戏胜利/失败判断
		if (damage >= TARGET_DAMAGE) {
			cout << "游戏胜利" << endl;
			break;
		}
		else if (current >= n && plant_num == 0) {  // 提前判定失败
			cout << "游戏失败" << endl;
			break;
		}
		else if (current >= 100) {  // 如果第100秒过去仍未积累足够阳光，则判负
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
	for (int i = 0; i < plant_num; ++i) {
		cout << lawn[i]->get_name() << endl;
	}


	for (int i = 0; i < LAWN_LENGTH; ++i) {
		if (lawn[i])
			delete lawn[i];
	}

	return 0;
}