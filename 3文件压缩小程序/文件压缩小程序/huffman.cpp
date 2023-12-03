#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <bitset>
#include "huffman.h"

//创建HuffmanTree
void HuffmanTree::createHuffmanTree(const std::string text) 
{
    std::map<char, int> Map;
    for (int i = 0; i < text.size(); i++) {
        Map[text[i]]++;
    }

    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, std::greater<HuffmanNode>> pqueue;
    for (auto& entry : Map) {
        pqueue.push(HuffmanNode(entry.first, entry.second));
    }

    while (pqueue.size() > 1) {
        HuffmanNode* lchild = new HuffmanNode(pqueue.top().data, pqueue.top().frequency, pqueue.top().left, pqueue.top().right);
        pqueue.pop();
        HuffmanNode* rchild = new HuffmanNode(pqueue.top().data, pqueue.top().frequency, pqueue.top().left, pqueue.top().right);
        pqueue.pop();
        HuffmanNode* parent = new HuffmanNode('\0', lchild->frequency + rchild->frequency, lchild, rchild);
        pqueue.push(*parent);
    }
    root->frequency = pqueue.top().frequency;
    //huffmanTree.root = new HuffmanNode('\0', pqueue.top().frequency);
    root->left = pqueue.top().left;
    root->right = pqueue.top().right;
}

//根据HuffmanTree创建Huffman表map codes
void HuffmanTree::buildHuffmanCodes(HuffmanNode* p, std::string code) 
{//dfs
    if (p == nullptr)
        return;
    if (!p->left && !p->right) {
        codes[p->data] = code;
    }
    else {
        buildHuffmanCodes(p->left, code + "0");
        buildHuffmanCodes(p->right, code + "1");
    }
    return;
}
void HuffmanTree::buildHuffmanCodes(std::string &text) 
{
    //除掉\r\n中的\r
    size_t cou;
    int f = 0;
    while ((cou = text.find("\r\n")) != std::string::npos){
        text.erase(cou, 1);
        f = cou;
    }
    std::string s;
    while (1) {
        int cn = text.find_first_of('\0');
        if (cn == 0) {
            text.erase(0, 1);
            break;
        }
        std::string s = text.substr(1, cn - 1);
        codes[text[0]] = s;
        text.erase(0, cn + 1);
    }
}

//zip
void HuffmanTree::encodeText(std::string text,std::string& encodedText) 
{
    //除掉/t
    //改进后
    text.erase(std::remove(text.begin(), text.end(), '\r'), text.end());
    ////改进前
    //size_t cou;
    //int f = 0;
    //while ((cou = text.find('\r', f)) != std::string::npos)
    //{
    //    text.erase(cou, 1);
    //    f = cou + 1;
    //}

    //创建Huffman树
    createHuffmanTree(text);////
    //创建Huffman编码表
    buildHuffmanCodes(root);
    // 用huffman编码编写文件
    std::string t_outputText;/////
    for (char i : text) {
        t_outputText += codes[i];
    }
    //把"01010110100000"写成char
    TurncharFile(t_outputText, encodedText);
}

//uzip
void HuffmanTree::decodeText(std::string text, std::string& decodedText) 
{
    //建立Huffman表
    buildHuffmanCodes(text);
    //把char的字符串翻译成"0010101001"字符串
    std::string t_outputText;
    TurnbinaryFile(text, t_outputText);
    //建树
    for (auto i : codes) {
        HuffmanNode* p = root;
        for (char j : i.second) {
            if (j == '0') {
                if (!p->left){
                    p->left = new HuffmanNode('\0', 0);
                }
                p = p->left;
            }
            else {
                if (!p->right) {
                    p->right = new HuffmanNode('\0', 0);
                }
                p = p->right;
            }
        }
        p->data = i.first;
    }
    HuffmanNode* p = root;
    for (char i : t_outputText) {
        if (i == '0') {
            p = p->left;
        }
        else {
            p = p->right;
        }
        if (!p->left && !p->right) {
            decodedText += p->data;
            p = root;
        }
    }
}

//"00101010"转成char串
void HuffmanTree::TurncharFile(const std::string binaryData, std::string &charData) {
    int cou = 0;
    unsigned char ch = '\0';
    //输出Huffman编码表
    for (auto i : codes) {
        std::cerr << i.first << "    " << i.second << std::endl;
        charData += i.first;
        charData += (i.second + '\0');
    }
    charData += '\0';//\0标志结束
    //输出编码后的文本
    for (char i : binaryData) {
        ch <<= 1;
        ch += i - '0';
        cou++;
        if (cou == 8) {
            charData += ch;
            cou = 0;
            ch &= 0;
        }
    }
    //处理最后不足文本
    ch <<= (8 - cou);//只有前cou位有效
    charData += ch;
    charData += char(8 - cou);//最后一个字节记录无效位数
}

//char的字符串转成"01000010"
void HuffmanTree::TurnbinaryFile(const std::string charData, std::string& binaryData)
{
    int cou = charData[charData.size() - 1];
    for (char i : charData) {
        for (int bit = 7; bit >= 0; --bit) {
            binaryData += ((i >> bit) & 1) ? "1" : "0";
        }
    }
    binaryData.erase(binaryData.size() - cou - 8, cou + 8);
}

//释放空间的函数
void HuffmanTree::Delete_each(HuffmanNode* p) {
    if (p) {
        Delete_each(p->left);
        Delete_each(p->right);
        delete p;
    }
}

//压缩函数
Zip_Uzip_file::Zip_Uzip_file(const char* i, const char* o, const char* b) :inputname(i), outputname(o), order(b)
{
    if (!Openfile()) {
        std::cerr << "Can not open the input file!" << std::endl; // 输出错误信息并退出
        exit;
    }
    if (!strcmp(order, "zip"))//zip
        huffmanTree.encodeText(text, outputText);
    else if (!strcmp(order, "uzip"))//uzip
        huffmanTree.decodeText(text, outputText);
    else
        return;
    if (!Writefile()) {
        std::cerr << "Can not open the output file!" << std::endl;
        exit;
    }
    else {
        std::cout << "Complete!" << std::endl;
    }
}


