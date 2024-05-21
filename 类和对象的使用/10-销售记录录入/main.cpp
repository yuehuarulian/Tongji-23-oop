#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

class Book_Sale
{
private:
    char* isbn; // ָ���鼮��ŵ�ָ��
    // ����鼮��ŵĿռ��趯̬����
    // �鼮����� 5 �� 13 λ������ɣ��� 978-7-121-15535-2
    int    sales_volume;   // ������
    double original_price; // ԭʼ�۸�
    double real_price;     // ʵ�ۼ۸�
    double discount;       // �ۿ�
    double gross_sales;    // �����ܶ�
    const char* isbn_bgn = "978-7-121";
public:
    /* ���Խ��� istream & �����ж�ȡ�鼮������Ϣ�Ĺ��캯��Book_Sale (istream &)�����������Լ�������Ҫ�ĳ�Ա���� */
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
    gross_sales = real_price * sales_volume;    // �����ܶ�
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
    gross_sales = real_price * sales_volume;    // �����ܶ�
}
void Book_Sale::show_value()
{
    cout  << "�����ISBN��Ϊ:" << isbn << endl;
    cout << setprecision(0) << "����Ϊ:" << setiosflags(ios::fixed) << setprecision(6) << sales_volume << "�� ԭ��Ϊ:" << original_price << "Ԫ �ۿ�Ϊ : " << discount << " �ּ�Ϊ : " << real_price << "Ԫ �����۶�Ϊ : " << gross_sales << "Ԫ" << endl;
}
Book_Sale::~Book_Sale()
{
    delete[]isbn;
}
/*
�����ISBN��Ϊ:978-7-121-15535-2
����Ϊ:200�� ԭ��Ϊ:128.000Ԫ �ۿ�Ϊ:0.800 �ּ�Ϊ:102.400Ԫ �����۶�Ϊ:20480.000Ԫ
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