#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream f; // ���ļ�
    f.open(("foo.bar"), ios::binary | ios::in);
    if (!f.is_open()) {
        cerr << "�޷����ļ� foo.bar" << endl;
        return 0;
    }
    int total = 0;
    int a[10000] = { 0 };
    int row = 0;
    char c;
    cout << "-*ԭʼ�ļ�*-\n";
    while (1) {
        c = f.get();
        total++;
        //if (total == 2945)
        //    system("pause");
        if (f.eof()){
            a[++row] = total;
            break;
        }
        if (c == '\n') {
            if (row >= 10000)
            {
                cout << "����̫С" << endl;
                return 1;
            }
            a[++row] = total;
        }
        cout << c;
    }
    cout << endl;
    cout << "-*�������*-\n";
    cout << row << endl;
    for (int i = 0; i <= row; i++)
        cout << a[i] << endl;
    f.close();
    return 0;
}