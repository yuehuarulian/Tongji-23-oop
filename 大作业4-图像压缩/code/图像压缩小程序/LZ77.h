#ifndef LZ77
#define LZ77
#define _CRT_SECURE_NO_WARNINGS
#include "PicReader.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <vector>
#include <bitset>

struct Token {
    int offset;
    int length;
    char nextChar;
    Token(int o = 0, int l = 0, char n = '\0') :offset(o), length(l), nextChar(n) {}
    // �Ƚ������
    bool operator<(const Token& other) const {
        if (this->offset != other.offset) {
            return this->offset < other.offset;
        }
        else if (this->length != other.length) {
            return this->length < other.length;
        }
        else {
            return this->nextChar < other.nextChar;
        }
    }
};
class Lz77 {
public:
    Lz77(std::string str) : input(str) {}
    void compress()
    {
        int currentIndex = 0;
        while (currentIndex < input.size()) {
            //��ʼ����ǰToken����ʼʱû��ƥ��
            Token token;
            token.nextChar = input[currentIndex + token.length]; 
            //�ӵ�ǰλ����ǰ�������ҵ��뵱ǰ�ַ�ƥ�����Ӵ���
            for (int i = min(currentIndex, windowSize); i > 0; --i) {
                int windowIndex = currentIndex - i;
                int bufferIndex = currentIndex;
                int matchLength = 0;

                while (bufferIndex < input.size() && matchLength < bufferSize && input[windowIndex] == input[bufferIndex]) {
                    ++windowIndex;
                    ++bufferIndex;
                    ++matchLength;
                }

                if (matchLength > token.length) {
                    token.offset = i;
                    token.length = matchLength;
                    token.nextChar = input[currentIndex + token.length];
                }
            }
            //��Token��ӵ�ѹ��������
            compressedData.push_back(token);
            currentIndex += (token.length + 1);
        }
        convertTokensToBinaryString();
    }
    std::vector<Token> compressedData;
    std::string binaryString;
    // �� Token �ṹ��ת��Ϊ�����Ʊ��ش�
    void convertTokensToBinaryString() {
        std::string binaryString;

        for (const Token& token : compressedData) {
            // �� offset ת��Ϊ�����Ʊ��ش�
            binaryString += std::to_string(token.offset);
            // �� length ת��Ϊ�����Ʊ��ش�
            binaryString += std::to_string(token.length);
            // �� nextChar ת��Ϊ�����Ʊ��ش�
            binaryString += token.nextChar;
        }
    }
    //std::string decompressLZ77(const std::vector<Token>& compressedData) {
    //    std::string decompressedData;
    //
    //    for (const auto& token : compressedData) {
    //        int startIndex = decompressedData.size() - token.offset;
    //        for (int i = 0; i < token.length; ++i) {
    //            decompressedData.push_back(decompressedData[startIndex + i]);
    //        }
    //        decompressedData.push_back(token.nextChar);
    //    }
    //
    //    return decompressedData;
    //}

private:
    const int windowSize = 15;  // Adjust the window size as needed  max:32768
    const int bufferSize = 4;   // Adjust the buffer size as needed
    std::string input;
};
//int main() {
//    // Replace this string with your actual image data
//    std::string imageData = "your_image_data_here";
//
//    // Compress the image data
//    std::vector<Token> compressedData = compressLZ77(imageData);
//
//    // Decompress the image data
//    std::string decompressedData = decompressLZ77(compressedData);
//
//    // Display the results (compare original and decompressed data)
//    std::cout << "Original Size: " << imageData.size() << " bytes\n";
//    std::cout << "Compressed Size: " << compressedData.size() * sizeof(Token) << " bytes\n";
//    std::cout << "Decompressed Size: " << decompressedData.size() << " bytes\n";
//
//    return 0;
//}

#endif
