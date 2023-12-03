#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
//学生的名字、学号、语文成绩、数学成绩和英语成绩
class Student {
public:
    char* name;
    int student_id;
    int chinese;
    int math;
    int english;
    float average;

    Student(char* n, int id, int c, int m, int e) :name(n), student_id(id), chinese(c), math(m), english(e)
    {
        calculateAverage();
    }

    void calculateAverage() 
    {
        average = static_cast<float>(chinese + math + english) / 3;
    }

    void change_grade(int index,int changed_grade) 
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
};

void printStudentInfo(const Student& student) {
    cout << "==学生信息==" << std::endl;
    cout << "姓名：" << student.name << std::endl;
    cout << "学号：" << student.student_id << std::endl;
    cout << "====成绩====" << std::endl;
    cout << "语文成绩：" << student.chinese << std::endl;
    cout << "数学成绩：" << student.math << std::endl;
    cout << "英语成绩：" << student.english << std::endl;
    cout << "平均成绩：" << std::fixed << std::setprecision(4) << student.average << std::endl;
    cout << std::endl;
}

int main() {
    vector<Student>students;
    int student_num;
    cin >> student_num;
 
    for (int i = 0; i < student_num; i++) {
        //一行信息
        char Line[100];
        cin.get();
        cin.getline(Line, 100000);
        char name[20];
        int id, chinese, math, english;
        sscanf(Line, "%s %d %d %d %d", name, &id, &chinese, &math, &english);
        Student student(name, id, chinese, math, english);
        printStudentInfo(student);
        //修改
        int change_num = 0;
        cin >> change_num;
        for (int j = 0; j < change_num; j++) {
            int index, changed_grade;
            cin >> index >> changed_grade;
            student.change_grade(index, changed_grade);
        }
        printStudentInfo(student);
        students.push_back(student);
    }
    return 0;
}
