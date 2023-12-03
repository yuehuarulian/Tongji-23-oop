#include "huffmantree.h"
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <bitset>

//创建HuffmanTree
void HuffmanTree::createHuffmanTree(std::string tokens)
{
    std::map<char, int> Map;
    for (const char& token : tokens) {
        Map[token]++;
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
std::string HuffmanTree::incrementBinary(std::string binaryCode) {
    int carry = 1;
    for (int i = binaryCode.length() - 1; i >= 0 && carry; --i) {
        if (binaryCode[i] == '0') {
            binaryCode[i] = '1';
            carry = 0;
        }
        else {
            binaryCode[i] = '0';
            carry = 1;
        }
    }
    if (carry) {
        binaryCode = "1" + binaryCode;
    }
    return binaryCode;
}
void HuffmanTree::encodeText(std::string tokens, std::string& encodedText,int huffman_cou[][2]) {
    createHuffmanTree(tokens);

    buildHuffmanCodes(root);
    //改写范式Huffman
    std::vector<std::pair<char, std::string>> sortedCodes(codes.begin(), codes.end());
    std::sort(sortedCodes.begin(), sortedCodes.end(),
        [](const auto& a, const auto& b) {
            return (a.second.length() == b.second.length()) ? a.second < b.second : a.second.length() < b.second.length();
        });

    int currentLength = 0;
    std::string currentCode;

    for (const auto& entry : sortedCodes) {
        while (entry.second.length() > currentLength) {
            currentLength += 1;
            currentCode = currentCode + "0";
        }
        codes[entry.first] = currentCode;
        huffman_cou[currentLength][0]++;
        if (huffman_cou[currentLength][0] == 1)
            huffman_cou[currentLength][1] = std::stoi(currentCode, nullptr, 2);
        currentCode = incrementBinary(currentCode);
    }
    //生成二进制0101字符串
    std::string binaryText;
    for (const auto& token : tokens) {
        binaryText += codes[token];
    }
    TurncharFile(binaryText, encodedText);
    for (int i = 0; i < 20; i++) {
        encodedText = char(huffman_cou[i][0]) + encodedText;
    }

    for (const auto& entry : sortedCodes) {
        encodedText = entry.first+encodedText;
    }
}
//"00101010"转成char串
void HuffmanTree::TurncharFile(const std::string binaryText, std::string& encodedText) {
    int cou = 0;
    unsigned char ch = '\0';
    ////输出Huffman编码表
    //for (auto i : codes) {
    //    std::cerr << i.first << "    " << i.second << std::endl;
    //    charData += i.first;
    //    charData += (i.second + '\0');
    //}
    //charData += '\0';//\0标志结束
    //输出编码后的文本
    for (char i : binaryText) {
        ch <<= 1;
        ch += i - '0';
        cou++;
        if (cou == 8) {
            encodedText += ch;
            cou = 0;
            ch &= 0;
        }
    }
    //处理最后不足文本            ???
    ch <<= (8 - cou);//只有前cou位有效
    encodedText += ch;

    //charData += char(8 - cou);//最后一个字节记录无效位数
}

////char的字符串转成"01000010"
//void HuffmanTree::TurnbinaryFile(const std::string charData, std::string& binaryData)
//{
//    int cou = charData[charData.size() - 1];
//    for (char i : charData) {
//        for (int bit = 7; bit >= 0; --bit) {
//            binaryData += ((i >> bit) & 1) ? "1" : "0";
//        }
//    }
//    binaryData.erase(binaryData.size() - cou - 8, cou + 8);
//}

//释放空间的函数
void HuffmanTree::Delete_each(HuffmanNode* p) {
    if (p) {
        Delete_each(p->left);
        Delete_each(p->right);
        delete p;
    }
}



