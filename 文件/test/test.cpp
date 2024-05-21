#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int a, b;
    cin >> a;
    cin.seekg(-1, ios::end);
    cin >> b;
    cout << a << ' ' << b << endl;
}