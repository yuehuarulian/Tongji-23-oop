/*请任选 单链表-成绩管理-1/2 中的一种文件读取/动态内存申请方式，将其相关功能封装为函数 read()，
在本题中调用使用，自行设计函数结构。
分数段规定如下: 优 [90, 100], 良 [80, 90), 中 [70, 80), 及格 [60, 70), 不及格 [0, 60)。*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
const char* ch[5] = { "优","良","中","及格","不及格" };

// 学生结构体
struct student {
    int no;
    char name[20];
    int score;   
    int fd; //优:4, 良:3, 中:2, 及格:1, 不及格:0
    struct student* next;
};

int FD(int score)
{
    if (score >= 0 && score < 60)
        return 4;
    else if (score >= 60 && score < 70)
        return 3;
    else if (score >= 70 && score < 80)
        return 2;
    else if (score >= 80 && score < 90)
        return 1;
    else if (score >= 90 && score <= 100)
        return 0;
    else
    {
        printf("ERROR");
        return -1;
    }
}
void PRINT(int cn[])
{
//信息如下：优: 15人  良 : 4人  中 : 6人  及格 : 6人  不及格 : 21人
    printf("信息如下：\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d人  ", ch[i], cn[i]);
    }
    printf("\n");
}
void COUNT(struct student* head, int cn[])
{
    struct student* p = head;
    while (p != NULL) {
        cn[p->fd]++;
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
struct student* read(int *m)
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
        new_student->fd = FD(new_student->score);
        if (new_student->fd == -1)
            return NULL;

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
    int cn[5] = { 0 };
    int m = 0; // 学生数量
    struct student* head = read(&m);
    if (head == NULL)
        return -1;
    COUNT(head, cn);
    PRINT(cn);
    FREE(head);
    return 0;
}