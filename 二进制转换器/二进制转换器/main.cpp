#include <iostream>
#include <cstring>
using namespace std;
void itobs(int num, char* buffer) {
    // ��λ���㽫����ת��Ϊ�����Ʋ����� buffer �ַ���
    for (int i = 0; i < 32; i++) {
        buffer[i] = (num & (1 << (31 - i))) ? '1' : '0';
    }
    buffer[32] = '\0'; // ��β�����ַ���������
}

int main() {
    int num;
    char character;
    while (cin >> num) {
        char s[60];
        itobs(num, s);
        cout << num << " �Ķ������ǣ�" ;
        for (int i = 0; i < 32; i++) {
            cout << s[i];
            if (i % 8 == 7)
                cout << ' ';
        }
        cout << endl;
    }
    cout << "------�������------" << endl;
    return 0;
}