#include <iostream>
#include <fstream>
using namespace std;
// 学生结构体
struct student {
    int no;                
    char name[20];         
    int score;             
    struct student* next;  
};

void PRINT(struct student* head)
{
    cout << "所有的学生信息如下：" << endl;
    struct student* p = head;
    while (p != NULL) {
        cout << "学号:" << p->no << " 姓名:" << p->name << " 成绩:" << p->score << endl;
        p = p->next;
    }
} 

int main() {
    int m;
    fstream f; // 打开文件
    f.open(("student.txt"), ios::in | ios::out);
    if (!f.is_open()) {
        cerr << "无法打开文件 student.txt" << endl;
        return 0;
    }
    f >> m; // 读取学生数量

    student* head = nullptr;
    student* tail = nullptr; 

    for (int i = 0; i < m; ++i) {
        student* newStudent = new (nothrow) student;
        if (!newStudent) {
            cout << "内存分配失败" << endl;
            return -1;
        }

        f >> newStudent->no >> newStudent->name >> newStudent->score;
        newStudent->next = nullptr;

        if (head == nullptr) {
            head = newStudent;
            tail = newStudent;
        }
        else {
            tail->next = newStudent;
            tail = newStudent;
        }
    }

    //f << "sds" << endl;
    f << "aaaadfasdfadfa" << endl;
    f.close();
    PRINT(head);
    while (head != nullptr) {
        student* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }

    return 0;
}