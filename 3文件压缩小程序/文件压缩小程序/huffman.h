#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream> 
#include <fstream>
#include <map>
//Huffman�ڵ�
typedef struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;//����
    HuffmanNode* right;//�Һ���
    HuffmanNode(char d, int freq, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr) : data(d), frequency(freq), left(l), right(r) {}
    //�ض�������� > ,�������ȶ��н�������
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
}HuffmanNode;

//Huffman��
typedef struct HuffmanTree {
private:
    HuffmanNode* root;
    std::map<char, std::string> codes;
    //����HuffmanTree
    void createHuffmanTree(const std::string text);
    //����HuffmanTree����Huffman��
    void buildHuffmanCodes(HuffmanNode* p, std::string code = "");
    void buildHuffmanCodes(std::string& text);
    //"00101010"ת��char��
    void TurncharFile(const std::string binaryData, std::string& charData);
    //char���ַ���ת��"01000010"
    void TurnbinaryFile(const std::string charData, std::string& binaryData);
    //�ͷſռ�ĺ���
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

//ѹ��
struct Zip_Uzip_file {
private:
    //�ļ���
    const char* inputname;
    const char* outputname;
    const char* order;
    //�ļ����ݴ����text��
    std::string text;
    //������ݴ����outputText��
    std::string t_outputText, outputText;
    // ����HuffmanTree��������outputText
    HuffmanTree huffmanTree;
    bool Openfile()//��ȡ�ļ����ɹ�����1��ʧ�ܷ���0
    {
        std::ifstream fin(inputname, std::ios::binary); // �Զ����Ʒ�ʽ���ļ�
        if (!fin)
            return 0;
        std::istreambuf_iterator<char> beg(fin), end; // ���������ļ�ָ�룬ָ��ʼ�ͽ������� char(һ�ֽ�) Ϊ����
        std::string t(beg, end); // ���ļ�ȫ������ string �ַ���
        text = t;
        fin.close(); // �������ļ���ر��ļ������һ����ϰ��
        return 1;
    }
    bool Writefile()
    {
        //�ļ����
        std::ofstream fout(outputname, std::ios::out); // ������ļ�
        if (!fout)
            return 0;
        fout << outputText; // ֱ�ӽ������õ��ַ����������
        fout.close();
        return 1;
    }
public:
    Zip_Uzip_file(const char* i, const char* o, const char* b);
};

#endif