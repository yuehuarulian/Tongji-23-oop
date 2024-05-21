#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
void valid(istream& f)
{
    char find[4] = { 0 };
    cin >> find;
    char uns[12] = { 0 };
    char fin[10000] = { 0 };
    while (!f.eof()) {
        f.getline(fin, 10000);
        if (strlen(fin) == 11 && !strncmp(find, fin, 3)) {
            for (int i = 0; i < 11; i++) {
                if (fin[i] > '0' && fin[i]<'9' && fin[i]>uns[i]) {
                    strcpy(uns, fin);
                    break;
                }
            }
        }
    }
    uns[11] = '\0';
    cout << uns << endl;
}
//即合法数据是 13000000000~19999999999
int main() {
    ifstream f; // 打开文件
    f.open(("messy.content"), ios::binary);
    if (!f.is_open()) {
        cerr << "无法打开文件 foo.bar" << endl;
        return 0;
    }
    valid(f);
    f.close();
    return 0;
}