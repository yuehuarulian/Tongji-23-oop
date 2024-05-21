#include <iostream>
#define LAWN_LENGTH 9
#define SUNLIGHT_TIME 3
#define TARGET_SUNLIGHT 500
using namespace std;

const int sunflower_cost = 50;
const int sunflower_create = 25;
time_t current = 0;  // 模拟记录时间，单位s

class PlantBase {
private:
	int hp;				// 植物的生命值

protected:
	time_t plant_time;	// 植物被种下的时间
	time_t interval;	// 植物攻击或生产的时间间隔

public:
	PlantBase(int hp, time_t interval);
	bool hurt(int damage);
};

/***********在这里给出PlantBase的实现***********/
PlantBase::PlantBase(int hp, time_t interval):hp(hp),interval(interval)
{
	plant_time = current;
}
/*从第 $n$ 秒开始，僵尸发起进攻，
每秒钟最右侧的植物会受到 $10*(t-n)$ 的伤害（其中 $t$ 表示当前时间）。
如果向日葵的生命值小于等于 $0$，向日葵死亡， 该位置变为空位置。数值 $n$ 由用户输入得到*/
bool PlantBase::hurt(int damage)//true 活着，false死了
{
	hp -= damage;
	return hp > 0;
}
/********************************************/


/********在这里给出SunFlower的声明和实现*********/
/*向日葵生命值 hp=60，需要消耗 cost=50 阳光，每 interval=5s 生产 create=25 点阳光。请你自行设计派生类*/
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
	/* 变量声明 */
	SunFlower* lawn[LAWN_LENGTH] = {};
	int plant_num = 0; // 记录植物总数

	// 输入数据
	int sunlight;
	time_t n;
	cin >> sunlight >> n;

	while (true) {
		// 1. 环境：每3/6/9/...s掉落一个25的阳光
		if (current % SUNLIGHT_TIME == 0 && current > 0) {
			sunlight += 25;
		}

		/* 2. 植物：产阳光 */
		for (int i = 0; i < plant_num; i++) {
			if ((current - lawn[i]->get_plant_time()) % (lawn[i]->get_interval()) == 0 && current > 0) {
				sunlight += lawn[i]->get_create();
			}
		}

		/* 3. 玩家：放植物（一次只能放一株）*/
		if (plant_num < LAWN_LENGTH && sunlight >= sunflower_cost) {
			SunFlower* sunflower = new(nothrow) SunFlower;
			if (sunflower == NULL){
				cout << "内存申请失败" << endl;
				return -1;
			}
			lawn[plant_num++] = sunflower;
			sunlight -= sunflower->get_cost();
		}

		/* 4. 僵尸：从第n秒开始，每一秒最右侧的向日葵会收到10*(current-n)的伤害 */
		if (int(current) > n && plant_num && !lawn[plant_num - 1]->hurt(10 * int(current - n))) {//死亡
			delete lawn[--plant_num];
			lawn[plant_num] = NULL;
		}

		cout << "时刻数：" << current << " 阳光数：" << sunlight << " 植物数：" << plant_num << endl;

		// 5. 游戏胜利/失败判断
		if (sunlight >= TARGET_SUNLIGHT) {
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

	// 内存回收
	for (int i = 0; i < LAWN_LENGTH; ++i) {
		if (lawn[i])
			delete lawn[i];
	}

	return 0;
}