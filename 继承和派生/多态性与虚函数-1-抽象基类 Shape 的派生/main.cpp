#include <iostream>
#include <cmath>
#define MY_PI 3.1415926

using namespace std;


/**********************************************
*
*    TO-DO:
*        请补全该区域的代码。
*
***********************************************/
class Shape {
public:
    virtual double area() = 0;
};
class Circle :public Shape {
public:
    Circle(int r) :r(r) {}
    double area()
    {
        return MY_PI * r * r;
    }
private:
    int r;
};
class Square : public Shape {
public:
    Square(int a) :a(a) {}
    double area()
    {
        return a * a;
    }
private:
    int a;
};
class Rectangle : public Shape {
public:
    Rectangle(int a, int b) :a(a), b(b) {}
    double area()
    {
        return a * b;
    }
private:
    int a, b;
};
class Trapezoid : public Shape {
public:
    Trapezoid(int a, int b, int h) :a(a), b(b), h(h) {}
    double area()
    {
        return double(a + b) * h / 2;
    }
private:
    int a, b, h;
};
class Triangle : public Shape {
public:
    Triangle(int a, int b, int c) :a(a), b(b), c(c) {}
    double area()
    {
        double p = double(a + b + c) / 2;
        if ((p - a) <= 0 || (p - b) <= 0 || (p - c) <= 0)
            return -1;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
private:
    int a, b, c;
};
/**********************************************
*
*    TO-DO END
*
***********************************************/


int main() {
    Circle    c1(2);
    Square    s1(3);
    Rectangle r1(4, 5);
    Trapezoid t1(6, 7, 8);
    Triangle  t2(3, 4, 5);


    Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };


    for (int i = 0; i < 5; i++) {
        cout << s[i]->area() << endl;
    }
    return 0;
}