#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

class Book_Sale
{
private:
    char* isbn; // 指向书籍编号的指针
    // 存放书籍编号的空间需动态申请
    // 书籍编号由 5 段 13 位数字组成，如 978-7-121-15535-2
    int    sales_volume;   // 销售量
    double original_price; // 原始价格
    double real_price;     // 实售价格
    double discount;       // 折扣
    double gross_sales;    // 销售总额
    const char* isbn_bgn = "978-7-121";
public:
    /* 可以接受 istream & 并从中读取书籍销售信息的构造函数Book_Sale (istream &)，析构函数以及其他必要的成员函数 */
    Book_Sale(istream&);
    Book_Sale() = default;
    void set(char *s, int sv, double op, double ds);
    void show_value();
    ~Book_Sale();
};
Book_Sale::Book_Sale(istream& in)
{
    //isbn
    char s[10];
    in >> s;
    isbn = new(nothrow) char[20];
    if (isbn == NULL)
        exit(-1);
    strcpy(isbn, isbn_bgn);
    strcat(isbn, "-");
    int len = int (strlen(s));
    for (int i = 5 - len; i; i--) {
        strcat(isbn, "0");
    }
    strcat(isbn, s);
    strcat(isbn, "-");
    int r = 10 - (9 + 3 * 7 + 8 + 3 * 7 + 1 + 3 * 2 + 1 + 3 * (isbn[10] - '0') + (isbn[11] - '0') + 3 * (isbn[12] - '0') + (isbn[13] - '0') + 3 * (isbn[14] - '0')) % 10;
    char x[2] = { '\0' };
    x[0] = r % 10 + '0';
    strcat(isbn, x);

    //
    in >> sales_volume >> original_price >> discount;
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;    // 销售总额
}
void Book_Sale::set(char *s, int sv, double op, double ds)
{
    //isbn
    isbn = new(nothrow) char[20];
    if (isbn == NULL)
        exit(-1);
    strcpy(isbn, isbn_bgn);
    strcat(isbn, "-");
    int len = int(strlen(s));
    for (int i = 5 - len; i; i--) {
        strcat(isbn, "0");
    }
    strcat(isbn, s);
    strcat(isbn, "-");
    int r = 10 - (9 + 3 * 7 + 8 + 3 * 7 + 1 + 3 * 2 + 1 + 3 * (isbn[10] - '0') + (isbn[11] - '0') + 3 * (isbn[12] - '0') + (isbn[13] - '0') + 3 * (isbn[14] - '0')) % 10;
    char x[2] = { '\0' };
    x[0] = r % 10 + '0';
    strcat(isbn, x);

    //
    sales_volume = sv;
    original_price = op;
    discount = ds;
    real_price = original_price * discount;
    gross_sales = real_price * sales_volume;    // 销售总额
}
void Book_Sale::show_value()
{
    cout  << "该书的ISBN号为:" << isbn << endl;
    cout << setprecision(0) << "销量为:" << setiosflags(ios::fixed) << setprecision(6) << sales_volume << "本 原价为:" << original_price << "元 折扣为 : " << discount << " 现价为 : " << real_price << "元 总销售额为 : " << gross_sales << "元" << endl;
}
Book_Sale::~Book_Sale()
{
    delete[]isbn;
}
/*
该书的ISBN号为:978-7-121-15535-2
销量为:200本 原价为:128.000元 折扣为:0.800 现价为:102.400元 总销售额为:20480.000元
*/
int main()
{
    Book_Sale book(cin);
    book.show_value();
    char s[10] = { '\0' };
    int sales_volume;
    double original_price, discount;
    while (cin >> s) {
        if (!strcmp(s, "-1"))
            break;
        else
            cin >> sales_volume >> original_price >> discount;
        Book_Sale book;
        book.set(s, sales_volume, original_price, discount);
        book.show_value();
    }
}