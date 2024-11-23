#ifndef CONSTA_H
#define CONSTA_H
/*
1.左键暂停
2.空格加速
3.右键退出本局游戏
*/
//常数
const double M_PI = 3.1415926;
//字体
const LOGFONT Font{ 20, 10, 0, 0, FW_DONTCARE, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"黑体" };

//game
    //屏幕
const int WINDOW_X = 1000;
const int WINDOW_Y = 660;
const int GAME_X = WINDOW_Y - 10;
const int GAME_Y = WINDOW_Y - 10;
//mode
const int MODE_NUM = 6;
//menu
const int ICONNUM = 24;
const int BUTTON_W = 200, BUTTON_H = 50;
const TCHAR GAME_MODE_NAME[MODE_NUM][50] = { _T("Basic Version"),_T("Advanced Version"),_T("Premium Edition"),_T("人机杀蛇版"),_T("Quit Game"),_T("History") };
//速度
const int Speed_Threshold = 30;//speed_count超过就减一节
//snake
const int SNAKE_BODY_PIC_SIZE = 30;//身体图片的大小
const int SNAKE_PRO_PIC_SIZE = 300;//保护圈图片的大小
const int SNAKE_INIT_LEN = 5;//初始蛇的长度
const int SNAKE_RADIUS = 12;//一节蛇身的半径
const int SNAKE_DIS = 14;//两节蛇身之间的距离
const int PROTECT_TIME = 5;

const int SNAKE_NUM_MAX = 6;//AI蛇的最大数量
const int ADD_AISNAKE_TIME_GAP = 6;//加AI蛇的时间间隔
//candy
const int CANDY_COUNT = 40;//屏幕上candy的数量
const int CANDY_PICTURE_SIZE = 30;//candy_pic的size

//file
//const char *HIGHEST_SCORE_FILENAME = (const char *)"userdata/highest_score.txt";
const char HIGHEST_SCORE_FILENAME[] = "userdata/highest_score.txt";
const char GAME_HISTORY_SAVE_FILENAME[] = "userdata/game_history.txt";//版本：入门版 用户名：root 得分：100

//drawtool
#define SDF_WIDTH_CIRCLE 30//抗锯齿处理像素宽度 circle
#define SDF_WIDTH_LINE 10//抗锯齿处理像素宽度 line

//各种color
#define MY_PURPLE RGB(150,142,185)
#define MY_WHITE RGB(248, 241, 248)
#define MY_RED RGB(245,150,150)
#define MY_LIGHT_RED RGB(255, 186, 201)
#define MY_PINK RGB(249,218,228)
#define MY_WHITE_2 RGB(249, 236, 243)
#define MY_BLUE RGB(239,239,246)
#endif // !CONST

