#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream f; // 打开文件
    f.open(("foo.bar"), ios::binary | ios::in);
    if (!f.is_open()) {
        cerr << "无法打开文件 foo.bar" << endl;
        return 0;
    }
    int total = 0;
    int a[10000] = { 0 };
    int row = 0;
    char c;
    cout << "-*原始文件*-\n";
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
                cout << "数组太小" << endl;
                return 1;
            }
            a[++row] = total;
        }
        cout << c;
    }
    cout << endl;
    cout << "-*输出内容*-\n";
    cout << row << endl;
    for (int i = 0; i <= row; i++)
        cout << a[i] << endl;
    f.close();
    return 0;
}