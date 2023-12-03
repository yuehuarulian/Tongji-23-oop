#include <iostream>
#include <iomanip>  // �������������ʽ
using namespace std;

int main() {
    double num[100000];
    double num_max = 0.0;
    double num_min = 0.0;
    int i = 0;
    while (cin >> num[i]) {
        if (cin.fail()) {
            cin.ignore(1000, '\n');
            cin.clear();
        }
        if (num[i] > 0 && num[i] > num_max)
            num_max = num[i];
        else if (num[i] < 0 && num[i] < num_min)
            num_min = num[i];
        i++;
    }
    int ws1 = 1;
    int ws2 = 2;
    int a1 = (int)num_max;
    int a2 = (int)num_min;
    while (a1 /= 10)
        ws1++;
    while (a2 /= 10)
        ws2++;

    cout << "������һЩ����������q����:" << endl;
    for (int j = 0; j < i; j++) {
        cout << fixed << setprecision(3) << setw(max(ws1, ws2) + 4) << (num[j] > 0 ? num[j] - 0.0005 : num[j] + 0.0005) << endl;

    }
    cout << "------�������------";
    return 0;
};