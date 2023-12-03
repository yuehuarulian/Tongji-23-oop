/*****************************************
*  Author: Root
*****************************************/

#include "PicReader.h"
#include "Png.h"
#include <stdio.h>

void testR() {
	PicReader imread;
	BYTE *data = nullptr;
	UINT x, y;

	/******************************************
	*  说明：readPic()接受一个字符串指针读取图片
	*       testReader(
	*            BYTE*&, 传入BYTE指针引用，用于接收像素信息
	*            UINT&,  读取图像的宽度信息
	*			 UINT&)  读取图像的高度信息
	*       像素信息每四个一组(R G B A)，即接下来每次输出的一行四个数字代表着原图一个像素
	*       由于testReader实现的是直接使用函数内申请的内存指针，故每次检查完数据后需要释放一次data
	*******************************************/

	// Pure black
	imread.readPic("test\\black.png");
	imread.getData(data, x, y);

	// Check the data
	printf("black data, should be 0 0 0 255 each line, press enter to continue...");
	(void)getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	(void)getchar();

	// Pure white

	imread.readPic("test\\white.png");
	imread.getData(data, x, y);

	// Check the data
	printf("white data, should be 255 255 255 255 each line, press enter to continue...");
	(void)getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	(void)getchar();

	// Pure red
	imread.readPic("test\\red.png");
	imread.getData(data, x, y);

	// Check the data
	printf("red data, should be 255 0 0 255 each line, press enter to continue...");
	(void)getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	(void)getchar();

	// Pure green
	imread.readPic("test\\green.png");
	imread.getData(data, x, y);

	// Check the data
	printf("green data, should be 0 255 0 255 each line, press enter to continue...");
	(void)getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	(void)getchar();

	// Pure blue
	imread.readPic("test\\blue.png");
	imread.getData(data, x, y);

	// Check the data
	printf("blue data, should be 0 0 255 255 each line, press enter to continue...");
	(void)getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	(void)getchar();
}

//void readLena() {
//	PicReader imread;
//	BYTE* data = nullptr;
//	UINT x, y;
//	imread.readPic("lena.tiff");
//	imread.getData(data, x, y);
//	printf("show lena, press enter to continue...");
//	//(void)getchar();
//	imread.showPic(data, x, y);
//	delete[] data;
//	data = nullptr;
//	printf("Press enter to continue...");
//	//(void)getchar();
//}
int main() {
	Jpeg jpegzip("lena.tiff");
	//jpegzip.Zip();
	return 0;
}