#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream> 
#include <fstream>
#include <map>
//Huffman节点
typedef struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;//左孩子
    HuffmanNode* right;//右孩子
    HuffmanNode(char d, int freq, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr) : data(d), frequency(freq), left(l), right(r) {}
    //重定义操作符 > ,方便优先队列进行排序
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
}HuffmanNode;

//Huffman树
typedef struct HuffmanTree {
private:
    HuffmanNode* root;
    std::map<char, std::string> codes;
    //创建HuffmanTree
    void createHuffmanTree(const std::string text);
    //根据HuffmanTree创建Huffman表
    void buildHuffmanCodes(HuffmanNode* p, std::string code = "");
    void buildHuffmanCodes(std::string& text);
    //"00101010"转成char串
    void TurncharFile(const std::string binaryData, std::string& charData);
    //char的字符串转成"01000010"
    void TurnbinaryFile(const std::string charData, std::string& binaryData);
    //释放空间的函数
    void Delete_each(HuffmanNode* p);
public:
    HuffmanTree(char data = '\0', int freq = 0)
    {
        root = new HuffmanNode(data, freq);
    }
    //zip
    void encodeText(std::string text, std::string& encodedText);
    //uzip
    void decodeText(std::string text, std::string& decodedText);
    ~HuffmanTree()
    {
        Delete_each(root);
    }
}HuffmanTree;

//压缩
struct Zip_Uzip_file {
private:
    //文件名
    const char* inputname;
    const char* outputname;
    const char* order;
    //文件内容存放在text中
    std::string text;
    //输出内容存放在outputText中
    std::string t_outputText, outputText;
    // 建立HuffmanTree对象并生成outputText
    HuffmanTree huffmanTree;
    bool Openfile()//读取文件，成功返回1，失败返回0
    {
        std::ifstream fin(inputname, std::ios::binary); // 以二进制方式打开文件
        if (!fin)
            return 0;
        std::istreambuf_iterator<char> beg(fin), end; // 设置两个文件指针，指向开始和结束，以 char(一字节) 为步长
        std::string t(beg, end); // 将文件全部读入 string 字符串
        text = t;
        fin.close(); // 操作完文件后关闭文件句柄是一个好习惯
        return 1;
    }
    bool Writefile()
    {
        //文件输出
        std::ofstream fout(outputname, std::ios::out); // 打开输出文件
        if (!fout)
            return 0;
        fout << outputText; // 直接将操作好的字符串进行输出
        fout.close();
        return 1;
    }
public:
    Zip_Uzip_file(const char* i, const char* o, const char* b);
};

#endif