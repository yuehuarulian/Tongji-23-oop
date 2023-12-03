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
struct student* FIND_AND_ADD(struct student* head, int query)
{
    struct student* p = head;
    while (p && p->no != query)
        p = p->next;
    if (p && p->no == query) 
    {
        cout << "�Ѵ���" << endl;
        return head;
    }
    else {
        student* newStudent = new (nothrow) student;
        newStudent->no = query;
        cin >> newStudent->name >> newStudent->score;
        newStudent->next = head;
        head = newStudent;
    }
    return head;
}
struct student* SORT(struct student* head)
{
    struct student* p, * q;
    struct student t;

    if (head == NULL) {
        return NULL;
    }

    for (p = head; p->next != NULL; ) {
        for (q = p->next; q != NULL;) {
            if (p->score < q->score || (p->score == q->score && p->no > q->no)) {
                // ���������ڵ������
                t = *p;
                *p = *q;
                *q = t;
                q->next = p->next;
                p->next = t.next;
            }
            q = q->next;
        }
        p = p->next;
    }
    return head;
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
    struct student* p = head;
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
        head = FIND_AND_ADD(head, query);
        if (!isContinue())
        {
            break; // �����յ�����Ҫ���������˳�ѭ��
        }
    }
    SORT(head);
    PRINT(head);
    FREE(head);
    return 0;
}