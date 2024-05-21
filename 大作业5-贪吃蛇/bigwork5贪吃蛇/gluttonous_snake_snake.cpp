#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"gluttonous_snake.h"
#include<ctime>
#include <graphics.h>

// 鼠标结构体
MOUSEMSG m{ 0 };
bool mouse_change;
//获得鼠标状态
bool mouse()
{
    if (!MouseHit())
    {
        m.x = 0;
        m.y = 0;
        mouse_change = false;
        return false;
    }
    while (MouseHit())  // 处理所有鼠标消息 清空消息列队只留有点击的那一个
    {
        m = GetMouseMsg();  // 获取鼠标消息
        if (m.uMsg == WM_LBUTTONDOWN || m.uMsg == WM_RBUTTONDOWN) {
            /*         while(MouseHit())
                         GetMouseMsg();*/
            break;
        }
    }
    mouse_change = true;
    return true;
}
//获取键盘按下值，如果没有返回NULL
char keyboard()
{
    char key = NULL;
    if (_kbhit()) {
        // 如果有键盘按键被按下
        key = _getch();
    }
    return key;
}


Snake::Snake()
{
    add_lenth = 0;
    lastmovetime = chrono::system_clock::now();
    birthtime = lastmovetime;
    speed = slow_speed;
    snakestatus = _notbirth;
    isprotect = true;
    head_toward = make_pair(1, 0);
    //身体图片
    snake_body_icon = new IMAGE(SNAKE_BODY_PIC_SIZE, SNAKE_BODY_PIC_SIZE);
    loadimage(snake_body_icon, _T("images/snake_body.png"), SNAKE_BODY_PIC_SIZE, SNAKE_BODY_PIC_SIZE);
    //保护圈图片
    snake_protect = new IMAGE(SNAKE_PRO_PIC_SIZE, SNAKE_PRO_PIC_SIZE);
    loadimage(snake_protect, _T("images/birth.png"), SNAKE_PRO_PIC_SIZE, SNAKE_PRO_PIC_SIZE);
}
Snake::~Snake()
{
    delete snake_body_icon;
    delete snake_protect;
}
//出生
void Snake::snake_birth(const int& birth_lenth)
{
    snake_body.clear();
    int y = GAME_Y / 2;
    int x = GAME_X / 2 - SNAKE_INIT_LEN * SNAKE_DIS;
    for (int c = 0; c < birth_lenth; c++) {
        snake_body.push_back(make_pair(x, y));
        x += SNAKE_DIS;
    }
    snake_head = snake_body.back();
}
//死后复生
void Snake::init()
{
    add_lenth = 0;
    lastmovetime = chrono::system_clock::now();
    birthtime = lastmovetime;
    speed = slow_speed;
    snake_birth(5);
    snakestatus = _move;
    isprotect = true;
    head_toward = make_pair(1, 0);
}
//设置未出生
//void Snake::set_notbirth()
//{
//    snakestatus = _notbirth;
//}
//
void Snake::renew_direction()
{
    double X = m.x - snake_head.first;
    double Y = m.y - snake_head.second;
    double Z = sqrt(X * X + Y * Y);
    if (Z > 3) {
        int x = int(X * SNAKE_DIS / Z);
        int y = int(Y * SNAKE_DIS / Z);
        head_toward = make_pair(x, y);
    }
    m.x = 0;
    m.y = 0;
}
void Snake::renew_speed(int& speed_count)
{
    //如果蛇的长度小于5无法加速直接return
    if (snake_body.size() <= 5) {
        speed = slow_speed;
        return;
    }
    char key = keyboard();
    if (key == NULL)
        speed = slow_speed;
    else {
        speed = fast_speed;
        speed_count++;
    }
}
void Snake::renew_addlenth(Map &game_map,long long &score,int &speed_count)
{
    if (snakestatus != _move) {
        return;
    }
    //吃到糖
    if (game_map.judge_eatcandy(snake_head.first, snake_head.second)) {
        score += 5;
        add_lenth++;//加长度
    }
    //加速减长度
    if (speed == fast_speed && snake_body.size() > 5) {
        if (speed_count >= Speed_Threshold) {
            speed_count = 0;
            add_lenth--;//减去长度
        }//毫秒
    }
}
void Snake::renew_body()
{
    int x = int(head_toward.first + snake_head.first);//往前移动后的坐标
    int y = int(head_toward.second + snake_head.second);
    snake_body.push_back(make_pair(x, y));//蛇头加
    add_lenth--;
    while (add_lenth > 0) {
        add_lenth--;
        auto i = snake_body.front();
        snake_body.push_front(i);//蛇尾加
    }
    while (add_lenth < 0) {
        add_lenth++;
        snake_body.pop_front();//蛇尾减
    }
}
bool Snake::judgemove_pro(const chrono::time_point<std::chrono::system_clock> &currenttime)
{
    //是否还在保护
    if (isprotect) {
        auto duration = (chrono::duration_cast<std::chrono::seconds>(currenttime - birthtime)).count();
        if (duration > PROTECT_TIME)
            isprotect = false;
    }
    //是否要移动
    auto duration = (chrono::duration_cast<std::chrono::milliseconds>(currenttime - lastmovetime)).count();
    if (duration < speed)
        return false;
    else {
        lastmovetime = currenttime;
        return true;
    }
}
//判断蛇的状态做出改变,顶层控制函数
void Snake::Top_control(Map& game_map,const vector <AISnake> &AIsnake, const GAME_MODES& mode, const chrono::time_point<std::chrono::system_clock>& currenttime,int &speed_count,long long &score)
{
    //是否需要重生
    if (snakestatus == _die || snakestatus == _notbirth) {
        init();
    }

    //是否需要移动蛇
    if (!judgemove_pro(currenttime))
        return;

    //判断有没有撞墙撞蛇
    if (!isprotect) {
        if (game_map.judge_hitwall(snake_head.first, snake_head.second, mode)) {//是否撞墙
            snakestatus = _die;
        }
        else if (mode == AI_snakes) {
            for (auto& aisnake : AIsnake) {
                if (aisnake.judge_hitsnake(snake_head.first, snake_head.second)) {
                    snakestatus = _die;
                    break;
                }
            }
        }
    }
    //是否死亡
    if (snakestatus == _die) {
        return;
    }
    //有没有吃糖更新蛇的长度
    renew_addlenth(game_map, score, speed_count);

    mouse();
    //鼠标值更新方向
    if (mouse_change) {
        renew_direction();
    }
    //键盘更新速度
    renew_speed(speed_count);
    //更新蛇的身体
    renew_body();
    //更新head和end
    snake_head = snake_body.back();
}

//画蛇
void Snake::Drawsnake(IMAGE* newimage) const//toward:0,30,60 - 330度
{
    //重新画蛇
    for (auto snake : snake_body) {
        transparentimage(newimage, snake.first - SNAKE_BODY_PIC_SIZE / 2, snake.second - SNAKE_BODY_PIC_SIZE / 2, snake_body_icon);
    }
    //头特殊处理
    auto snake = snake_body.back();
    if (isprotect) {
        transparentimage(newimage, snake.first - SNAKE_PRO_PIC_SIZE / 2, snake.second - SNAKE_PRO_PIC_SIZE / 2, snake_protect);
    }
    setfillcolor(WHITE);
    fillcircle(snake.first, snake.second, SNAKE_RADIUS / 2);
    setfillcolor(BLACK);
    fillcircle(snake.first, snake.second, 2);
    //SDF_circle(snake.first, snake.second, WHITE, NULL, SNAKE_RADIUS / 2, 0, 2);
    //SDF_circle(snake.first, snake.second, BLACK, NULL, 2, 0, 2);
}

//是否撞到了this蛇，也就是说我是否杀死了对方
bool Snake::judge_hitsnake(const int &x, const int &y, const int die_dis)const
{
    if (isprotect)
        return false;
    for (auto i : snake_body) {
        double disdance = sqrt((x - i.first) * (x - i.first) + (y - i.second) * (y - i.second));
        if (disdance <= die_dis)
            return true;
    }
    return false;
}

//获取蛇长
int Snake::get_snakesize()
{
    return int(snake_body.size());
}

//获取状态
SNAKE_STATUS Snake::get_snakestatus()
{
    return snakestatus;
}


//AI
AISnake::AISnake() : Snake() {
    aisnake_mode = eat_candy;
    loadimage(snake_body_icon, _T("images/aisnake_body.png"), SNAKE_BODY_PIC_SIZE, SNAKE_BODY_PIC_SIZE);
    loadimage(snake_protect, _T("images/birthAI.png"), SNAKE_PRO_PIC_SIZE, SNAKE_PRO_PIC_SIZE);
    init();
}
AISnake::AISnake(const AISnake& AIs)
{
    lastmovetime = AIs.lastmovetime;
    birthtime = AIs.birthtime;
    isprotect = AIs.isprotect;
    head_toward = AIs.head_toward;
    speed = AIs.speed;
    snakestatus = AIs.snakestatus;
    snake_body = AIs.snake_body;
    snake_head = AIs.snake_head;
    add_lenth = AIs.add_lenth;
    head_toward = make_pair(1, 0);

    target = AIs.target;
    aisnake_mode = AIs.aisnake_mode;
    //身体图片
    snake_body_icon = new IMAGE(SNAKE_BODY_PIC_SIZE, SNAKE_BODY_PIC_SIZE);
    loadimage(snake_body_icon, _T("images/aisnake_body.png"), SNAKE_BODY_PIC_SIZE, SNAKE_BODY_PIC_SIZE);
    //保护圈图片
    snake_protect = new IMAGE(SNAKE_PRO_PIC_SIZE, SNAKE_PRO_PIC_SIZE);
    loadimage(snake_protect, _T("images/birthAI.png"), SNAKE_PRO_PIC_SIZE, SNAKE_PRO_PIC_SIZE);
}
AISnake &AISnake::operator=(const AISnake& AIs) {
    lastmovetime = AIs.lastmovetime;
    birthtime = AIs.birthtime;
    isprotect = AIs.isprotect;
    head_toward = AIs.head_toward;
    speed = AIs.speed;
    snakestatus = AIs.snakestatus;
    snake_body = AIs.snake_body;
    snake_head = AIs.snake_head;
    add_lenth = AIs.add_lenth;

    target = AIs.target;
    aisnake_mode = AIs.aisnake_mode;
    //身体图片
    snake_body_icon = new IMAGE(SNAKE_BODY_PIC_SIZE, SNAKE_BODY_PIC_SIZE);
    loadimage(snake_body_icon, _T("images/aisnake_body.png"), SNAKE_BODY_PIC_SIZE, SNAKE_BODY_PIC_SIZE);
    //保护圈图片
    snake_protect = new IMAGE(SNAKE_PRO_PIC_SIZE, SNAKE_PRO_PIC_SIZE);
    loadimage(snake_protect, _T("images/birthAI.png"), SNAKE_PRO_PIC_SIZE, SNAKE_PRO_PIC_SIZE);
    return *this;
}
//规划方向
void AISnake::makeDecision(const Snake& snake, const Map& game_map)
{
    static bool have_target = false;//是否有目标
    //更新目标
    if (!have_target) {
        //outtextxy(10, 10, _T("换目标"));
        aisnake_mode = AISNAKE_MODES(rand() % 2);
        switch (rand() % 2) {
            case 0:
                speed = middle_speed;
                break;
            case 1:
                speed = slow_speed;
                break;
        }
        if (aisnake_mode == kill_player) {
            //speed = slow_speed;
            target.first = snake.snake_head.first + snake.head_toward.first * 2;//?
            target.second = snake.snake_head.second + snake.head_toward.second * 2;//?
        }
        else if (aisnake_mode == eat_candy) {
            //speed = middle_speed;
            auto it = game_map.candy.begin();
            int i = rand() % game_map.candy.size();
            std::advance(it, i - 1);  // 使用 std::advance 将迭代器移动到第 i 个元素
            if (it != game_map.candy.end()) {
                target.first = it->first.first;
                target.second = it->first.second;
            }
            else {
                target.first = GAME_X / 2;
                target.second = GAME_Y / 2;
            }
        }
        have_target = true;
    }
    else if (aisnake_mode == eat_candy && game_map.candy.find(target) == game_map.candy.end()) {
        have_target = false;
    }
    else if (aisnake_mode == kill_player) {
        target.first = snake.snake_head.first + snake.head_toward.first * 2;//?
        target.second = snake.snake_head.second + snake.head_toward.second * 2;//?
    }
    //更新方向
    double X = target.first - snake_head.first;
    double Y = target.second - snake_head.second;
    double Z = sqrt(X * X + Y * Y);
    int x = head_toward.first;
    int y = head_toward.second;
    if (Z > 3) {
        x = int(X * SNAKE_DIS / Z);
        y = int(Y * SNAKE_DIS / Z);
    }
    //看会不会撞墙和撞蛇
    int xpredict = int(x + snake_head.first * 5);//预估走后的位置
    int ypredict = int(y + snake_head.second * 5);
    if (game_map.judge_hitwall(xpredict, ypredict, AI_snakes)) {
        //outtextxy(10,10, _T("撞墙"));
        x = -x;
        y = -y;
        have_target = false;
    }
    else if (snake.judge_hitsnake(xpredict, ypredict, 50)) {
        x = snake.head_toward.first;
        y = snake.head_toward.second;
        //outtextxy(10, 10, _T("撞蛇"));
        have_target = false;
    }
    head_toward = make_pair(x, y);
    //TCHAR infoText[256];
    //_stprintf(infoText, _T("x:%d,y:%d"), int(x),int(y));
    //outtextxy(200,200, infoText);
}
//判断蛇的状态做出改变,顶层控制函数
void AISnake::AI_Top_control(Map& game_map, const Snake& snake, const GAME_MODES& mode, const chrono::time_point<std::chrono::system_clock>& currenttime, int& life)
{
    if (!judgemove_pro(currenttime)) {
        return;
    }
    //判断有没有撞墙撞蛇
    if (!isprotect) {
        if (game_map.judge_hitwall(snake_head.first, snake_head.second, mode)) {
            snakestatus = _die;
            return;
        }
        else if (snake.judge_hitsnake(snake_head.first, snake_head.second)) {
            snakestatus = _die;
            return;
        }
    }
    //有没有吃糖更新蛇的长度
    if (game_map.judge_eatcandy(snake_head.first, snake_head.second)) {
        add_lenth++;
    }

    //做出决定更新方向
    makeDecision(snake, game_map);
    //更新蛇的身体
    renew_body();
    //更新head和end
    snake_head = snake_body.back();

}
