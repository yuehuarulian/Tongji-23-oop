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
	// RGBAת��YCbCr
	void RGBtoYCbCr(int row, int col);
	// ���� DCT ת������
	const double alpha_u(int u);
	const double alpha_v(int v);
	// ִ����ɢ���ұ任 (DCT)
	void performDCT(double block[blockSize][blockSize]);
	// ����
	void quantizeDCT(double block[blockSize][blockSize], const char quantizationTable[blockSize][blockSize]);
	// ��������� DCT ϵ����������ɨ��˳��ת��Ϊһά����
	void zigzagScan(double block[blockSize][blockSize], int zigzagArray[blockSize * blockSize]);
	//huffman����д���ļ�
	void write_bitstring(const BitString* bs, int counts, int& newByte, int& newBytePos);
	// �ļ�ͷд��
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
