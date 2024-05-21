#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

// 学生结构体
struct student {
    int no;                // 学号
    char name[20];         // 姓名
    int score;             // 成绩
    struct student* next;  // 下一结点
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
int main() {
    int m; // 学生数量
    FILE* file = fopen("student.txt", "r"); // 打开文件

    if (file == NULL) {
        printf("文件打开失败\n");
        return 1;
    }

    fscanf(file, "%d", &m); // 读取学生数量
    struct student* head = NULL;
    struct student* tail = NULL;

    for (int i = 0; i < m; i++) {
        struct student* new_student = (struct student*)malloc(sizeof(struct student));

        if (new_student == NULL) {
            printf("内存分配失败\n");
            return -1;
        }
        int no, score;
        char name[20];
        fscanf(file, "%d %s %d", &no, name, &score);
        new_student->no = no;
        for(int i=0;i<20;i++)
            new_student->name[i] = name[i];
        
        new_student->score = score;
       /* fscanf(file, "%d", &new_student->no);
        fscanf(file, "%s", new_student->name);
        fscanf(file, "%d",&new_student->score);*/
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

    PRINT(head);
    FREE(head);

    return 0;
}