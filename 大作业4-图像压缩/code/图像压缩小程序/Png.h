#ifndef PNG
#define PNG
#define _CRT_SECURE_NO_WARNINGS
#include "PicReader.h"
#include "LZ77.h"
#include "huffmantree.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
class Png {
public:
	Png(const char* file)
	{
		//strcpy_s(filename, sizeof(filename), file);
		imread.readPic(file);
		imread.getData(data, x, y);
		//printf("show lena, press enter to continue...")
		//(void)getchar();
		//imread.showPic(data, x, y);
	}
	~Png()
	{
		delete[4 * x * y] currentFilter_PAETH;
		delete[] data;
		data = nullptr;
	}
	void Zip();
private:
	//ÂË²¨Æ÷
	void Filtering();
	unsigned char paeth_predictor(unsigned char a, unsigned char b, unsigned char c);
	void createPNGHeader();
	void writePNGFile(const std::string& filename);
	void fout_picture();
	std::string encodePicture;
	PicReader imread;
	UINT x, y;
	BYTE* data = nullptr;
	BYTE* currentFilter_PAETH;
	std::vector<unsigned char> header;
};




#endif