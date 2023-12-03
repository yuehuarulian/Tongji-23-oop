#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
#include "huffman.h"
using namespace std;

int main(int argc, char* argv[]) 
{
    //计时开始
    auto starttime = chrono::high_resolution_clock::now();
    cout << "Zipper 0.001! Author: root" << endl;
    if (argc != 4) {
        cerr << "Please make sure the number of parameters is correct." << endl;
        return -1;
    }
    if (strcmp(argv[3], "zip") && strcmp(argv[3], "uzip")) {
        cerr << "Unknown parameter!\nCommand list:\nzip" << endl;
        return -1;
    }
     
    Zip_Uzip_file File(argv[1], argv[2], argv[3]);

    //记录时间
    auto endtime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<chrono::microseconds>(endtime - starttime);
    cout << "运行时间: " << double(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den << " 秒" << std::endl;
    return 0;
}