#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
//ѧ�������֡�ѧ�š����ĳɼ�����ѧ�ɼ���Ӣ��ɼ�
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
    cout << "==ѧ����Ϣ==" << std::endl;
    cout << "������" << student.name << std::endl;
    cout << "ѧ�ţ�" << student.student_id << std::endl;
    cout << "====�ɼ�====" << std::endl;
    cout << "���ĳɼ���" << student.chinese << std::endl;
    cout << "��ѧ�ɼ���" << student.math << std::endl;
    cout << "Ӣ��ɼ���" << student.english << std::endl;
    cout << "ƽ���ɼ���" << std::fixed << std::setprecision(4) << student.average << std::endl;
    cout << std::endl;
}

int main() {
    vector<Student>students;
    int student_num;
    cin >> student_num;
 
    for (int i = 0; i < student_num; i++) {
        //һ����Ϣ
        char Line[100];
        cin.get();
        cin.getline(Line, 100000);
        char name[20];
        int id, chinese, math, english;
        sscanf(Line, "%s %d %d %d %d", name, &id, &chinese, &math, &english);
        Student student(name, id, chinese, math, english);
        printStudentInfo(student);
        //�޸�
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
