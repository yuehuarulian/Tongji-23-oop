#include <iostream>
using namespace std;

class dateToDay
{
public:
    dateToDay(int y, int m, int d) :year(y), month(m), day(d) {}    // ͨ�����ι���
    dateToDay() {}    // ����ʱ�Ӽ��̶��� ʵ�ַ�ʽ��ѡһ
    void setDate(int y, int m, int d); // ��������
    void setDate()// �Ӽ��̶����������� ʵ�ַ�ʽ��ѡһ
    {
        if (!checkValid())
        {
            cout << "Illegal" << endl;
            exit(0);
        }
    } 
    // �Ϸ��Լ��Ӧ���ڹ���/����ʱ���
    void display();    // �����������(�������ڵڼ���)
private:
    bool checkLeap();  // �ú������ڼ������
 
    bool checkValid() // �ú������ڼ��Ϸ�
    {
        /*
 ��һ�֤Ϊ��������ʾҪ�������ڵ��꣬��Χ 1-9999��
�ڶ����ʾҪ�������ڵ��£��Ϸ�����Ϊ��������Χ 1-12������֮�⣬�п��ܻ�����ַ��򸡵����ȷǷ����ݡ�
�������ʾҪ�������ڵ��գ��Ϸ�����Ϊ��������Χ 1-28/29/30/31��������·��Լ����������ע�����ü�顣����֮�⣬�п��ܻ�����ַ��򸡵����ȷǷ����ݡ��Ƿ�������� Illegal
*/
        if (year < 1 || year>9999)
            return false;
        if (month < 1 || month>12)
            return false;
        //�������Ƕ��µ����ж�
        if (month == 2 && checkLeap()) {
            if (day < 1 || day>29)
                return false;
        }
        else {
            if (day<1 || day>day_[month - 1])
                return false;
        }
        return true;
    }
    int computeDay();  // �ú������ڼ�������
    int year;
    int month;
    int day;
    const int day_[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
};
int main()
{
    // ��һ�ι���ʱ��ֵ
    int year, month, day;
    cin >> year >> month >> day;
    if(!cin.good())
    {
        cout << "Illegal " << endl;
        return 0;
    }
    dateToDay data(year, month, day);
    data.setDate();
    data.display();
}