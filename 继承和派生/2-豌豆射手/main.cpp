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
/*豌豆射手生命值 60，需要消耗 100 点阳光，每 2s 进行一次攻击，造成 10 点伤害。*/
const int peashooter_life = 60;
const int peashooter_cost = 100;
const int peashooter_hurt = 10;
const int peashooter_interval = 2;
//const char* NUM[9] = { char* ("一"),char* ("二"),const char* ("三"),const char* ("四"),const char* ("五") ,const char* ("六") ,const char* ("七"),const char* ("八"),const char* ("九") };
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
	/* 变量声明 */
	PeaShooter* lawn[LAWN_LENGTH] = {};
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

		/* 2. 植物：发动攻击 */
		for (int i = 0; i < plant_num; i++) {
			if ((current - lawn[i]->get_plant_time()) % (lawn[i]->get_interval()) == 0 && current > 0) {
				damage += lawn[i]->get_hurtpoint();
			}
		}

		/* 3. 玩家：放植物（一次只能放一株）*/
		if (plant_num < LAWN_LENGTH && sunlight >= peashooter_cost) {
			PeaShooter* pea = new(nothrow) PeaShooter;
			if (pea == NULL) {
				cout << "内存申请失败" << endl;
				return -1;
			}
			lawn[plant_num++] = pea;
			sunlight -= pea->get_cost();
			plant_time.push_back(current);
		}

		/* 4. 僵尸：从第n秒开始，每一秒最右侧的植物会收到10*(current-n)的伤害 */
		if (int(current) > n && !lawn[plant_num - 1]->hurt(10 * int(current - n))) {//死亡
			delete lawn[--plant_num];
			lawn[plant_num] = NULL;
		}

		//cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;
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


/*
游戏胜利

时刻数：16 阳光数：225 植物数：9

每一株植物种下的时刻：
0 1 2 3 4 5 6 7 8

幸存植物的名字：
第一株豌豆
第二株豌豆
第三株豌豆
第四株豌豆
第五株豌豆
第六株豌豆
第七株豌豆
第八株豌豆
第九株豌豆
*/