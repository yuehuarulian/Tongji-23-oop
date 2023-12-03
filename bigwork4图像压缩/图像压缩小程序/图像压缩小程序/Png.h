#ifndef JPEG_H
#define JPEG_H
#include "PicReader.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
const int blockSize = 8;
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
	double Y[blockSize * blockSize] = { 0 };
	double Cb[blockSize * blockSize] = { 0 };
	double Cr[blockSize * blockSize] = { 0 };
};
struct Jpeg {
public:
	Jpeg(const char* file)
	{
		imread.readPic(file);
		imread.getData(data, x, y);

		ycbcr = new YCbCr[256 * 256 / 64];
		if (ycbcr == NULL) {
			std::cout << "·ÖÅäÄÚ´æÊ§°Ü" << std::endl;
		}
		zigzag = new zigzagArray[256 * 256 / 64];
		if (zigzag == NULL) {
			std::cout << "·ÖÅäÄÚ´æÊ§°Ü" << std::endl;
		}
		//printf("show lena, press enter to continue...")
		//(void)getchar();
		//imread.showPic(data, x, y);
	}
	~Jpeg()
	{
		/*delete[4 * x * y] currentFilter_PAETH;*/
		delete[] data;
		data = nullptr;
	}
	void Zip();
private:
	//void createPNGHeader();
	//void writePNGFile(const std::string& filename);
	/*std::string encodePicture;*/
	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;
	YCbCr* ycbcr;
	int x_ycbcr, y_ycbcr;
	zigzagArray* zigzag;
	//BYTE* currentFilter_PAETH;
	//std::vector<unsigned char> header;
	//int huffman_cou[256][2] = { 0 };

};

#endif