#include "huffman.h"
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <bitset>

//创建HuffmanTree
void HuffmanTree::createHuffmanTree(const std::vector<Token> tokens)
{
    std::map<Token, int> Map;
    for (const auto& token : tokens) {
        Map[token]++;
    }

    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, std::greater<HuffmanNode>> pqueue;
    for (auto& entry : Map) {
        pqueue.push(HuffmanNode(entry.first, entry.second));
    }

    while (pqueue.size() > 1) {
        HuffmanNode* lchild = new HuffmanNode(pqueue.top().token, pqueue.top().frequency, pqueue.top().left, pqueue.top().right);
        pqueue.pop();
        HuffmanNode* rchild = new HuffmanNode(pqueue.top().token, pqueue.top().frequency, pqueue.top().left, pqueue.top().right);
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
        codes[p->token] = code;
    }
    else {
        buildHuffmanCodes(p->left, code + "0");
        buildHuffmanCodes(p->right, code + "1");
    }
    return;
}
//void HuffmanTree::buildHuffmanCodes(std::string& text)
//{
//    //除掉\r\n中的\r
//    size_t cou;
//    int f = 0;
//    while ((cou = text.find("\r\n")) != std::string::npos) {
//        text.erase(cou, 1);
//        f = cou;
//    }
//    std::string s;
//    while (1) {
//        int cn = text.find_first_of('\0');
//        if (cn == 0) {
//            text.erase(0, 1);
//            break;
//        }
//        std::string s = text.substr(1, cn - 1);
//        codes[text[0]] = s;
//        text.erase(0, cn + 1);
//    }
//}



//uzip
//void HuffmanTree::decodeText(std::string text, std::string& decodedText)
//{
//    //建立Huffman表
//    buildHuffmanCodes(text);
//    //把char的字符串翻译成"0010101001"字符串
//    std::string t_outputText;
//    TurnbinaryFile(text, t_outputText);
//    //建树
//    for (auto i : codes) {
//        HuffmanNode* p = root;
//        for (char j : i.second) {
//            if (j == '0') {
//                if (!p->left) {
//                    p->left = new HuffmanNode('\0', 0);
//                }
//                p = p->left;
//            }
//            else {
//                if (!p->right) {
//                    p->right = new HuffmanNode('\0', 0);
//                }
//                p = p->right;
//            }
//        }
//        p->data = i.first;
//    }
//    HuffmanNode* p = root;
//    for (char i : t_outputText) {
//        if (i == '0') {
//            p = p->left;
//        }
//        else {
//            p = p->right;
//        }
//        if (!p->left && !p->right) {
//            decodedText += p->data;
//            p = root;
//        }
//    }
//}

//"00101010"转成char串
void HuffmanTree::TurncharFile(const std::string binaryData, std::string& charData) {
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
    //处理最后不足文本            ???
    ch <<= (8 - cou);//只有前cou位有效
    charData += ch;
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



