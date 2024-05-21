#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

// ѧ���ṹ��
struct student {
    int no;                // ѧ��
    char name[20];         // ����
    int score;             // �ɼ�
    struct student* next;  // ��һ���
};

void PRINT(struct student* head)
{
    printf("���е�ѧ����Ϣ���£�\n");
    struct student* p = head;
    while (p != NULL) {
        printf("ѧ��:%d ����:%s �ɼ�:%d\n", p->no, p->name, p->score);
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
    int m; // ѧ������
    FILE* file = fopen("student.txt", "r"); // ���ļ�

    if (file == NULL) {
        printf("�ļ���ʧ��\n");
        return 1;
    }

    fscanf(file, "%d", &m); // ��ȡѧ������
    struct student* head = NULL;
    struct student* tail = NULL;

    for (int i = 0; i < m; i++) {
        struct student* new_student = (struct student*)malloc(sizeof(struct student));

        if (new_student == NULL) {
            printf("�ڴ����ʧ��\n");
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