#include <iostream>
using namespace std;

class dateToDay
{
public:
    dateToDay(int y, int m, int d):year(y), month(m), day(d) {}    // ͨ�����ι���
    dateToDay() {}    // ����ʱ�Ӽ��̶��� ʵ�ַ�ʽ��ѡһ
    void setDate(int y, int m, int d) // ��������
    {
        year = y;
        month = m;
        day = d;
        if (!checkValid())
        {
            cout << "Illegal" << endl;
            exit(0);
        }
    }
    void setDate()// �Ӽ��̶����������� ʵ�ַ�ʽ��ѡһ
    {
        if (!checkValid())
        {
            cout << "Illegal" << endl;
            exit(0);
        }
    } 
    // �Ϸ��Լ��Ӧ���ڹ���/����ʱ���
    void display()    // �����������(�������ڵڼ���)
    {
        //2097-9-23��2097��ĵ�266��
        cout << year << '-' << month << '-' << day << "��" << year << "��ĵ�" << computeDay() << "��" << endl;
    }
private:
    bool checkLeap()   // �ú������ڼ�����겢�Ҹ���day_�Ķ�������
    {
        if ((!(year % 4) && year % 100) || !(year % 400)) {
            day_[1]++;
            return true;
        }
        return false;
    }
 
    bool checkValid() // �ú������ڼ��Ϸ�
    {
        if (year < 1 || year>9999)
            return false;
        if (month < 1 || month>12)
            return false;
        //�������Ƕ��µ����ж�
        checkLeap();
        if (day<1 || day > day_[month - 1])
            return false;
        return true;
    }
    int computeDay()   // �ú������ڼ�������
    {
        int sum = 0;
        for (int i = 0; i < month - 1; i++) {
            sum += day_[i];
        }
        sum += day;
        return sum;
    }
    int year;
    int month;
    int day;
    int day_[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
};
int main()
{
    // ��һ�ι���ʱ��ֵ
    int year, month, day;
    cin >> year >> month >> day;
    if(!cin.good())
    {
        cout << "Illegal" << endl;
        return 0;
    }
    dateToDay data1(year, month, day);
    data1.setDate();
    data1.display();
    // �ڶ��ι�����ֵ
    dateToDay data2;
    cin >> year >> month >> day;
    if (!cin.good())
    {
        cout << "Illegal" << endl;
        return 0;
    }
    data2.setDate(year, month, day);
    data2.display();
    return 0;
}