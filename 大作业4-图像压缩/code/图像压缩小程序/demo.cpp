/*****************************************
*  Author: Root
*****************************************/



//PNG文件署名域:89 50 4E 47 0D 0A 1A 0A
//文件头数据块IHDR:Width	4	宽度（像素）
//                 Height	4	高度（像素）
//                 Bit Depth	1	图像深度
//                 Color Type	1	颜色类型
//                 Compression method	1	压缩方法
//                 Filter method	1	滤波器方法
//                 Interlace mthod	1	隔行扫描方法
//调色板数据块PLTE：Red	1	0 = 黑色 255 = 红色
//                  Green 1 0 = 黑色 255 = 绿色 
//                  Blue  1 0 = 黑色 255 = 蓝色
//图像数据块IDAT:存储实际的数据，在数据流中可包含多个连续顺序的图像数据块。
//图像结束数据IEND:用来标记PNG文件或者数据流已经结束，并且必须要放在文件的尾部。

//第一行： 00 00 00 0D 表示IHDR数据块总长度为13字节
//第二行： 49 48 44 52 为IHDR数据块标识
//第三行： 00 00 06 B6 表示图像宽度1718像素
//第四行： 00 00 04 8E 表示图像高度1166像素
//第五行：08 表示图像色深，该图像为真彩色图像
//第六行：06 表示颜色类型，该图像为带α通道数据的真彩色图像
//第七行：00 表示压缩方法，该图像使用LZ77派生算法，目前规定为0
//第八行：04 表示滤波器方法
//第九行：00 表示隔行扫描方法，该图像使用非隔行扫描
//第十行：CRC校验位
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
	//testR();
	//readLena();
	Png pngzip("lena.tiff");
	pngzip.Zip();
	return 0;
}