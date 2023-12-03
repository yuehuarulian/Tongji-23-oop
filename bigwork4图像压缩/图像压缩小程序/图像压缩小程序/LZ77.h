#ifndef LZ77
#define LZ77
#include <iostream>
#include <string>
#include <vector>

struct Token {
    bool isLiteral; // �Ƿ�Ϊ�����ַ�
    char literal;   // �����ַ�
    int offset;     // ָ��ƫ��
    int length;     // ƥ�䳤��

    Token(bool isLit, char lit) : isLiteral(isLit), literal(lit), offset(0), length(0) {}
    Token(int off, int len) : isLiteral(false), literal('\0'), offset(off), length(len) {}
   
};
struct Lz77 {
    void compress(const std::string& input, int windowSize, int bufferSize) {
        int currentIndex = 0;
        while (currentIndex < input.size()) {
            int bestOffset = 0;
            int bestLength = 0;
            for (int offset = 1; offset <= windowSize && currentIndex - offset >= 0; ++offset) {
                int length = 0;

                while (length < bufferSize && currentIndex + length < input.size() && input[currentIndex - offset + length] == input[currentIndex + length]) {
                    ++length;
                }

                if (length > bestLength) {
                    bestLength = length;
                    bestOffset = offset;
                }
            }

            if (bestLength > 2) {
                compressed.emplace_back(bestOffset, bestLength);
                currentIndex += bestLength;
            }
            else {
                compressed.emplace_back(true, input[currentIndex]);
                ++currentIndex;
            }
        }
        convertTokensToBinaryString();
    }
    void convertTokensToBinaryString() {

        //for (const Token& token : compressed) {
        //    // �� offset ת��Ϊ�����Ʊ��ش�
        //    binaryString += std::to_string(token.offset);
        //    // �� length ת��Ϊ�����Ʊ��ش�
        //    binaryString += std::to_string(token.length);
        //    // �� nextChar ת��Ϊ�����Ʊ��ش�
        //    binaryString += token.nextChar;
        //}
    }
    std::string binaryString;
    std::vector<Token> compressed;
};
//std::string decompressLZSS(const std::vector<Token>& compressed) {
//    std::string decompressed;
//
//    for (const Token& token : compressed) {
//        if (token.isLiteral) {
//            decompressed += token.literal;
//        }
//        else {
//            int start = static_cast<int>(decompressed.size()) - token.offset;
//            for (int i = 0; i < token.length; ++i) {
//                decompressed += decompressed[start + i];
//            }
//        }
//    }
//
//    return decompressed;
//}
#endif