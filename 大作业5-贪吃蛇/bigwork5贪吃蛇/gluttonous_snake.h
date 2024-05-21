#ifndef GAME_H
#define GAME_H
#include <stdio.h>
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <math.h>
#include <string>
#include <windows.h>
#include <chrono>
#include <fstream>
#include "consta.h"
using namespace std;
//游戏模式
enum GAME_MODES {
	basic_version,//初级版
	advanced_version,//进阶版
	premium_edition,//高级版
	AI_snakes,//AI杀蛇版
	Quit_game,//退出游戏界面
	History//历史记录
};
//游戏状态
enum GAME_STATUS {
	_notstart,
	_play,
	_pause,
	_gameover
};
//蛇的状态
enum SNAKE_STATUS {
	_notbirth,
	_move,
	_die,
};
//Snakespeed
enum SNAKE_SPEED {
	slow_speed = 90,
	middle_speed = 50,
	fast_speed = 30
};
//AIsnake的模式
enum AISNAKE_MODES {
	kill_player,
	eat_candy
};
class Snake;
class AISnake;
class Map;
class Game;
class File;

class Snake {
protected:
	IMAGE* snake_body_icon, * snake_protect;//图片
	chrono::time_point<std::chrono::system_clock>lastmovetime, birthtime;//上次move的时间 出生时间
	bool isprotect;//是否保护时间
	//pair<int, int> head_toward;//蛇头朝向
	SNAKE_SPEED speed;//蛇的速度
	SNAKE_STATUS snakestatus;//s蛇的状态
	deque<pair<int, int>>snake_body;//end为蛇头。0为蛇尾
	//pair<int, int> snake_head;//蛇开始和结束
	int add_lenth;//蛇身增加长度
	//蛇出生
	void snake_birth(const int& birth_lenth);
	//更新方向
	void renew_direction();
	//更新速度
	void renew_speed(int& speed_count);
	//更新长度
	void renew_addlenth(Map& game_map, long long& score, int& speed_count);
	//更新身体
	void renew_body();
	//判断是否要移动是否在保护时间
	bool judgemove_pro(const chrono::time_point<std::chrono::system_clock>& currenttime);//是否移动一格
public:
	//friend AISnake;
	friend Map;
	Snake();
	~Snake();
	pair<int, int> head_toward;//蛇头朝向
	pair<int, int> snake_head;//蛇开始
	//每局游戏开始时初始化
	void init();
	//获得蛇长
	int get_snakesize();
	//获得蛇状态
	SNAKE_STATUS get_snakestatus();
	//
	void Top_control(Map& game_map, const vector <AISnake>& AIsnake, const GAME_MODES &mode, const chrono::time_point<std::chrono::system_clock>& currenttime,int& speed_count, long long& score);//改变snakebody处理蛇的状态
	void Drawsnake(IMAGE* newimage) const;//画蛇
	bool judge_hitsnake(const int &x, const int &y, const int die_dis = 20) const;//是否撞到了本蛇
};
class AISnake : public Snake {
private:
	pair<int, int> target;//目标
	AISNAKE_MODES aisnake_mode;
	void makeDecision(const Snake& snake, const Map& game_map);//做出决定，规划方向
public:
	AISnake();
	explicit AISnake(const AISnake& AIs);
	AISnake& operator=(const AISnake& AIs);
	~AISnake() {};
	void AI_Top_control(Map& game_map, const Snake& snake, const GAME_MODES& mode, const chrono::time_point<std::chrono::system_clock>& currenttime, int& life);//改变蛇
};
class Map {
public:
	Map();
	~Map();
	void create_candy(const GAME_MODES &mode, const GAME_STATUS &gamestatus, const Snake& snake);
	void draw_candy(IMAGE* newimage);
	void draw_wall();
	bool judge_hitwall(const int &x, const int &y, const GAME_MODES &mode, const int die_dis = 20) const;
	bool judge_eatcandy(const int &x, const int &y);
private:
	map<pair<int, int>, int> candy;
	set<pair<int, int>> wall;
	vector<IMAGE*> candy_pic;
	friend class AISnake;
	friend class Snake;
};
class File {
public:
	File();
	void update_highest_score(const GAME_MODES &mode, const long long &score);
	void read_highest_score();
	void reset_highest_score();

	void save_history(const GAME_MODES &mode, const TCHAR* username, const long long &score);
	bool read_history(int history_num);
	void reset_history();
	long long int highest_score[MODE_NUM - 2];
	WCHAR history[256];
private:
	void save_to_file(const char* filename, long long int* array, const size_t &size);
	void save_to_file(const char* filename, TCHAR* array, const size_t &size);
	streamsize read_from_file(const char* filename, long long int* array, const size_t &size);
	streamsize read_from_file(const char* filename, TCHAR* array, const int &history_num);
	void clear_file(const char* filename);
};

class Game {
public:
	Game();//初始化整个游戏
	~Game();
	void Top_control();//整体控制函数
private:
	//时间
	chrono::time_point<std::chrono::system_clock>currentTime;//记录现在的时间
	chrono::time_point<std::chrono::system_clock>gamestartTime;//记录一局游戏开始的时间
	chrono::time_point<std::chrono::system_clock>lastaddAIsnakeTime;
	int speed_count;
	//menu菜单的5个模式
	vector<pair<int, int>> title_position;
	//背景图片 菜单图片
	IMAGE* background;
	vector<IMAGE*>menuimage;
	//状态记录模式记录
	GAME_STATUS gamestatus;
	GAME_MODES mode;
	//蛇
	Snake snake;
	vector <AISnake> AIsnake;
	//地图
	Map game_map;
	//文件
	File file;
	//一些游戏的参数
	int life;//生命值
	long long int score;//本局分数
	int kill_num;//击杀数量
	TCHAR username[256] = _T("");//用户名
	//函数
	void menu();//菜单
	void history_search();//历史记录

	void init_eachgame();//初始化一局游戏，包括snake和map的初始化

	void renew_status();//更新status
	//bool mouse();//获取鼠标结构体
	//char keyboard();//获取键盘
	//void renew_direction();//获取方向
	//void renew_speed();
	void renew_pause_nostart();
	void handle_pause();
	void handle_die_gameover();
	//void handle_move();
	//void Judge_status();//判断状态，更新status
	void renew_AISnake();
	bool increase_AISnake();
	
	void renew_interface();//重新画蛇和糖果
	void show_gameinf();

	void renew_file();
};

bool mouse();
//draw tool
COLORREF mix_color(COLORREF bg, COLORREF color, double alpha);
void SDF_circle(int center_x, int center_y, COLORREF color_1, COLORREF color_2, int  radius_1, int radius_2, int SDF_degree);
void SDF_line(int x1, int y1, int x2, int y2, COLORREF color, int thickness, int SDF_degree);
void button(int x, int y, const TCHAR* text);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
#endif