/*****************************************
*  Author: Root
*****************************************/



//PNG�ļ�������:89 50 4E 47 0D 0A 1A 0A
//�ļ�ͷ���ݿ�IHDR:Width	4	��ȣ����أ�
//                 Height	4	�߶ȣ����أ�
//                 Bit Depth	1	ͼ�����
//                 Color Type	1	��ɫ����
//                 Compression method	1	ѹ������
//                 Filter method	1	�˲�������
//                 Interlace mthod	1	����ɨ�跽��
//��ɫ�����ݿ�PLTE��Red	1	0 = ��ɫ 255 = ��ɫ
//                  Green 1 0 = ��ɫ 255 = ��ɫ 
//                  Blue  1 0 = ��ɫ 255 = ��ɫ
//ͼ�����ݿ�IDAT:�洢ʵ�ʵ����ݣ����������пɰ����������˳���ͼ�����ݿ顣
//ͼ���������IEND:�������PNG�ļ������������Ѿ����������ұ���Ҫ�����ļ���β����

//��һ�У� 00 00 00 0D ��ʾIHDR���ݿ��ܳ���Ϊ13�ֽ�
//�ڶ��У� 49 48 44 52 ΪIHDR���ݿ��ʶ
//�����У� 00 00 06 B6 ��ʾͼ����1718����
//�����У� 00 00 04 8E ��ʾͼ��߶�1166����
//�����У�08 ��ʾͼ��ɫ���ͼ��Ϊ���ɫͼ��
//�����У�06 ��ʾ��ɫ���ͣ���ͼ��Ϊ����ͨ�����ݵ����ɫͼ��
//�����У�00 ��ʾѹ����������ͼ��ʹ��LZ77�����㷨��Ŀǰ�涨Ϊ0
//�ڰ��У�04 ��ʾ�˲�������
//�ھ��У�00 ��ʾ����ɨ�跽������ͼ��ʹ�÷Ǹ���ɨ��
//��ʮ�У�CRCУ��λ
#include "PicReader.h"
#include "Png.h"
#include <stdio.h>

void testR() {
	PicReader imread;
	BYTE *data = nullptr;
	UINT x, y;

	/******************************************
	*  ˵����readPic()����һ���ַ���ָ���ȡͼƬ
	*       testReader(
	*            BYTE*&, ����BYTEָ�����ã����ڽ���������Ϣ
	*            UINT&,  ��ȡͼ��Ŀ����Ϣ
	*			 UINT&)  ��ȡͼ��ĸ߶���Ϣ
	*       ������Ϣÿ�ĸ�һ��(R G B A)����������ÿ�������һ���ĸ����ִ�����ԭͼһ������
	*       ����testReaderʵ�ֵ���ֱ��ʹ�ú�����������ڴ�ָ�룬��ÿ�μ�������ݺ���Ҫ�ͷ�һ��data
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