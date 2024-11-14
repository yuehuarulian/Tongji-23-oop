#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include <iostream> 
#include <fstream>
#include <map>
#include "LZ77.h"
//Huffman�ڵ�
typedef struct HuffmanNode {
    Token token;
    int frequency;
    HuffmanNode* left;//����
    HuffmanNode* right;//�Һ���
    HuffmanNode(Token d, int freq = 0, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr) : token(d), frequency(freq), left(l), right(r) {}
    //�ض�������� > ,�������ȶ��н�������
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
}HuffmanNode;

//Huffman��
struct HuffmanTree {
private:
    HuffmanNode* root;
    std::map<Token, std::string> codes;
    //����HuffmanTree
    void createHuffmanTree(std::string tokens);
    //����HuffmanTree����Huffman��
    void buildHuffmanCodes(HuffmanNode* p, std::string code = "");
    //"00101010"ת��char��
    void TurncharFile(const std::string binaryData, std::string& charData);
    std::string incrementBinary(std::string binaryCode);
    //�ͷſռ�ĺ���
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
