#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
const int student_num = 5;
using namespace std;
//ѧ�������֡�ѧ�š����ĳɼ�����ѧ�ɼ���Ӣ��ɼ�
class Student {
public:
    int student_id;
    int grade;
    Student(int id, int g) :student_id(id), grade(g) {}
    Student() {};
};
int main()
{
    Student students[student_num];
    for (Student* p = students; p - students < student_num; p++) {
        cout << "�������" << p - students + 1 << "��ѧ����ѧ�źͳɼ�:";
        cin >> p->student_id >> p->grade;
    }
    cout << "��1��ѧ����ѧ���� " << students[0].student_id << " �ɼ�Ϊ " << students[0].grade << endl;
    cout << "��3��ѧ����ѧ���� " << students[2].student_id << " �ɼ�Ϊ " << students[2].grade << endl;
    cout << "��5��ѧ����ѧ���� " << students[4].student_id << " �ɼ�Ϊ " << students[4].grade << endl;
    return 0;
}