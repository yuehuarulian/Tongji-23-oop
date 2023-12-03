#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include"Jpeg.h"
//your_project.exe -compress lena.tiff
//˵���� ѹ��ͼƬ�������ͬһĿ¼�£����ܸ���Դ�ļ����ļ���Ӧ��lena(Դ�ļ���)��ͷ���ļ����Ϳ�����ȷ��(��.dat.bin��)
//your_project.exe -read lena.dat
//˵���� ��ȡ�������ѹ���õ�ͼƬ����չʾ����������ṩչʾ������
//int main() {
//	Jpeg jpegzip("lena.tiff");
//	jpegzip.Zip("output.jpg");
//	return 0;
//}
void readLena(const char* filename) {
    PicReader imread;
    BYTE* data = nullptr;
    UINT x, y;
    imread.readPic(filename);
    imread.getData(data, x, y);
    imread.showPic(data, x, y);
    delete[] data;
    data = nullptr;
}
int main(int argc, char* argv[]) {
    // �����������
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " -compress <input_file> or -read <compressed_file>" << std::endl;
        return 1;
    }
    std::string operation = argv[1];
    // ѹ��
    if (operation == "-compress") {
        Jpeg jpegzip(argv[2]);
        jpegzip.Zip("lena.dat");
    }
    // ��ȡ��չʾͼ��
    else if (operation == "-read") {
        readLena(argv[2]);
    }
    else {
        std::cerr << "Unknown operation: " << operation << std::endl;
        return 1;
    }
    return 0;
}

