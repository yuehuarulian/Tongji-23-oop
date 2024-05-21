#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

// ѧ���ṹ��
struct student {
    int no;
    char name[20];
    int score;
    struct student* next;
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

struct student* read(int* m)
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
    int m = 0; // ѧ������
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