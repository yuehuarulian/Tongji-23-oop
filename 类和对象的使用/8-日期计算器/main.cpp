#include <iostream>
using namespace std;

class dateToDay
{
public:
    dateToDay(int y, int m, int d):year(y), month(m), day(d) {}    // 通过传参构建
    dateToDay() {}    // 构建时从键盘读入 实现方式二选一
    void setDate(int y, int m, int d) // 设置日期
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
    void setDate()// 从键盘读入设置日期 实现方式二选一
    {
        if (!checkValid())
        {
            cout << "Illegal" << endl;
            exit(0);
        }
    } 
    // 合法性检查应该在构建/设置时完成
    void display()    // 将计算结果输出(即本年内第几天)
    {
        //2097-9-23是2097年的第266天
        cout << year << '-' << month << '-' << day << "是" << year << "年的第" << computeDay() << "天" << endl;
    }
private:
    bool checkLeap()   // 该函数用于检查闰年并且更改day_的二月数据
    {
        if ((!(year % 4) && year % 100) || !(year % 400)) {
            day_[1]++;
            return true;
        }
        return false;
    }
 
    bool checkValid() // 该函数用于检查合法
    {
        if (year < 1 || year>9999)
            return false;
        if (month < 1 || month>12)
            return false;
        //闰年且是二月单独判断
        checkLeap();
        if (day<1 || day > day_[month - 1])
            return false;
        return true;
    }
    int computeDay()   // 该函数用于计算日期
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
    // 第一次构建时赋值
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
    // 第二次构建后赋值
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