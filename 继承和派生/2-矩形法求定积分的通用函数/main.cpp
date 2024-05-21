#include <iostream>
#include <cmath>


using namespace std;


/**********************************************
*
*    TO-DO:
*        请补全该区域的代码。
*
***********************************************/
class integral {
public:
    double value() 
    {
        double sum = 0;
        double detax = (b - a) / 10000;
        for (int i = 0; i <= 10000; i++) {
            double x = a + detax * i;
            sum += calcu(x) * detax;
        }
        return sum;
    }
    double a, b;
protected:
    virtual double calcu(double x) { return 0; };//空虚函数
};
class integral_sin :public integral{
protected:
    virtual double calcu(double x)
    {
        return sin(x);
    }
};
class integral_cos :public integral {
protected:
    virtual double calcu(double x)
    {
        return cos(x);
    }
};
class integral_exp :public integral {
protected:
    virtual double calcu(double x)
    {
        return exp(x);
    }
};
istream& operator >>(istream& in, integral& itg)
{
    cin >> itg.a >> itg.b;
    return in;
}
/**********************************************
*
*    TO-DO END
*
***********************************************/


int main()
{
    integral_sin s1;
    integral_cos s2;
    integral_exp s3;
    integral* p;


    cout << "请输入上下限：";
    cin >> s1;
    p = &s1;
    cout << "∫sinxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s2;
    p = &s2;
    cout << "∫cosxdx的计算结果为：" << (p->value()) << endl;


    cout << "请输入上下限：";
    cin >> s3;
    p = &s3;
    cout << "∫expxdx的计算结果为：" << (p->value()) << endl;


    return 0;
}