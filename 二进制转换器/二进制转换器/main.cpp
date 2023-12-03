#include <iostream>
#include <cstring>
using namespace std;
void itobs(int num, char* buffer) {
    // 按位运算将整数转换为二进制并存入 buffer 字符串
    for (int i = 0; i < 32; i++) {
        buffer[i] = (num & (1 << (31 - i))) ? '1' : '0';
    }
    buffer[32] = '\0'; // 结尾加上字符串结束符
}

int main() {
    int num;
    char character;
    while (cin >> num) {
        char s[60];
        itobs(num, s);
        cout << num << " 的二进制是：" ;
        for (int i = 0; i < 32; i++) {
            cout << s[i];
            if (i % 8 == 7)
                cout << ' ';
        }
        cout << endl;
    }
    cout << "------程序结束------" << endl;
    return 0;
}