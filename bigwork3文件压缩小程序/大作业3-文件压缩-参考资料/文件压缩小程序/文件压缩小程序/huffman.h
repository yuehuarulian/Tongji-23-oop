#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H
typedef struct HuffmanNode {
    char data;
    int frequency;
    //unsigned int parent, lchild, rchild;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int freq, HuffmanNode* l = nullptr, HuffmanNode* r = nullptr) : data(d), frequency(freq), left(l), right(r) {}
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
}HuffmanNode;

typedef struct HuffmanTree {
private:
    HuffmanNode* root;
    std::map<char, std::string> codes;
    void createHuffmanTree(const std::string text);
    void buildHuffmanCodes(HuffmanNode* p, std::string code = "");
    void buildHuffmanCodes(std::string& text);
    void TurncharFile(const std::string binaryData, std::string& charData);
    void TurnbinaryFile(const std::string charData, std::string& binaryData);
    void Delete_each(HuffmanNode* p);
public:
    HuffmanTree(char data, int freq) 
    {
        root = new HuffmanNode(data, freq);
    }
    void encodeText(std::string text, std::string& encodedText);
    void decodeText(std::string text, std::string& decodedText);
    void Delete() 
    {
        Delete_each(root);
    }
}HuffmanTree;

struct Zip_Uzip_file {
private:
    std::string filepace;
    std::string inputname;
    std::string outputname;
    bool zip;
public:
    Zip_Uzip_file(std::string f, std::string i, std::string o) :filepace(f), inputname(i), outputname(i)
    {

    }
};

#endif