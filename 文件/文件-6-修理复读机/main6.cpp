#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int main() {
    fstream f; // ���ļ�
    f.open(("noise.txt"), ios::in);
    if (!f.is_open()) {
        cerr << "�޷����ļ� foo.bar" << endl;
        return 0;
    }
    int cou = 0;
    char ch;
    while (!f.eof()) {
        ch = f.get();
        if (!(cou %= 3))
            cout << ch;
        cou++;
    }
    f.close();
    return 0;
}