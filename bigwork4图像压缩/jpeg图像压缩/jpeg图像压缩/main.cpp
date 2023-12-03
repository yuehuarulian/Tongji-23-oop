#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include"Jpeg.h"
//your_project.exe -compress lena.tiff
//说明： 压缩图片，输出至同一目录下，不能覆盖源文件，文件名应以lena(源文件名)开头，文件类型可自由确定(如.dat.bin等)
//your_project.exe -read lena.dat
//说明： 读取用你程序压缩好的图片，并展示出来（框架提供展示方法）
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
    // 输入参数不足
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " -compress <input_file> or -read <compressed_file>" << std::endl;
        return 1;
    }
    std::string operation = argv[1];
    // 压缩
    if (operation == "-compress") {
        Jpeg jpegzip(argv[2]);
        jpegzip.Zip("lena.dat");
    }
    // 读取并展示图像
    else if (operation == "-read") {
        readLena(argv[2]);
    }
    else {
        std::cerr << "Unknown operation: " << operation << std::endl;
        return 1;
    }
    return 0;
}

