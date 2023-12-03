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

    struct student* head = new (nothrow) student;
    if (!head) {
        cout << "�ڴ����ʧ��" << endl;
        return 0;
    }
    head->next = NULL;
    struct student* tail = head;
    for (int i = 0; i < m; ++i) {
        student* newStudent = new (nothrow) student;
        if (!newStudent) {
            cout << "�ڴ����ʧ��" << endl;
            return 0;
        }
        f >> newStudent->no >> newStudent->name >> newStudent->score;
        newStudent->next = nullptr;
        tail->next = newStudent;
        tail = newStudent;
    }
    f.close();
    return head;
}
void FIND_AND_DEL(struct student* head, int query)
{
    struct student* p = head->next;
    struct student* q = head;
    while (p && p->no != query) {
        q = p;
        p = p->next;
    }
    if (p && p->no == query) {
        q->next = p->next;
        delete p;
    }
    else
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
void PRINT(struct student* head)
{
    cout << "ʣ���ѧ����Ϣ���£�" << endl;
    struct student* p = head->next;
    while (p != NULL) {
        cout << "ѧ��:" << p->no << " ����:" << p->name << " �ɼ�:" << p->score << endl;
        p = p->next;
    }
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
        FIND_AND_DEL(head, query);
        if (!isContinue())
        {
            break; // �����յ�����Ҫ���������˳�ѭ��
        }
    }
    PRINT(head);
    FREE(head);
    return 0;
}