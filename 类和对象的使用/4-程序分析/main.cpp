#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
const int semester_num = 4;
using namespace std;
typedef struct SemesterGrad {
public:
    int chinese;
    int math;
    int english;
    float average;
    SemesterGrad(int c, int m, int e) : chinese(c), math(m), english(e)
    {
        calculateAverage();
    }
    SemesterGrad() {};
    void calculateAverage()
    {
        average = static_cast<float>(chinese + math + english) / 3;
    }
    void change_grade(int index, int changed_grade)
    {
        switch (index) {
            case 1:
                chinese = changed_grade;
                break;
            case 2:
                math = changed_grade;
                break;
            case 3:
                english = changed_grade;
                break;
        }
        calculateAverage();
    }
}SemesterGrad;
//����һ��ѧ����Student�����󣬶������԰���ѧ�����֡�ѧ�š��ĸ�ѧ�ڳɼ���SemesterGrad�����顣
class Student {
public:
    char* name;
    int student_id;
    SemesterGrad semesterGrads[4];
    Student(char* n, int id) :name(n), student_id(id){}
    void printStudentInfo() {
        cout << "==ѧ����Ϣ==" << endl;
        cout << "������" << name << endl;
        cout << "ѧ�ţ�" << student_id << endl;

        for (int i = 0; i < 4; ++i) {
            cout << "==ѧ�ڳɼ�==" << endl;
            cout << "=ѧ��" << i + 1 << "=" << endl;
            cout << "���ĳɼ���" << semesterGrads[i].chinese << endl;
            cout << "��ѧ�ɼ���" << semesterGrads[i].math << endl;
            cout << "Ӣ��ɼ���" << semesterGrads[i].english << endl;
            cout << "ƽ���ɼ���" << fixed << std::setprecision(4) << semesterGrads[i].average << endl;
        }
    }
};

/*
sophia 2312004
91 75 88
87 96 93
81 73 82
83 94 86
*/
int main()
{
    char name[20];
    int id;
    cin >> name >> id;
    Student student(name, id);

    for (int i = 0; i < semester_num; i++) {
        int chinese, math, english;
        cin >> chinese >> math >> english;
        student.semesterGrads[i] = SemesterGrad(chinese, math, english);
    }
    int changed_semester, subject, changed_grade;
    cin >> changed_semester >> subject >> changed_grade;
    student.semesterGrads[changed_semester - 1].change_grade(subject, changed_grade);
    student.printStudentInfo();
    return 0;
}