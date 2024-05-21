#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
const int student_num = 5;
using namespace std;
//学生的名字、学号、语文成绩、数学成绩和英语成绩
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
        cout << "请输入第" << p - students + 1 << "个学生的学号和成绩:";
        cin >> p->student_id >> p->grade;
    }
    cout << "第1个学生的学号是 " << students[0].student_id << " 成绩为 " << students[0].grade << endl;
    cout << "第3个学生的学号是 " << students[2].student_id << " 成绩为 " << students[2].grade << endl;
    cout << "第5个学生的学号是 " << students[4].student_id << " 成绩为 " << students[4].grade << endl;
    return 0;
}