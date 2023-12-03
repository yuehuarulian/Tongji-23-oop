#include <iostream>
using namespace std;

class dateToDay
{
public:
    dateToDay(int y, int m, int d) :year(y), month(m), day(d) {}    // 通过传参构建
    dateToDay() {}    // 构建时从键盘读入 实现方式二选一
    void setDate(int y, int m, int d); // 设置日期
    void setDate()// 从键盘读入设置日期 实现方式二选一
    {
        if (!checkValid())
        {
            cout << "Illegal" << endl;
            exit(0);
        }
    } 
    // 合法性检查应该在构建/设置时完成
    void display();    // 将计算结果输出(即本年内第几天)
private:
    bool checkLeap();  // 该函数用于检查闰年
    /*
    第一项保证为整数，表示要计算日期的年，范围 1-9999。
第二项表示要计算日期的月，合法数据为整数，范围 1-12。除此之外，有可能会给出字符或浮点数等非法数据。
第三项表示要计算日期的日，合法数据为整数，范围 1-28/29/30/31，需根据月份以及闰年决定，注意做好检查。除此之外，有可能会给出字符或浮点数等非法数据。非法数据输出 Illegal 
*/
    bool checkValid() // 该函数用于检查合法
    {
        if(year<)
    }
    int computeDay();  // 该函数用于计算日期
    int year;
    int month;
    int day;
};
int main()
{
    // 第一次构建时赋值
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