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
//���Ϸ������� 13000000000~19999999999
int main() {
    ifstream f; // ���ļ�
    f.open(("messy.content"), ios::binary);
    if (!f.is_open()) {
        cerr << "�޷����ļ� foo.bar" << endl;
        return 0;
    }
    valid(f);
    f.close();
    return 0;
}