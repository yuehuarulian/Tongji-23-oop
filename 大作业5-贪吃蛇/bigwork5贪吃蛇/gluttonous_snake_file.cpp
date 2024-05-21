#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"gluttonous_snake.h"

/// <summary>
/// File Function
/// </summary>
File::File()
{
    read_highest_score();//读取到highestScore
}
//把字符串保存到文件
void File::save_to_file(const char* filename, long long int* array, const size_t& size) {
    ofstream file(filename, ios::binary | ios::out);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(array), sizeof(long long int) * size);
        file.close();
    }
    else {
        cerr << "无法打开文件：" << GAME_HISTORY_SAVE_FILENAME << endl;
        exit(-1);
    }
    /*FILE* file = fopen(filename, "wb");
    if (file == NULL)
        exit(-1);
    fwrite(array, sizeof(T), size, file);
    fclose(file);*/
}
void File::save_to_file(const char* filename, TCHAR* array, const size_t& size) {
    ofstream file(filename, ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(array), sizeof(TCHAR) * size);
        file.close();
    }
    else {
        cerr << "无法打开文件：" << GAME_HISTORY_SAVE_FILENAME << endl;
        exit(-1);
    }
}
//从文件读取字符串
streamsize File::read_from_file(const char* filename, long long int* array, const size_t& size) {
    ifstream file(filename, ios::binary | ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(array), sizeof(long long int) * size);
        streamsize bytesRead = file.gcount();
        file.close();
        return bytesRead;
    }
    else {
        cerr << "无法打开文件：" << GAME_HISTORY_SAVE_FILENAME << endl;
        exit(-1);
    }
    return NULL;
    //FILE* file = fopen(filename, "rb");
    //if (file == NULL)
    //    exit(-1);
    //fread(array, sizeof(T), size, file);
    //fclose(file);
}
streamsize File::read_from_file(const char* filename, TCHAR* array, const int& history_num) {
    ifstream file(filename, ios::in);
    if (file.is_open()) {
        for (int i = 0; i < history_num; i++) {
            file.getline(reinterpret_cast<char*>(array), 256);
            file.get();///?
            if (file.eof())
                return NULL;
        }
        streamsize bytesRead = file.gcount();
        file.close();
        return bytesRead;
    }
    else {
        cerr << "无法打开文件：" << GAME_HISTORY_SAVE_FILENAME << endl;
        exit(-1);
    }
    return NULL;
}
//清空文件
void File::clear_file(const char* filename) {
    // 以输出模式打开文件，这会清空文件内容
    ofstream file(filename, ios::out | ios::trunc);
    if (file.is_open()) {
        file.close();
    }
    else {
        cerr << "无法打开文件：" << filename << endl;
        exit(-1);
    }
}
//更新最高成绩
void File::update_highest_score(const GAME_MODES& mode, const long long& score) {
    if (highest_score[mode] >= score)
        return;
    highest_score[mode] = score;
    save_to_file(HIGHEST_SCORE_FILENAME, highest_score, MODE_NUM - 2);
}
void File::read_highest_score() {
    streamsize readnum = read_from_file(HIGHEST_SCORE_FILENAME, highest_score, MODE_NUM - 2);
    if (readnum != (MODE_NUM - 2) * sizeof(long long int))//如果文件里面什么都没有就初始化一下
        reset_highest_score();
}
void File::reset_highest_score()
{
    clear_file(HIGHEST_SCORE_FILENAME);
    for (int i = 0; i < MODE_NUM - 2; i++)
        highest_score[i] = { 0 };
}
//保存历史
void File::save_history(const GAME_MODES& mode, const TCHAR* username, const long long& score)
{
    WCHAR infoText[256];
    _stprintf(infoText, _T("版本:%s 用户名:%s 得分:%lld\n"), GAME_MODE_NAME[mode], username, score);
    save_to_file(GAME_HISTORY_SAVE_FILENAME, infoText, wcslen(infoText) * 1);
    //版本：入门版 用户名：root 得分：100
}
bool File::read_history(int history_num)
{
    if (read_from_file(GAME_HISTORY_SAVE_FILENAME, history, history_num) == NULL)
        return false;
    return true;

    //版本：入门版 用户名：root 得分：100
}
void File::reset_history()
{
    clear_file(GAME_HISTORY_SAVE_FILENAME);
    //// 以输出模式打开文件，这会清空文件内容
    //ofstream file(GAME_HISTORY_SAVE_FILENAME, ios::out | ios::trunc);
    //if (file.is_open()) {
    //    file.close();
    //}
    //else {
    //    cerr << "无法打开文件：" << GAME_HISTORY_SAVE_FILENAME << endl;
    //    exit(-1);
    //}
}