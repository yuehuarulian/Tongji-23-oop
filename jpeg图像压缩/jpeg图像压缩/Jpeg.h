#ifndef JPEG_H
#define JPEG_H
#define _CRT_SECURE_NO_WARNINGS
#include "PicReader.h"
#include "Huffmancode.h"
#include "const.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
const double M_PI = 3.1415926;
struct Pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
	Pixel(byte r, byte g, byte b, byte a) :R(r), G(g), B(b), A(a) {}
};
struct YCbCr {
	double Y[blockSize][blockSize] = { 0 };
	double Cb[blockSize][blockSize] = { 0 };
	double Cr[blockSize][blockSize] = { 0 };
};
struct zigzagArray {
	int Y[blockSize * blockSize] = { 0 };
	int Cb[blockSize * blockSize] = { 0 };
	int Cr[blockSize * blockSize] = { 0 };
};
class Jpeg {
public:
	Jpeg(const char* file);
	~Jpeg();
	void Zip(const char* outputfile);
	char m_YTable[blockSize][blockSize];
	char m_CbCrTable[blockSize][blockSize];
private:
	// RGBA转换YCbCr
	void RGBtoYCbCr(int row, int col);
	// 定义 DCT 转换矩阵
	const double alpha_u(int u);
	const double alpha_v(int v);
	// 执行离散余弦变换 (DCT)
	void performDCT(double block[blockSize][blockSize]);
	// 量化
	void quantizeDCT(double block[blockSize][blockSize], const char quantizationTable[blockSize][blockSize]);
	// 将量化后的 DCT 系数按照螺旋扫描顺序转换为一维数组
	void zigzagScan(double block[blockSize][blockSize], int zigzagArray[blockSize * blockSize]);
	//huffman编码写入文件
	void write_bitstring(const BitString* bs, int counts, int& newByte, int& newBytePos);
	// 文件头写入
	void _write_jpeg_header();
	void _write_byte_(unsigned char value);
	void _write_word_(unsigned short value);
	void _write_(const void* p, int byteSize);
	BYTE* data = nullptr;
	UINT x, y;
	YCbCr* ycbcr;
	int x_ycbcr, y_ycbcr;
	zigzagArray* zigzag;
	FILE* f;
	HuffmanCode huffmancode;
};

#endif
