#include <conio.h>
#include <iostream>
#include "Matrix.h"
using namespace std;

// �˿�����в�������������ҵ�������޸�

void wait_for_enter()
{
    cout << endl
        << "���س�������";
    while (_getch() != '\r')
        ;
    cout << endl
         << endl;
}

int main()
{
    int choice = 0;

    wait_for_enter();
    while (true) // ע���ѭ���˳�������
    {
        system("cls"); // ��������

        choice=menu(); // ���ò˵���ʾ���������в������

        // ��Ҫ������˵�ѡ����choice

        if (choice == '0') // ѡ���˳�
        {
            char ch;
            cout << "\nȷ���˳���?(���� Y �� N):" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
            // ���������������������Ʋ���ɣ����������������������͵ȣ�����ѡ��ӷ�������в���
            case '1':
                cout << "\n1.����ӷ���" << endl;
                matriplus();
                break;
            case '2':
                cout << "\n2.�������ˣ�" << endl;
                nummulti();
                break;
            case '3':
                cout << "\n3.����ת�ã�" << endl;
                matritrans();
                break;
            case '4':
                cout << "\n4.����˷���" << endl;
                matrimulti();
                break;
            case '5':
                cout << "\n5.Hadamard�˻�" << endl;
                hadamulti();
                break;
            case '6':
                cout << "\n6.��������kernel size = 3��padding = 1��stride = 1��dilation = 1��" << endl;
                conv();
                break;
            case '7':
                cout << "\n7.���Ӧ��" << endl;
                demo();
                break;
            case '8':
                cout << "\n8.OTSU �㷨" << endl;
                OTSU();
                break;
            case '9':
                cout << "\n9.�����ӷ���" << endl;
                cout << "ʵ���ҵ��ų衰ѩ��-snowball.jpg (200*150)" << endl;
                plus_code("images/snowball.jpg");
                cout << "�������- polyhedrosis.jpg (98*90)" << endl;
                plus_code("images/polyhedrosis.jpg");
                cout << "����-ship.jpg (128*96)" << endl;
                plus_code("images/ship.jpg");
                cout << "�Բ�Ӱ���ȡ-brain.jpg (119*78)" << endl;
                plus_code("images/brain.jpg",5,6);
                break;
            case 'A':   
            case 'a': 
                cout << "\nA.���ɷ���" << endl;
                free_act();
                break;
            default:
                cout << "\n����������������" << endl;
                
        }
        
        cin.ignore(100000, '\n');
        wait_for_enter();
    }
    return 0;
}

