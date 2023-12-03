#include"Jpeg.h"
#include <iostream>
#include <cmath>
#include <iostream>
#include <cmath>
#include <stdio.h>

// 打开文件，分配内存
Jpeg::Jpeg(const char* file)
{
    PicReader imread;
    imread.readPic(file);
    imread.getData(data, x, y);
    ycbcr = new YCbCr[x * y / 64];
    if (ycbcr == NULL) {
        std::cout << "分配内存失败" << std::endl;
        exit(1);
    }
    zigzag = new zigzagArray[x * y / 64];
    if (zigzag == NULL) {
        std::cout << "分配内存失败" << std::endl;
        exit(1);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int t = zigzagOrder[i * 8 + j];
            m_YTable[t / 8][t % 8] = luminanceQuantizationTable[i][j];
            m_CbCrTable[t / 8][t % 8] = chrominanceQuantizationTable[i][j];
        }
    }
}

// delete
Jpeg::~Jpeg()
{
    delete[] data;
    data = nullptr;
    delete[] ycbcr;
    delete[] zigzag;
}

//RGBA转换YCbCr
void Jpeg::RGBtoYCbCr(int row, int col)
{
    // 对 8x8 的图像块进行处理
    for (int blockY = 0; blockY < blockSize; ++blockY) {
        for (int blockX = 0; blockX < blockSize; ++blockX) {
            unsigned int currentX = col + blockX;
            unsigned int currentY = row + blockY;

            // 处理当前像素
            if (currentX < x && currentY < y) {
                Pixel currentPixel(data[currentY * y * 4 + currentX * 4],
                    data[currentY * y * 4 + currentX * 4 + 1],
                    data[currentY * y * 4 + currentX * 4 + 2],
                    data[currentY * y * 4 + currentX * 4 + 3]);
                // 进行颜色空间转换
                ycbcr[row / blockSize * x_ycbcr + col / blockSize].Y[blockY][blockX] = 0.29871 * currentPixel.R + 0.58661 * currentPixel.G + 0.11448 * currentPixel.B - 128;
                ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cb[blockY][blockX] = -0.168736 * currentPixel.R - 0.331264 * currentPixel.G + 0.5 * currentPixel.B;
                ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cr[blockY][blockX] = 0.5 * currentPixel.R - 0.418688 * currentPixel.G - 0.081312 * currentPixel.B;
            }
        }
    }
}

// 定义 DCT 转换矩阵
const double Jpeg::alpha_u(int u) {
    return (u == 0) ? 1.0 / std::sqrt(2) : 1.0;
}
const double Jpeg::alpha_v(int v) {
    return (v == 0) ? 1.0 / std::sqrt(2) : 1.0;
}
// 执行离散余弦变换 (DCT)
void Jpeg::performDCT(double block[blockSize][blockSize]) {
    double result[blockSize][blockSize] = { 0.0 };

    for (int u = 0; u < blockSize; ++u) {
        for (int v = 0; v < blockSize; ++v) {
            double sum = 0.0;

            for (int x = 0; x < blockSize; ++x) {
                for (int y = 0; y < blockSize; ++y) {
                    sum += block[x][y] * std::cos((2.0 * x + 1.0) * u * M_PI / 16.0) *
                        std::cos((2.0 * y + 1.0) * v * M_PI / 16.0);
                }
            }
            result[u][v] = 0.25 * alpha_u(u) * alpha_v(v) * sum;
        }
    }

    // 将结果复制回原始图像块
    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            block[i][j] = result[i][j];
        }
    }
}

// 量化
void Jpeg::quantizeDCT(double block[blockSize][blockSize], const char quantizationTable[blockSize][blockSize]) {
    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            block[i][j] = std::round(block[i][j] / quantizationTable[i][j]);
            //std::cout << block[i][j] << "  ";
        }
        //std::cout << std::endl;
    }
    //std::cout << std::endl;
}
// 将量化后的 DCT 系数按照螺旋扫描顺序转换为一维数组
void Jpeg::zigzagScan(double block[blockSize][blockSize], int zigzagArray[blockSize * blockSize]) {
    for (int i = 0; i < blockSize * blockSize; ++i) {
        zigzagArray[zigzagOrder[i]] = int(block[i / blockSize][i % blockSize]);
    }
    //for (int i = 0; i < 64; i++) {
    //    std::cout << zigzagArray[i] << " ";
    //}
    //std::cout << std::endl;
}

// 主操作函数
void Jpeg::Zip(const char* outputfile)
{
    f = fopen(outputfile, "wb");
    if (f == nullptr) {
        // 文件打开失败，处理错误
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }
    //文件头
    _write_jpeg_header();
    // JPEG 图像分割
    x_ycbcr = x / blockSize;
    y_ycbcr = y / blockSize;
    int prev_DC_Y = 0, prev_DC_Cb = 0, prev_DC_Cr = 0;
    int newByte = 0, newBytePos = 7;

    for (unsigned int row = 0; row < x; row += blockSize) {
        for (unsigned int col = 0; col < y; col += blockSize) {
            //分割 RGBtoYCbCr转换
            RGBtoYCbCr(row, col);
            // DCT
            performDCT(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Y);
            performDCT(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cb);
            performDCT(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cr);
            // 量化
            quantizeDCT(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Y, m_YTable);
            quantizeDCT(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cb, m_CbCrTable);
            quantizeDCT(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cr, m_CbCrTable);
            // 使用螺旋扫描将二维数组转换为一维数组
            zigzagScan(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Y, zigzag[row / blockSize * x_ycbcr + col / blockSize].Y);
            zigzagScan(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cb, zigzag[row / blockSize * x_ycbcr + col / blockSize].Cb);
            zigzagScan(ycbcr[row / blockSize * x_ycbcr + col / blockSize].Cr, zigzag[row / blockSize * x_ycbcr + col / blockSize].Cr);

            //for (int i = 0; i < 8; i++)
            //{
            //    for (int j = 0; j < 8; j++) {
            //        std::cout << zigzag[row / 8 * x_ycbcr + col / 8].Y[i * 8 + j] << ' ';
            //    }
            //    std::cout << std::endl;
            //}
            //std::cout << std::endl;
            //哈夫曼编码
            BitString outputBitString[128];
            int bitStringCounts;

            huffmancode.encode(zigzag[row / blockSize * x_ycbcr + col / blockSize].Y, prev_DC_Y, huffmancode.m_Y_DC_Huffman_Table, huffmancode.m_Y_AC_Huffman_Table, outputBitString, bitStringCounts);
            write_bitstring(outputBitString, bitStringCounts, newByte, newBytePos);
            huffmancode.encode(zigzag[row / blockSize * x_ycbcr + col / blockSize].Cb, prev_DC_Cb, huffmancode.m_CbCr_DC_Huffman_Table, huffmancode.m_CbCr_AC_Huffman_Table, outputBitString, bitStringCounts);
            write_bitstring(outputBitString, bitStringCounts, newByte, newBytePos);
            huffmancode.encode(zigzag[row / blockSize * x_ycbcr + col / blockSize].Cr, prev_DC_Cr, huffmancode.m_CbCr_DC_Huffman_Table, huffmancode.m_CbCr_AC_Huffman_Table, outputBitString, bitStringCounts);
            write_bitstring(outputBitString, bitStringCounts, newByte, newBytePos);

        }
    }
    _write_word_(0xFFD9); 
    fclose(f);
}

//hafuman编码写入
void Jpeg::write_bitstring(const BitString* bs, int counts, int& newByte, int& newBytePos)
{
    unsigned short mask[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768 };
    // 遍历 Huffman 编码后的位字符串数组
    for (int i = 0; i < counts; i++) {
        int value = bs[i].value;  // 获取当前位字符串的值
        int posval = bs[i].length - 1;  // 获取当前位字符串的长度
        // 逐位处理当前位字符串的值
        while (posval >= 0) {
            // 使用掩码检查当前位是否为1
            if ((value & mask[posval]) != 0) {
                // 将 newByte 对应的位设置为1
                newByte = newByte | mask[newBytePos];
            }
            posval--;
            newBytePos--;

            // 如果当前字节已满，将当前字节写入文件
            if (newBytePos < 0) {
                //_write_byte_((unsigned char)(newByte));
                fwrite((unsigned char*)(&newByte), 1, 1, f);
                // 处理特殊情况，如果当前字节为 0xFF，插入一个 0x00 字节
                if (newByte == 0xFF) {
                    //_write_byte_((unsigned char)(0x00));
                    char a = '\0';
                    fwrite(&a, 1, 1, f);
                }
                // 重新初始化
                newBytePos = 7;
                newByte = 0;
            }
        }
    }
}

//文件头写入
void Jpeg::_write_jpeg_header()
{
    //SOI
    _write_word_(0xFFD8);		// marker = 0xFFD8

    //APPO JFIF
    _write_word_(0xFFE0);		// marker = 0xFFE0
    _write_word_(16);			// length = 16 for usual JPEG, no thumbnail
    _write_("JFIF", 5);			// 'JFIF\0'
    _write_byte_(1);			// version_hi
    _write_byte_(1);			// version_low
    _write_byte_(0);			// xyunits = 0 no units, normal density
    _write_word_(1);			// xdensity
    _write_word_(1);			// ydensity
    _write_byte_(0);			// thumbWidth
    _write_byte_(0);			// thumbHeight

    //DQT:一个或者多个量化表(Difine Quantization Table)
    _write_word_(0xFFDB);		//marker = 0xFFDB
    _write_word_(132);			//size=132
    _write_byte_(0);			//QTYinfo== 0: (table for Y) 
    //              bit 0..3: number of QT = 0 
    //				bit 4..7: precision of QT
    //				bit 8	: 0
    _write_(m_YTable, 64);		//YTable
    _write_byte_(1);			//QTCbinfo = 1 (quantization table for Cb,Cr)
    _write_(m_CbCrTable, 64);	//CbCrTable

    //SOFO
    _write_word_(0xFFC0);			//marker = 0xFFC0
    _write_word_(17);				//length = 17 for a truecolor YCbCr JPG
    _write_byte_(8);				//precision = 8: 8 bits/sample 
    _write_word_(y & 0xFFFF);	//height
    _write_word_(x & 0xFFFF);	//width
    _write_byte_(3);				//nrofcomponents = 3: We encode a truecolor JPG

    _write_byte_(1);				//IdY = 1
    _write_byte_(0x11);				//HVY sampling factors for Y (bit 0-3 vert., 4-7 hor.)(SubSamp 1x1)
    _write_byte_(0);				//QTY  Quantization Table number for Y = 0

    _write_byte_(2);				//IdCb = 2
    _write_byte_(0x11);				//HVCb = 0x11(SubSamp 1x1)
    _write_byte_(1);				//QTCb = 1

    _write_byte_(3);				//IdCr = 3
    _write_byte_(0x11);				//HVCr = 0x11 (SubSamp 1x1)
    _write_byte_(1);				//QTCr Normally equal to QTCb = 1

    //DHT
    _write_word_(0xFFC4);		//marker = 0xFFC4
    _write_word_(0x01A2);		//length = 0x01A2
    _write_byte_(0);			//HTYDCinfo 
    //          bit 0..3	: number of HT (0..3), for Y =0
    //			bit 4		: type of HT, 0 = DC table,1 = AC table
    //			bit 5..7	: not used, must be 0
    _write_(Standard_DC_Luminance_NRCodes, sizeof(Standard_DC_Luminance_NRCodes));	//DC_L_NRC
    _write_(Standard_DC_Luminance_Values, sizeof(Standard_DC_Luminance_Values));		//DC_L_VALUE
    _write_byte_(0x10);			//HTYACinfo
    _write_(Standard_AC_Luminance_NRCodes, sizeof(Standard_AC_Luminance_NRCodes));
    _write_(Standard_AC_Luminance_Values, sizeof(Standard_AC_Luminance_Values)); 
    _write_byte_(0x01);			//HTCbDCinfo
    _write_(Standard_DC_Chrominance_NRCodes, sizeof(Standard_DC_Chrominance_NRCodes));
    _write_(Standard_DC_Chrominance_Values, sizeof(Standard_DC_Chrominance_Values));
    _write_byte_(0x11);			//HTCbACinfo
    _write_(Standard_AC_Chrominance_NRCodes, sizeof(Standard_AC_Chrominance_NRCodes));
    _write_(Standard_AC_Chrominance_Values, sizeof(Standard_AC_Chrominance_Values));

    //SOS
    _write_word_(0xFFDA);		//marker = 0xFFC4
    _write_word_(12);		    //length = 12
    _write_byte_(3);			//nrofcomponents, Should be 3: truecolor JPG

    _write_byte_(0x01);			//Idy=1
    _write_byte_(0x00);			//HTY	
    //      bits 0..3: AC table (0..3)
    //		bits 4..7: DC table (0..3)
    _write_byte_(0x02);			//IdCb
    _write_byte_(0x11);			//HTCb

    _write_byte_(3);			//IdCr
    _write_byte_(0x11);			//HTCr

    _write_byte_(0);			//Ss not interesting, they should be 0,63,0
    _write_byte_(0x3F);			//Se
    _write_byte_(0);			//Bf
}

void Jpeg::_write_byte_(unsigned char value)
{
    _write_(&value, 1);
}

void Jpeg::_write_word_(unsigned short value)
{
    unsigned short _value = ((value >> 8) & 0xFF) | ((value & 0xFF) << 8);
    _write_(&_value, 2);
}

void Jpeg::_write_(const void* p, int byteSize)
{
    fwrite(p, 1, byteSize, f);

}


