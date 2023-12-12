#include <iostream>
using namespace std;

// LinuxCalculator 클래스
class LinuxCalculator 
{
public:
    double execute(double n1, double n2) 
		{ //두 숫자(n1, n2)를 더하고 결과를 반환
        cout << "리눅스" << endl;
        return n1 + n2;
    }
};

// WindowCalculator 클래스
class WindowCalculator 
{
public:
    double execute(double n1, double n2) 
		{ ////두 숫자(n1, n2)를 더하고 결과를 반환
        cout << "윈도우" << endl;
        return n1 + n2;
    }
};

// CalculatorAdapter 클래스 (리눅스 계산기(LinuxCalculator) 의 자식 클래스임)
class CalculatorAdapter : public LinuxCalculator 
{
private:
    WindowCalculator calculator; //윈도우 계산기 클래스를 포함(어댑터 역할을 함!)

public:
    CalculatorAdapter(WindowCalculator cal) : calculator(cal) {} //생성자에서 윈도우계산기클래스의 객체를 받음

    //부모 클래스(리눅스 클래스)의 메서드를 오버라이딩
    // (아래 코드가 없다면 원래 리눅스 클래스의 계산기를 실행하겠지만 
    // 오버라이딩으로 인해 윈도우 계산기 클래스의 메서드를 실행하게 됨)
    double execute(double n1, double n2) 
	{ 
        cout << "어댑터 변환 : ";
        return calculator.execute(n1, n2);
    }
};

int main() 
{
    // Linux 계산기
    LinuxCalculator linuxCalculator;
    double result1 = linuxCalculator.execute(1, 2);

    // Windows 계산기
    WindowCalculator windowCalculator;
    double result2 = windowCalculator.execute(3, 4);

    // Linux 환경에서 Window 계산기를 사용할 수 있는 기능을 어댑터를 사용하여 변경
    CalculatorAdapter calculatorAdapter(windowCalculator);
    double result3 = calculatorAdapter.execute(5, 6);

    std::cout << result1 << std::endl;
    std::cout << result2 << std::endl;
    std::cout << result3 << std::endl;

    return 0;
}
