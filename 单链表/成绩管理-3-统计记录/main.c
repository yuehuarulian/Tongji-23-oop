/*����ѡ ������-�ɼ�����-1/2 �е�һ���ļ���ȡ/��̬�ڴ����뷽ʽ��������ع��ܷ�װΪ���� read()��
�ڱ����е���ʹ�ã�������ƺ����ṹ��
�����ι涨����: �� [90, 100], �� [80, 90), �� [70, 80), ���� [60, 70), ������ [0, 60)��*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
const char* ch[5] = { "��","��","��","����","������" };

// ѧ���ṹ��
struct student {
    int no;
    char name[20];
    int score;   
    int fd; //��:4, ��:3, ��:2, ����:1, ������:0
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
//��Ϣ���£���: 15��  �� : 4��  �� : 6��  ���� : 6��  ������ : 21��
    printf("��Ϣ���£�\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %d��  ", ch[i], cn[i]);
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
    FILE* file = fopen("student.txt", "r"); // ���ļ�

    if (file == NULL) {
        printf("�ļ���ʧ��\n");
        return NULL;
    }

    fscanf(file, "%d", m); // ��ȡѧ������
    for (int i = 0; i < *m; i++) {
        struct student* new_student = (struct student*)malloc(sizeof(struct student));
        if (new_student == NULL) {
            printf("�ڴ����ʧ��\n");
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
    int m = 0; // ѧ������
    struct student* head = read(&m);
    if (head == NULL)
        return -1;
    COUNT(head, cn);
    PRINT(cn);
    FREE(head);
    return 0;
}