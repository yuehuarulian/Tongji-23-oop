#include <conio.h>
#include <iostream>
#include "Matrix.h"
using namespace std;

// 此框架若有不完美可以在作业中任意修改

void wait_for_enter()
{
    cout << endl
        << "按回车键继续";
    while (_getch() != '\r')
        ;
    cout << endl
         << endl;
}

int main()
{
    int choice = 0;

    wait_for_enter();
    while (true) // 注意该循环退出的条件
    {
        system("cls"); // 清屏函数

        choice=menu(); // 调用菜单显示函数，自行补充完成

        // 按要求输入菜单选择项choice

        if (choice == '0') // 选择退出
        {
            char ch;
            cout << "\n确定退出吗?(输入 Y 或 N):" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
            // 下述矩阵操作函数自行设计并完成（包括函数参数及返回类型等），若选择加分项，请自行补充
            case '1':
                cout << "\n1.矩阵加法：" << endl;
                matriplus();
                break;
            case '2':
                cout << "\n2.矩阵数乘：" << endl;
                nummulti();
                break;
            case '3':
                cout << "\n3.矩阵转置：" << endl;
                matritrans();
                break;
            case '4':
                cout << "\n4.矩阵乘法：" << endl;
                matrimulti();
                break;
            case '5':
                cout << "\n5.Hadamard乘积" << endl;
                hadamulti();
                break;
            case '6':
                cout << "\n6.矩阵卷积：kernel size = 3，padding = 1，stride = 1，dilation = 1；" << endl;
                conv();
                break;
            case '7':
                cout << "\n7.卷积应用" << endl;
                demo();
                break;
            case '8':
                cout << "\n8.OTSU 算法" << endl;
                OTSU();
                break;
            case '9':
                cout << "\n9.其他加分项" << endl;
                cout << "实验室的团宠“雪球”-snowball.jpg (200*150)" << endl;
                plus_code("images/snowball.jpg");
                cout << "多角星形- polyhedrosis.jpg (98*90)" << endl;
                plus_code("images/polyhedrosis.jpg");
                cout << "船舰-ship.jpg (128*96)" << endl;
                plus_code("images/ship.jpg");
                cout << "脑部影像截取-brain.jpg (119*78)" << endl;
                plus_code("images/brain.jpg",5,6);
                break;
            case 'A':   
            case 'a': 
                cout << "\nA.自由发挥" << endl;
                free_act();
                break;
            default:
                cout << "\n输入错误，请从新输入" << endl;
                
        }
        
        cin.ignore(100000, '\n');
        wait_for_enter();
    }
    return 0;
}

