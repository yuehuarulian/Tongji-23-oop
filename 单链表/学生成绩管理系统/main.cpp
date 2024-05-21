#include <iostream>
#include <fstream>
using namespace std;
const char* ch[5] = { "��","��","��","����","������" };
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
void menu()
{
    int i;
    std::cout << std::endl;
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
    std::cout << std::endl;
    std::cout << "*\t1 ��ʾ��¼\t2 ͳ�Ƽ�¼\t3 �����¼\t*\n";
    std::cout << "*\t4 ���Ҽ�¼\t5 ɾ����¼\t6 �޸ļ�¼\t*\n";
    std::cout << "*\t7 ��Ӽ�¼\t0 �˳�ϵͳ\t\t\t*\n";
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
}
void disp(struct student* head)
{
    cout << "���е�ѧ����Ϣ���£�" << endl;
    struct student* p = head;
    while (p != NULL) {
        cout << "ѧ��:" << p->no << " ����:" << p->name << " �ɼ�:" << p->score << endl;
        p = p->next;
    }
}
void count(struct student* head)
{
    int cn[5] = { 0 };
    struct student* p = head;
    while (p != NULL) {
        if (p->score >= 0 && p->score < 60)
            cn[4]++;
        else if (p->score >= 60 && p->score < 70)
            cn[3]++;
        else if (p->score >= 70 && p->score < 80)
            cn[2]++;
        else if (p->score >= 80 && p->score < 90)
            cn[1]++;
        else if (p->score >= 90 && p->score <= 100)
            cn[0]++;
        p = p->next;
    }
    printf("��Ϣ���£�\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d��  ", ch[i], cn[i]);
    }
    printf("\n");
    return;
}
void sort(struct student* head)
{
    struct student* p, * q;
    struct student t;
    if (head == NULL) {
        return;
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
    return;
}
void searchbyID(struct student* head, int query)
{
    struct student* p = head;
    while (p) {
        if (p->no == query) {
            cout << "ѧ��:" << p->no << " ����:" << p->name << " �ɼ�:" << p->score << endl;
            return;
        }
        p = p->next;
    }
    cout << "������" << endl;
    return;
}
struct student* delbyID(struct student* head, int query)
{
    struct student* p = head;
    struct student* q = NULL;
    if (head == NULL)
    {
        cout << "������" << endl;
        return NULL;
    }
    while (p && p->no != query) {
        q = p;
        p = p->next;
    }
    if (p == head) {
        head = head->next;
        delete p;
    }
    else if (p && p->no == query) {
        q->next = p->next;
        delete p;
    }
    else
        cout << "������" << endl;
    return head;
}
struct student* modibyID(struct student* head, int query)
{
    struct student* p = head;
    while (p && p->no != query) {
        p = p->next;
    }
    if (p && p->no == query) {
        cin >> p->score;
    }
    else
        cout << "������" << endl;
    return head;
}
struct student* addbyID(struct student* head, int query)
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

void quit(struct student* head)
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
    int choice; // ��֤�����Ϊ����������
    char ch;
    int m = 0;
    struct student* head = read(m); // �������ȡ�ļ�������ʼ���������������
    menu();  // ���ò˵���ʾ������Ϊ��ֹ��������޶ȣ��뽫�������ѭ���ⲿ

    while (true) // ע���ѭ���˳�������
    {
         //system("CLS");
        // /* ����������Ϊ��ֹɳ���ж�ʧ�����ύʱ��������Ϊע�� */

        // ���ǹ���ʹ����ؿ���̨������������ͼ�ν��棬����Ϊ�˷�ֹɳ������ʧ��
        // ��ͬ��ʹ�����䱣��ע�ͣ����˹�����ʱ��ȡ��ע�ͱ��ر������ģ�
        std::cout << "ѡ��˵���(0~7):";
        std::cin >> choice;
        if (choice == 0) // ѡ���˳�
        {
            std::cout << "\n ȷ���˳���?(y/n)" << std::endl;
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                quit(head); // �������
                break;
            }
            else
                continue;
        }
        switch (choice)
        {
            case 1:
                disp(head); // �������
                break;
            case 2:
                count(head); // �������
                break;
            case 3:
                sort(head); // �������
                //disp(head);
                break;
            case 4:
                while (1)
                {
                    // �����ѯѭ��
                    int query;
                    cin >> query;
                    /* ִ�в�ѯ */
                    searchbyID(head, query);
                    if (!isContinue())
                    {
                        break; // �����յ�����Ҫ���������˳�ѭ��
                    }
                }
                break;
            case 5:
                while (1)
                {
                    // �����ѯѭ��
                    int query;
                    cin >> query;
                    /* ִ�в�ѯ */
                    head = delbyID(head, query);
                    if (!isContinue())
                    {
                        break; // �����յ�����Ҫ���������˳�ѭ��
                    }
                }
                //disp(head);
                break;
            case 6:
                while (1)
                {
                    // �����ѯѭ��
                    int query;
                    cin >> query;
                    /* ִ�в�ѯ */
                    head = modibyID(head, query);
                    if (!isContinue())
                    {
                        break; // �����յ�����Ҫ���������˳�ѭ��
                    }
                }
                //disp(head);
                break;
            case 7:
                while (1)
                {
                    // �����ѯѭ��
                    int query;
                    cin >> query;
                    /* ִ�в�ѯ */
                    head = addbyID(head, query);
                    if (!isContinue())
                    {
                        break; // �����յ�����Ҫ���������˳�ѭ��
                    }
                }
                sort(head);
                //disp(head);
                break;
            default:
                std::cout << "\n����������������" << std::endl;
        }
      /*  while (getchar() != ' ')
            ;*/
    }
    return 0;
}

