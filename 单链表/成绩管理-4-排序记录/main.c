#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

// 学生结构体
struct student {
    int no;
    char name[20];
    int score;
    struct student* next;
};
void PRINT(struct student* head)
{
    printf("所有的学生信息如下：\n");
    struct student* p = head;
    while (p != NULL) {
        printf("学号:%d 姓名:%s 成绩:%d\n", p->no, p->name, p->score);
        p = p->next;
    }
}
void FREE(struct student* head)
{
    struct student* p = head;
    while (p != NULL) {
        struct student* q = p;
        p = p->next;
        free(q);
    }
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

struct student* read(int* m)
{
    struct student* head = NULL;
    struct student* tail = NULL;
    FILE* file = fopen("student.txt", "r"); // 打开文件

    if (file == NULL) {
        printf("文件打开失败\n");
        return NULL;
    }

    fscanf(file, "%d", m); // 读取学生数量
    for (int i = 0; i < *m; i++) {
        struct student* new_student = (struct student*)malloc(sizeof(struct student));
        if (new_student == NULL) {
            printf("内存分配失败\n");
            return NULL;
        }
        fscanf(file, "%d %s %d", &new_student->no, new_student->name, &new_student->score);


        new_student->next = NULL;
        if (head == NULL) {
            head = new_student;
            tail = new_student;
        }
        else {
            tail->next = new_student;
            tail = new_student;
        }

    }
    fclose(file);
    return head;
}
int main() {
    int m = 0; // 学生数量
    struct student* head = read(&m);
    if (head == NULL)
        return -1;
    head = SORT(head);
    if (head == NULL)
        return -1; 
    PRINT(head);
    FREE(head);
    return 0;
}