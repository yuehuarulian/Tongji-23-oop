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
    /*
    ��һ�֤Ϊ��������ʾҪ�������ڵ��꣬��Χ 1-9999��
�ڶ����ʾҪ�������ڵ��£��Ϸ�����Ϊ��������Χ 1-12������֮�⣬�п��ܻ�����ַ��򸡵����ȷǷ����ݡ�
�������ʾҪ�������ڵ��գ��Ϸ�����Ϊ��������Χ 1-28/29/30/31��������·��Լ����������ע�����ü�顣����֮�⣬�п��ܻ�����ַ��򸡵����ȷǷ����ݡ��Ƿ�������� Illegal 
*/
    bool checkValid() // �ú������ڼ��Ϸ�
    {
        if(year<)
    }
    int computeDay();  // �ú������ڼ�������
    int year;
    int month;
    int day;
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