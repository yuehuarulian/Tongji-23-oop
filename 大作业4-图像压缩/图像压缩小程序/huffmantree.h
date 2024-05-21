#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include <iostream> 
#include <fstream>
#include <map>
#include "LZ77.h"
//Huffman节点
typedef struct HuffmanNode {
    Token token;
    int frequency;
    HuffmanNode* left;//左孩子
    HuffmanNode* right;//右孩子
    HuffmanNode(Token d, int freq = 0, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr) : token(d), frequency(freq), left(l), right(r) {}
    //重定义操作符 > ,方便优先队列进行排序
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
}HuffmanNode;

//Huffman树
struct HuffmanTree {
private:
    HuffmanNode* root;
    std::map<Token, std::string> codes;
    //创建HuffmanTree
    void createHuffmanTree(std::string tokens);
    //根据HuffmanTree创建Huffman表
    void buildHuffmanCodes(HuffmanNode* p, std::string code = "");
    //"00101010"转成char串
    void TurncharFile(const std::string binaryData, std::string& charData);
    std::string incrementBinary(std::string binaryCode);
    //释放空间的函数
    void Delete_each(HuffmanNode* p);

public:
    HuffmanTree()
    {
        Token token;
        root = new HuffmanNode(token);
    }
    //zip
    void encodeText(std::string tokens, std::string& encodedText);

    ~HuffmanTree()
    {
        Delete_each(root);
    }
};


#endif
