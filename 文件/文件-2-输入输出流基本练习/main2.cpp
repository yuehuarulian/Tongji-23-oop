#include <iostream>
#include <iomanip>  // �������������ʽ
using namespace std;

/* �������������ܾ��������� */
istream& f(istream& in) {
    /* �������������ܾ��������� */
    auto in_state = in.rdstate(); // �������뺯����״̬

    // do something

    int num;
    while (!in.eof()) {
        in >> num;
        // �ж��Ƿ�Ϊ�Ϸ�����
        if (in.good() && num == -1)
            break;
        else if (!in.fail() && !in.bad()) {
            cout << "��˵��:" << num << endl;
        }
        else {
            cout << "[Illegal]" << endl;
            in.clear();
            char c;
            // ѭ�������ַ���ֱ�������ո���з�
            while (in.get(c) && c != ' ' && c != '\n');

        }
    }

    in.setstate(in_state);        // ��λ��           
    return in;
}


int main() {
    cout << "������һЩ��������-1��Ctrl+Z������" << endl;
    f(cin);
    return 0;
}