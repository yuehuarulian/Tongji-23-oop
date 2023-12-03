#include <iostream>

class Fahrenheit {
public:
    // ת�����캯��
    explicit Fahrenheit(double celsius) : temperature(celsius * 9.0 / 5.0 + 32.0) {}

    void display() {
        std::cout << "Temperature in Fahrenheit: " << temperature << " F" << std::endl;
    }

private:
    double temperature;
};

int main() {
    // ��ʽ����ת��
    Fahrenheit f(20.0);  // ʹ��ת�����캯���� double ����ת��Ϊ Fahrenheit ����
    f.display();

    return 0;
}
