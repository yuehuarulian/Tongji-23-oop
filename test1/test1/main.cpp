#include <iostream>

class Fahrenheit {
public:
    // 转换构造函数
    explicit Fahrenheit(double celsius) : temperature(celsius * 9.0 / 5.0 + 32.0) {}

    void display() {
        std::cout << "Temperature in Fahrenheit: " << temperature << " F" << std::endl;
    }

private:
    double temperature;
};

int main() {
    // 隐式类型转换
    Fahrenheit f(20.0);  // 使用转换构造函数将 double 类型转换为 Fahrenheit 类型
    f.display();

    return 0;
}
