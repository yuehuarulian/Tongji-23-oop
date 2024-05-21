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
//定义一个学生（Student）对象，对象属性包括学生名字、学号、四个学期成绩（SemesterGrad）数组。
class Student {
public:
    char* name;
    int student_id;
    SemesterGrad semesterGrads[4];
    Student(char* n, int id) :name(n), student_id(id){}
    void printStudentInfo() {
        cout << "==学生信息==" << endl;
        cout << "姓名：" << name << endl;
        cout << "学号：" << student_id << endl;

        for (int i = 0; i < 4; ++i) {
            cout << "==学期成绩==" << endl;
            cout << "=学期" << i + 1 << "=" << endl;
            cout << "语文成绩：" << semesterGrads[i].chinese << endl;
            cout << "数学成绩：" << semesterGrads[i].math << endl;
            cout << "英语成绩：" << semesterGrads[i].english << endl;
            cout << "平均成绩：" << fixed << std::setprecision(4) << semesterGrads[i].average << endl;
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