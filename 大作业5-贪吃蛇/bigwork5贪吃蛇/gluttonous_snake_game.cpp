#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"gluttonous_snake.h"
#include<ctime>
#include <graphics.h>
//用户名输入
extern MOUSEMSG m;
extern bool mouse_change;
Game::Game()
{
    gamestatus = GAME_STATUS(_notstart);
    life = 5;
    score = 0;
    // 初始化绘图窗口
    initgraph(WINDOW_X, WINDOW_Y, SHOWCONSOLE);
    //初始化menu
    IMAGE* menupicture = new IMAGE(WINDOW_X, WINDOW_Y);//生成image指针对象
    loadimage(menupicture, L"images/bk2.jpg", WINDOW_X, WINDOW_Y);
    SetWorkingImage(menupicture);
    //gamename
    IMAGE* gametitle = new IMAGE(900, 500);
    loadimage(gametitle, L"images/gamename.png", 900, 500);
    transparentimage(menupicture, 150, 0, gametitle);
    //加button
    for (int i = 0; i < MODE_NUM; i++) {
        button(150, 40 + i * 80, GAME_MODE_NAME[i]);
        title_position.push_back(make_pair(150, 40 + i * 80));
    }
    button(150, 40 + 5 * 80, _T("查看历史"));
    title_position.push_back(make_pair(150, 40 + 5 * 80));
    //icon
    string s1 = "images/icon/1-";
    string s2 = ".png";
    IMAGE* iconpicture = new IMAGE(600, 300);//生成image指针对象
    wchar_t* wideFilename = new wchar_t[256];
    for (int i = 1; i <= ICONNUM; i++) {
        IMAGE* picture = new IMAGE(WINDOW_X, WINDOW_Y);//生成image指针对象
        SetWorkingImage(picture);
        putimage(0, 0, menupicture);
        string s = to_string(i);
        string filename = s1 + s + s2;
        const char* cStyleString = filename.c_str();
        int bufferSize = MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), -1, NULL, 0);// 将字符串转换为 ANSI 编码
        MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), -1, wideFilename, bufferSize);
        loadimage(iconpicture, wideFilename, 600, 300);// 使用转换后的字符串加载图片
        transparentimage(picture, 400, WINDOW_Y - 300, iconpicture);
        transparentimage(picture, 0, WINDOW_Y - 300, iconpicture);
        menuimage.push_back(picture);
    }
    delete gametitle;
    delete iconpicture;
    delete[] wideFilename; // 释放内存

    // 初始化background
    background = new IMAGE(WINDOW_X, WINDOW_Y);
    loadimage(background, L"images/bk.jpg", WINDOW_X, WINDOW_Y);
    SetWorkingImage(background);//先在background上面画
    for (int x = 10; x <= GAME_X; x += 20) {//边框
        SDF_circle(x, 10, MY_BLUE, MY_PURPLE, 10, 2, 10);
        SDF_circle(x, GAME_Y, MY_BLUE, MY_PURPLE, 10, 2, 10);
    }
    for (int y = 10; y <= GAME_Y; y += 20) {
        SDF_circle(10, y, MY_BLUE, MY_PURPLE, 10, 2, 10);
        SDF_circle(GAME_X, y, MY_BLUE, MY_PURPLE, 10, 2, 10);
    }
}
Game::~Game()
{
    delete background;
    for (auto i : menuimage) {
        delete i;
    }
}


//顶层控制游戏进程
void Game::Top_control()
{
    while (1) {
        // 菜单
        menu();
        // 退出
        if (mode == Quit_game)
            break;
        //初始化每一局游戏
        init_eachgame();
        while (gamestatus != _gameover && gamestatus != _notstart) {//游戏结束和退出
            //时间差
            currentTime = chrono::system_clock::now();
            //auto duration = (chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime)).count();
            //if (duration < snake.speed)
            //    continue;
            //else
            //    lastTime = currentTime;
            //游戏
            renew_status();//获取方向和暂停退出
            if (mode == AI_snakes) {
                renew_AISnake();
            }
            renew_interface();//重画页面
        }
        renew_file();
    }
    closegraph();		// 退出图形界面
}
//菜单状态维护
void Game::menu()
{
    SetWorkingImage(NULL);
    gamestatus = _notstart;
    //获取信息
    int count = 0;

    while (gamestatus == _notstart && mode != Quit_game) {
        putimage(0, 0, menuimage[count]);
        count = (count + 1) % ICONNUM;
        Sleep(20);
        mouse(); 
        switch (m.uMsg)
        {
            case WM_LBUTTONDOWN:
                // 左键按下
                if ((m.x - title_position[0].first) >= 0 && (m.x - title_position[0].first) <= BUTTON_W
                    && (m.y - title_position[0].second) >= 0 && (m.y - title_position[0].second) <= BUTTON_H)
                {
                    gamestatus = _play;
                    mode = basic_version;
                }
                else if ((m.x - title_position[1].first) >= 0 && (m.x - title_position[1].first) <= BUTTON_W
                    && (m.y - title_position[1].second) >= 0 && (m.y - title_position[1].second) <= BUTTON_H)
                {
                    gamestatus = _play;
                    mode = advanced_version;
                }
                else if ((m.x - title_position[2].first) >= 0 && (m.x - title_position[2].first) <= BUTTON_W
                    && (m.y - title_position[2].second) >= 0 && (m.y - title_position[2].second) <= BUTTON_H)
                {
                    gamestatus = _play;
                    mode = premium_edition;
                }
                else if ((m.x - title_position[3].first) >= 0 && (m.x - title_position[3].first) <= BUTTON_W
                    && (m.y - title_position[3].second) >= 0 && (m.y - title_position[3].second) <= BUTTON_H)
                {
                    gamestatus = _play;
                    mode = AI_snakes;
                }
                else if ((m.x - title_position[4].first) >= 0 && (m.x - title_position[4].first) <= BUTTON_W
                    && (m.y - title_position[4].second) >= 0 && (m.y - title_position[4].second) <= BUTTON_H)
                {
                    mode = Quit_game;
                }
                else if ((m.x - title_position[5].first) >= 0 && (m.x - title_position[5].first) <= BUTTON_W
                    && (m.y - title_position[5].second) >= 0 && (m.y - title_position[5].second) <= BUTTON_H)
                {
                    history_search();
                }
                break;
            case WM_RBUTTONDOWN:
                // 右键按下
                break;
            case WM_MOUSEMOVE:
                // 鼠标移动
                break;
            case WM_LBUTTONDBLCLK:
                // 左键双击
                break;
        }
        m.x = 0; m.y = 0;
    }
}
//历史查询和重置
void Game::history_search()
{
    // 获取查询的历史编号
    TCHAR num[256];
    InputBox(num, 50, _T("请输入查询的编号，第一次为1，依次递增。\n重置历史请输入0"), _T("历史查询"));
    wstring numStr(num);
    try {
        int intValue = std::stoi(numStr);
        TCHAR infoText[256];
        if (intValue == 0) {
            file.reset_highest_score();
            file.reset_history();
            _stprintf(infoText, _T("已重置"));
        }
        else if (file.read_history(intValue) == false)
            _stprintf(infoText, _T("没有该历史"));
        else
            _stprintf(infoText, _T("第%d条历史数据:%s"), intValue, file.history);
        MessageBox(GetHWnd(), infoText, _T("历史"), MB_OK | MB_ICONINFORMATION);
    }
    catch (invalid_argument) {
        cerr << "无效的输入，无法转换为整数。" << endl;
        exit(-1);
    }
    catch (out_of_range) {
        cerr << "超出整数范围。" << endl;
        exit(-1);
    }
}
//初始化游戏界面
void Game::init_eachgame()
{
    //初始化
    srand(unsigned int(time(NULL)));
    score = 0;
    life = 5;
    kill_num = 0;
    // 假设用户名不超过50个字符
    do
        InputBox(username, 50, _T("请输入用户名\n不得为空"), _T("用户名输入"));
    while (username[0] == '\0');
    //time
    gamestartTime = chrono::system_clock::now();
    lastaddAIsnakeTime = gamestartTime;
    //背景图片显示
    SetWorkingImage(NULL);
    putimage(0, 0, background);
    //蛇
    snake.init();
    AIsnake.clear();
    //糖果
    game_map.create_candy(mode, _notstart, snake);//生成糖果
}
//1.更新游戏状态
void Game::renew_status()
{
    //更新蛇
    snake.Top_control(game_map, AIsnake, mode, currentTime, speed_count, score);
    //看蛇有没有die,处理life和gameover
    handle_die_gameover();
    //生成糖果
    game_map.create_candy(mode, gamestatus, snake);

    //鼠标值更新status
    renew_pause_nostart();
    //暂停和退出
    if (gamestatus == _pause)
        handle_pause();
    else if (gamestatus == _notstart)//退出
        return;
}
//void Game::renew_direction()
//{
//    double X = m.x - snake.snake_head.first;
//    double Y = m.y - snake.snake_head.second;
//    double Z = sqrt(X * X + Y * Y);
//    if (Z > 3) {
//        int x = int(X * SNAKE_DIS / Z);
//        int y = int(Y * SNAKE_DIS / Z);
//        snake.head_toward = make_pair(x, y);
//    }
//    m.x = 0;
//    m.y = 0;
//}
//void Game::renew_speed()
//{
//    //如果蛇的长度小于5无法加速直接return
//    if (snake.snake_body.size() <= 5) {
//        snake.speed = slow_speed;
//        return;
//    }
//    char key = keyboard();
//    if (key == NULL)
//        snake.speed = slow_speed;
//    else {
//        snake.speed = fast_speed;
//        speed_count++;
//    }
//}
void Game::renew_pause_nostart()
{
    if (!mouse_change)
        return;
    switch (m.uMsg)
    {
        case WM_LBUTTONDOWN:
            // 左键按下暂停
            // 再按下取消暂停
            if (gamestatus != _pause)
                gamestatus = _pause;
            else
                gamestatus = _play;
            break;
        case WM_RBUTTONDOWN:
            // 右键按下退出
            gamestatus = _notstart;
            //snake.set_notbirth();
            break;
        case WM_MOUSEMOVE:
            // 鼠标移动
            break;
        case WM_LBUTTONDBLCLK:
            // 左键双击
            break;
    }
}
void Game::handle_pause() 
{
    setbkmode(TRANSPARENT);//设置背景透明
    settextstyle(&Font);
    settextcolor(MY_RED);
    TCHAR infoText[256];
    _stprintf(infoText, _T("请再次按下左键取消暂停"));
    outtextxy(GAME_X / 2 - sizeof(infoText) / 8, GAME_Y / 2, infoText);
    while (gamestatus == _pause) {
        mouse();
        if (mouse_change) {
            //鼠标值更新status
            renew_pause_nostart();
        }
    }
}
void Game::handle_die_gameover()
{
    if (snake.get_snakestatus() != _die)
        return;
    else {
        life--;
        if (life == 0 || mode == AI_snakes) {
            gamestatus = _gameover;
            //snake.set_notbirth();
            return;
        }
    }
}
//void Game::handle_move()
//{
//    int x = int(snake.head_toward.first + snake.snake_head.first);//往前移动后的坐标
//    int y = int(snake.head_toward.second + snake.snake_head.second);
//    //吃到糖
//    if (game_map.judge_eatcandy(x, y)) {
//        score += 5;
//        snake.add_lenth++;//加长度
//    }
//    //加速减长度
//    if (snake.speed == fast_speed && snake.snake_body.size() > 5) {
//        if (speed_count >= Speed_Threshold) {
//            speed_count = 0;
//            snake.add_lenth--;//减去长度
//        }//毫秒
//    }
//}
//更新AI蛇
void Game::renew_AISnake()
{
    //是否加蛇
    if (AIsnake.size() <= SNAKE_NUM_MAX && increase_AISnake()) {
        AISnake aisnake;
        AIsnake.push_back(aisnake);
    }
    //是否死亡
    for (auto it = AIsnake.begin(); it != AIsnake.end(); ) {
        auto& aisnake = *it;
        aisnake.AI_Top_control(game_map,snake,mode,currentTime,life);
        //生成糖果
        if (aisnake.get_snakestatus() == _die) {
            game_map.create_candy(mode, gamestatus, aisnake);
            it = AIsnake.erase(it);  // 移除蛇，并迭代器指向下一个元素
            kill_num++;
            continue;
        }
        ++it;  // 迭代器自增
    }

}
bool Game::increase_AISnake()
{
    auto duration = (chrono::duration_cast<std::chrono::seconds>(currentTime - lastaddAIsnakeTime)).count();
    if (duration > ADD_AISNAKE_TIME_GAP) {
        lastaddAIsnakeTime = currentTime;
        return true;
    }
    return false;
}
//2.更新页面
void Game::renew_interface()
{
    IMAGE* newimage = new IMAGE(WINDOW_X, WINDOW_Y);//生成image指针对象
    SetWorkingImage(newimage);//离屏渲染
    putimage(0, 0, background);
    //糖果
    game_map.draw_candy(newimage);//生成糖果
    //墙
    if (mode == advanced_version)
        game_map.draw_wall();
    //蛇 AI蛇
    snake.Drawsnake(newimage);
    if (mode == AI_snakes) {
        for (const auto &aisnake : AIsnake) {
            aisnake.Drawsnake(newimage);
        }
    }
    //分数和生命
    show_gameinf();
    //放图片到显示上
    SetWorkingImage(NULL);
    putimage(0, 0, newimage);
    delete newimage;
}
void Game::show_gameinf()
{
    setbkmode(TRANSPARENT);//设置背景透明
    settextstyle(&Font);
    settextcolor(MY_PURPLE);

    TCHAR infoText[256];
    auto duration = (chrono::duration_cast<std::chrono::milliseconds>(currentTime - gamestartTime)).count();
    int gametime = int(duration) / 1000;//更新游戏时间
    switch (mode) {
        case basic_version:
            _stprintf(infoText, _T("[初级版]"));
            break;
        case advanced_version:
            _stprintf(infoText, _T("[进阶版]"));
            break;
        case premium_edition:
            _stprintf(infoText, _T("[高级版]"));
            break;
        case AI_snakes:
            _stprintf(infoText, _T("[AI杀蛇版]"));
            break;
        default:
            break;
    }
    const int ygap = 40;
    outtextxy(GAME_X + 20, ygap * 1, infoText);
    _stprintf(infoText, _T("历史最高分：%lld"), file.highest_score[mode]);
    outtextxy(GAME_X + 20, ygap * 2, infoText);
    _stprintf(infoText, _T("游戏得分：%lld"), score);
    outtextxy(GAME_X + 20, ygap * 3, infoText);
    _stprintf(infoText, _T("蛇的长度：%zd"), snake.get_snakesize());
    outtextxy(GAME_X + 20, ygap * 4, infoText);
    if (mode != AI_snakes)
        _stprintf(infoText, _T("生命次数：%d"), life);
    else
        _stprintf(infoText, _T("击杀数量：%d"), kill_num);
    outtextxy(GAME_X + 20, ygap * 5, infoText);
    _stprintf(infoText, _T("游戏时间：%02d:%02d"), gametime / 60, gametime % 60);
    outtextxy(GAME_X + 20, ygap * 6, infoText);

    settextcolor(MY_RED);
    _stprintf(infoText, _T("提示："));
    outtextxy(GAME_X + 20, ygap * 8, infoText);
    _stprintf(infoText, _T("鼠标左键暂停，再次左键取消暂停"));
    outtextxy(GAME_X + 20, ygap * 9, infoText);
    _stprintf(infoText, _T("鼠标右键退出本局游戏"));
    outtextxy(GAME_X + 20, ygap * 10, infoText);
    _stprintf(infoText, _T("空格加速！！！"));
    outtextxy(GAME_X + 20, ygap * 11, infoText);
    _stprintf(infoText, _T("但是会减去长度，谨慎使用哦~~~"));
    outtextxy(GAME_X + 20, ygap * 12, infoText);
    _stprintf(infoText, _T("出生五秒无敌时间，无法互相杀死！"));
    outtextxy(GAME_X + 20, ygap * 13, infoText);
    if (snake.get_snakesize() <= 5) {
        _stprintf(infoText, _T("蛇的长度太短啦，跑不动啦！！！"));
        outtextxy(GAME_X + 20, ygap * 14, infoText);
    }

}

void Game::renew_file()
{
    file.update_highest_score(mode, score);//更新最高分
    file.save_history(mode, username, score);
}

