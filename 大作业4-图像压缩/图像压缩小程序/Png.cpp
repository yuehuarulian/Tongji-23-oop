#include "Png.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <string>
//#include <zlib.h>  // ���� CRC32 У��

void Png::Zip()
{
    Filtering();
    std::string str;
    for (long long int i = 0; i < 4*x*y; ++i) {
        str = str + char(currentFilter_PAETH[i]);
    }
    Lz77 lz(str);
    lz.compress();
    HuffmanTree huffman;
    huffman.encodeText(lz.binaryString, encodePicture);
    // д�� PNG �ļ�
    writePNGFile("output.png");
}
unsigned char Png::paeth_predictor(unsigned char a, unsigned char b, unsigned char c) {
    int p = a + b - c;
    int pa = std::abs(p - a);
    int pb = std::abs(p - b);
    int pc = std::abs(p - c);

    // ѡ����С���Բ�ķ�����ΪԤ��ֵ
    if (pa <= pb && pa <= pc) {
        return a;
    }
    else if (pb <= pc) {
        return b;
    }
    else {
        return c;
    }
}
void Png::Filtering()
{
    /// <summary>
    /// 
    /// </summary>
    //for (int row = 0; row < 9; ++row) {
    //    for (int col = 0; col < 9; ++col) {
    //        int index = row * y * 4 + col * 4;
    //        std::cout << int(data[index]) << ' ';
    //        //std::cout << int(data[index + 1]) << ' ';
    //        //std::cout << int(data[index + 2]) << ' ';
    //        //std::cout << int(data[index + 3]) << ' ';
    //    }
    //    std::cout << std::endl;
    //}
    currentFilter_PAETH = new(std::nothrow) BYTE[(size_t)x * y * 4];
    if (currentFilter_PAETH == NULL) {
        std::cout << "�����ڴ�ʧ��" << std::endl;
        exit(1);
    }
    memset(currentFilter_PAETH, 0, (size_t)x * y * 4);
    // Ӧ�ù�����
    // PAETH X-L
    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
            int index = row * y * 4 + col * 4;
            int index_U = (row - 1) * y * 4 + col * 4;
            int index_L = row * y * 4 + (col - 1) * 4;
            int index_UL = (row - 1) * y * 4 + (col - 1) * 4;
            currentFilter_PAETH[index] = ((col == 0 || row == 0) ? data[index] : data[index] -
                paeth_predictor(data[index_U], data[index_L], data[index_UL]));//r
            currentFilter_PAETH[index + 1] = ((col == 0 || row == 0) ? data[index + 1] : data[index + 1] -
                paeth_predictor(data[index_U + 1], data[index_L + 1], data[index_UL + 1]));//g
            currentFilter_PAETH[index + 2] = ((col == 0 || row == 0) ? data[index + 2] : data[index + 2] -
                paeth_predictor(data[index_U + 2], data[index_L + 2], data[index_UL + 2]));//b
            currentFilter_PAETH[index + 3] = ((col == 0 || row == 0) ? data[index + 3] : data[index + 3] -
                paeth_predictor(data[index_U + 3], data[index_L + 3], data[index_UL + 3]));//a
        }
    }
    //std::cout << std::endl;
    //std::cout << std::endl;
    //for (int row = 0; row < 9; ++row) {
    //    for (int col = 0; col < 9; ++col) {
    //        int index = row * y * 4 + col * 4;
    //        std::cout << int(currentFilter_PAETH[index]) << ' ';
    //        //std::cout << int(currentFilter_PAETH[index + 1]) << ' ';
    //        //std::cout << int(currentFilter_PAETH[index + 2]) << ' ';
    //        //std::cout << int(currentFilter_PAETH[index + 3]) << ' ';
    //    }
    //    std::cout << std::endl;
    //}

    //// ������Բ��
    //int sum = 0;
    //for (int row = 0; row < x; ++row) {
    //    for (int col = 0; col < y; ++col) {
    //        int index = row * y * 4 + col * 4;
    //        sum += std::abs(currentFilter_SUB[index]);
    //        sum += std::abs(currentFilter_SUB[index + 1]);
    //        sum += std::abs(currentFilter_SUB[index + 2]);
    //        sum += std::abs(currentFilter_SUB[index + 3]);
    //    }
    //}
    //// ������С�ͼ����Ӧ�Ĺ�����
    //if (sum < minSum) {
    //    minSum = sum;
    //    for (int row = 0; row < numRows; ++row) {
    //        for (int col = 0; col < numCols; ++col) {
    //            minFilter[row][col] = currentFilter[row][col];
    //        }
    //    }
    //}


}
// ���� PNG �ļ�ͷ
void Png::createPNGHeader() {
    // PNG �ļ�ͷ
    header = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

    // IHDR �飨ͼ��ͷ�飩
    header.insert(header.end(), {
        0x00, 0x00, 0x00, 0x0D,  // IHDR �鳤��
        0x49, 0x48, 0x44, 0x52,  // IHDR ���ͱ�ʶ
        });

    // ͼ���Ⱥ͸߶�
    header.push_back((y >> 24) & 0xFF);
    header.push_back((y >> 16) & 0xFF);
    header.push_back((y >> 8) & 0xFF);
    header.push_back(y & 0xFF);

    header.push_back((x >> 24) & 0xFF);
    header.push_back((x >> 16) & 0xFF);
    header.push_back((x >> 8) & 0xFF);
    header.push_back(x & 0xFF);

    header.insert(header.end(), {
        0x08,  // λ��ȣ�8 λ/ͨ��
        0x06,  // ɫ�����ͣ�RGBA
        0x00,  // ѹ��������0��deflate ѹ����
        0x05,  // �˲�������
        0x00,  // ����ɨ�裺0���޸���ɨ�裩
        });

    //// CRC32 У��
    //unsigned long crc = crc32(0L, Z_NULL, 0);
    //crc = crc32(crc, &header[12], 17);
    //header.push_back((crc >> 24) & 0xFF);
    //header.push_back((crc >> 16) & 0xFF);
    //header.push_back((crc >> 8) & 0xFF);
    //header.push_back(crc & 0xFF);

    //IDAT 
    unsigned long Size = encodePicture.size();
    header.push_back((Size >> 24) & 0xFF);
    header.push_back((Size >> 16) & 0xFF);
    header.push_back((Size >> 8) & 0xFF);
    header.push_back(Size & 0xFF);
    header.insert(header.end(), {
    0x49, 0x44, 0x41, 0x54,  // IDAT ���ͱ�ʶ
        });

}
// д�� PNG �ļ�
void Png::writePNGFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    // д�� PNG �ļ�ͷ
    createPNGHeader();
    file.write(reinterpret_cast<const char*>(header.data()), header.size());
    // д��ѹ���������
    file.write(encodePicture.c_str(), encodePicture.size());
    file.close();
}



