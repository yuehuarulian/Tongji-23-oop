#include <iostream>
#include <fstream>
using namespace std;
const char* ch[5] = { "优","良","中","及格","不及格" };
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
void menu()
{
    int i;
    std::cout << std::endl;
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
    std::cout << std::endl;
    std::cout << "*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
    std::cout << "*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
    std::cout << "*\t7 添加记录\t0 退出系统\t\t\t*\n";
    for (i = 0; i < 57; i++)
    {
        std::cout << '*';
    }
}
void disp(struct student* head)
{
    cout << "所有的学生信息如下：" << endl;
    struct student* p = head;
    while (p != NULL) {
        cout << "学号:" << p->no << " 姓名:" << p->name << " 成绩:" << p->score << endl;
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
    printf("信息如下：\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d人  ", ch[i], cn[i]);
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
    return;
}
void searchbyID(struct student* head, int query)
{
    struct student* p = head;
    while (p) {
        if (p->no == query) {
            cout << "学号:" << p->no << " 姓名:" << p->name << " 成绩:" << p->score << endl;
            return;
        }
        p = p->next;
    }
    cout << "不存在" << endl;
    return;
}
struct student* delbyID(struct student* head, int query)
{
    struct student* p = head;
    struct student* q = NULL;
    if (head == NULL)
    {
        cout << "不存在" << endl;
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
        cout << "不存在" << endl;
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
        cout << "不存在" << endl;
    return head;
}
struct student* addbyID(struct student* head, int query)
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
    int choice; // 保证输入的为正整数数字
    char ch;
    int m = 0;
    struct student* head = read(m); // 在这里读取文件或作初始化操作，自行设计
    menu();  // 调用菜单显示函数，为防止输出超出限度，请将此项放在循环外部

    while (true) // 注意该循环退出的条件
    {
         //system("CLS");
        // /* 清屏函数，为防止沙箱判断失误，请提交时保留此项为注释 */

        // 我们鼓励使用相关控制台美化代码美化图形界面，但是为了防止沙箱判题失误，
        // 请同样使相关语句保持注释，当人工审阅时会取消注释本地编译评阅！
        std::cout << "选择菜单项(0~7):";
        std::cin >> choice;
        if (choice == 0) // 选择退出
        {
            std::cout << "\n 确定退出吗?(y/n)" << std::endl;
            std::cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                quit(head); // 自行设计
                break;
            }
            else
                continue;
        }
        switch (choice)
        {
            case 1:
                disp(head); // 自行设计
                break;
            case 2:
                count(head); // 自行设计
                break;
            case 3:
                sort(head); // 自行设计
                //disp(head);
                break;
            case 4:
                while (1)
                {
                    // 程序查询循环
                    int query;
                    cin >> query;
                    /* 执行查询 */
                    searchbyID(head, query);
                    if (!isContinue())
                    {
                        break; // 当接收到不需要继续，则退出循环
                    }
                }
                break;
            case 5:
                while (1)
                {
                    // 程序查询循环
                    int query;
                    cin >> query;
                    /* 执行查询 */
                    head = delbyID(head, query);
                    if (!isContinue())
                    {
                        break; // 当接收到不需要继续，则退出循环
                    }
                }
                //disp(head);
                break;
            case 6:
                while (1)
                {
                    // 程序查询循环
                    int query;
                    cin >> query;
                    /* 执行查询 */
                    head = modibyID(head, query);
                    if (!isContinue())
                    {
                        break; // 当接收到不需要继续，则退出循环
                    }
                }
                //disp(head);
                break;
            case 7:
                while (1)
                {
                    // 程序查询循环
                    int query;
                    cin >> query;
                    /* 执行查询 */
                    head = addbyID(head, query);
                    if (!isContinue())
                    {
                        break; // 当接收到不需要继续，则退出循环
                    }
                }
                sort(head);
                //disp(head);
                break;
            default:
                std::cout << "\n输入错误，请从新输入" << std::endl;
        }
      /*  while (getchar() != ' ')
            ;*/
    }
    return 0;
}

