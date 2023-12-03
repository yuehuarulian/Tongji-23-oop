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
    fstream f; // 打开文件
    f.open(("student.txt"), ios::in);
    if (!f.is_open()) {
        cerr << "无法打开文件 student.txt" << endl;
        return 0;
    }
    f >> m; // 读取学生数量
    struct student* tail = nullptr;
    struct student* head = nullptr;
    for (int i = 0; i < m; ++i) {
        student* newStudent = new (nothrow) student;
        if (!newStudent) {
            cout << "内存分配失败" << endl;
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
        cout << "已存在" << endl;
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
                // 交换两个节点的数据
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
    std::cout << "是否继续？(y/n): \n";
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
    cout << "剩余的学生信息如下：" << endl;
    struct student* p = head;
    while (p != NULL) {
        cout << "学号:" << p->no << " 姓名:" << p->name << " 成绩:" << p->score << endl;
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
    /* 在这里读取文件 */
    int m = 0; // 学生数量
    struct student* head = read(m);
    if (head == NULL)
        return -1;

    // 当你读取完成
    while (1)
    {
        // 程序查询循环
        int query;
        cin >> query;
        /* 执行查询 */
        head = FIND_AND_ADD(head, query);
        if (!isContinue())
        {
            break; // 当接收到不需要继续，则退出循环
        }
    }
    SORT(head);
    PRINT(head);
    FREE(head);
    return 0;
}