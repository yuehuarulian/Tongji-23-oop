#include "Png.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <string>
//#include <zlib.h>  // 用于 CRC32 校验

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
    // 写入 PNG 文件
    writePNGFile("output.png");
}
unsigned char Png::paeth_predictor(unsigned char a, unsigned char b, unsigned char c) {
    int p = a + b - c;
    int pa = std::abs(p - a);
    int pb = std::abs(p - b);
    int pc = std::abs(p - c);

    // 选择最小绝对差的方向作为预测值
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
        std::cout << "申请内存失败" << std::endl;
        exit(1);
    }
    memset(currentFilter_PAETH, 0, (size_t)x * y * 4);
    // 应用过滤器
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

    //// 计算绝对差和
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
    //// 更新最小和及其对应的过滤器
    //if (sum < minSum) {
    //    minSum = sum;
    //    for (int row = 0; row < numRows; ++row) {
    //        for (int col = 0; col < numCols; ++col) {
    //            minFilter[row][col] = currentFilter[row][col];
    //        }
    //    }
    //}


}
// 创建 PNG 文件头
void Png::createPNGHeader() {
    // PNG 文件头
    header = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

    // IHDR 块（图像头块）
    header.insert(header.end(), {
        0x00, 0x00, 0x00, 0x0D,  // IHDR 块长度
        0x49, 0x48, 0x44, 0x52,  // IHDR 类型标识
        });

    // 图像宽度和高度
    header.push_back((y >> 24) & 0xFF);
    header.push_back((y >> 16) & 0xFF);
    header.push_back((y >> 8) & 0xFF);
    header.push_back(y & 0xFF);

    header.push_back((x >> 24) & 0xFF);
    header.push_back((x >> 16) & 0xFF);
    header.push_back((x >> 8) & 0xFF);
    header.push_back(x & 0xFF);

    header.insert(header.end(), {
        0x08,  // 位深度：8 位/通道
        0x06,  // 色彩类型：RGBA
        0x00,  // 压缩方法：0（deflate 压缩）
        0x05,  // 滤波方法：
        0x00,  // 隔行扫描：0（无隔行扫描）
        });

    //// CRC32 校验
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
    0x49, 0x44, 0x41, 0x54,  // IDAT 类型标识
        });

}
// 写入 PNG 文件
void Png::writePNGFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    // 写入 PNG 文件头
    createPNGHeader();
    file.write(reinterpret_cast<const char*>(header.data()), header.size());
    // 写入压缩后的数据
    file.write(encodePicture.c_str(), encodePicture.size());
    file.close();
}



