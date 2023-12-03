#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    long long int num[30];
    fstream f; // 打开文件
    f.open(("1.txt"), ios::in);
    if (!f.is_open()) {//if(f==NULL)/if(f)...
        cerr << "无法打开文件 student.txt" << endl;
        return 0;
    }
    for (int i = 0; i < 10; i++)
        f >> num[i];
    f.close();
    for (int i = 10; i < 20; i++)
        cin >> num[i];
    sort(num, num + 20);
    for (int i = 0; i < 20; i++)
        cout <<num[i] << endl;
    return 0;
}