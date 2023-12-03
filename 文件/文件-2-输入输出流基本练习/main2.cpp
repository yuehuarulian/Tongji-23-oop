#include <iostream>
#include <iomanip>  // 用于设置输出格式
using namespace std;

/* 复读整数，并拒绝错误输入 */
istream& f(istream& in) {
    /* 复读整数，并拒绝错误输入 */
    auto in_state = in.rdstate(); // 保存流入函数的状态

    // do something

    int num;
    while (!in.eof()) {
        in >> num;
        // 判断是否为合法数据
        if (in.good() && num == -1)
            break;
        else if (!in.fail() && !in.bad()) {
            cout << "你说了:" << num << endl;
        }
        else {
            cout << "[Illegal]" << endl;
            in.clear();
            char c;
            // 循环忽略字符，直到遇到空格或换行符
            while (in.get(c) && c != ' ' && c != '\n');

        }
    }

    in.setstate(in_state);        // 复位流           
    return in;
}


int main() {
    cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
    f(cin);
    return 0;
}