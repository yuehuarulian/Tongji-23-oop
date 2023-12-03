#include <iostream>
#include <fstream>
using namespace std;

struct student {
    int no;
    char name[20];
    int score;
    struct student* next;
};

struct student* read(int& m)
{
    fstream f; // ���ļ�
    f.open(("student.txt"), ios::in);
    if (!f.is_open()) {
        cerr << "�޷����ļ� student.txt" << endl;
        return 0;
    }
    f >> m; // ��ȡѧ������
    struct student* tail = nullptr;
    struct student* head = nullptr;
    for (int i = 0; i < m; ++i) {
        student* newStudent = new (nothrow) student;
        if (!newStudent) {
            cout << "�ڴ����ʧ��" << endl;
            return 0;
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
    f.close();
    return head;
}
void PRINT(struct student* p)
{
    cout << "ѧ��:" << p->no << " ����:" << p->name << " �ɼ�:" << p->score << endl;
}
void FIND(struct student* head, int query)
{
    struct student* p = head;
    while (p) {
        if (p->no == query) {
            PRINT(p);
            return;
        }
        p = p->next;
    }
    cout << "������" << endl;
    return;
}
bool isContinue()
{
    std::cout << "�Ƿ������(y/n): \n";
    char tmp;
    std::cin >> tmp;
    if (tmp == 'Y' || tmp == 'y')
    {
        return true;
    }
    return false;
}
void FREE(struct student* head)
{
    while (head != nullptr) {
        student* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
}
int main()
{
    /* �������ȡ�ļ� */
    int m = 0; // ѧ������
    struct student* head = read(m);
    if (head == NULL)
        return -1;

    // �����ȡ���
    while (1)
    {
        // �����ѯѭ��
        int query;
        cin >> query;
        /* ִ�в�ѯ */
        FIND(head, query);
        if (!isContinue())
        {
            break; // �����յ�����Ҫ���������˳�ѭ��
        }
    }
    FREE(head);
    return 0;
}