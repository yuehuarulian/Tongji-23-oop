#include <iostream>
#include <fstream>
using namespace std;
// ѧ���ṹ��
struct student {
    int no;                
    char name[20];         
    int score;             
    struct student* next;  
};

void PRINT(struct student* head)
{
    cout << "���е�ѧ����Ϣ���£�" << endl;
    struct student* p = head;
    while (p != NULL) {
        cout << "ѧ��:" << p->no << " ����:" << p->name << " �ɼ�:" << p->score << endl;
        p = p->next;
    }
} 

int main() {
    int m;
    fstream f; // ���ļ�
    f.open(("student.txt"), ios::in | ios::out);
    if (!f.is_open()) {
        cerr << "�޷����ļ� student.txt" << endl;
        return 0;
    }
    f >> m; // ��ȡѧ������

    student* head = nullptr;
    student* tail = nullptr; 

    for (int i = 0; i < m; ++i) {
        student* newStudent = new (nothrow) student;
        if (!newStudent) {
            cout << "�ڴ����ʧ��" << endl;
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