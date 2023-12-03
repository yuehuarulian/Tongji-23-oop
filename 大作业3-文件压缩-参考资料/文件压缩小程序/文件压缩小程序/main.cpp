#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include "huffman.h"
using namespace std;

int main(int argc, char* argv[]) 
{
    //技术开始
    auto starttime = chrono::high_resolution_clock::now();
    cout << "Zipper 0.001! Author: root" << endl;
    if (argc != 4) {
        cerr << "Please make sure the number of parameters is correct." << endl;
        return -1;
    }
    if (strcmp(argv[3], "zip") && strcmp(argv[3], "uzip")) {
        cerr << "Unknown parameter!\nCommand list:\nzip" << endl;
        return -1;
    }
    ifstream fin(argv[1], ios::binary); // 以二进制方式打开文件
    if (!fin) {
        cerr << "Can not open the input file!" << endl; // 输出错误信息并退出
        return -1;
    }
    istreambuf_iterator<char> beg(fin),end; // 设置两个文件指针，指向开始和结束，以 char(一字节) 为步长
    string text(beg, end); // 将文件全部读入 string 字符串
    fin.close(); // 操作完文件后关闭文件句柄是一个好习惯

    // 建立HuffmanTree对象并生成outputText
    HuffmanTree huffmanTree('\0', 0);
    string t_outputText, outputText;
    if (!strcmp(argv[3], "zip"))//zip
        huffmanTree.encodeText(text, outputText);
    else //uzip
        huffmanTree.decodeText(text, outputText);
    huffmanTree.Delete();//手动delet一下防止析构函数出各种问题

    //文件输出
    ofstream fout(argv[2]); // 打开输出文件
    if (!fout) {
        cerr << "Can not open the output file!" << endl;
        return -1;
    }
    fout << outputText; // 直接将操作好的字符串进行输出
    fout.close();
    cout << "Complete!" << endl;

    //记录时间
    auto endtime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<chrono::microseconds>(endtime - starttime);
    cout << "运行时间: " << double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den << " 秒" << std::endl;
    return 0;
}