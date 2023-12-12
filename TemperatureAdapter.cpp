#include <iostream>
#include <string>

// 새로운 인터페이스를 제공하는 타겟 클래스
class Temperature {
public:
    virtual double getTemperature() const = 0;
    virtual void setTemperature(double temp) = 0;
};

// 기존의 클래스로 화씨와 섭씨를 동시에 가지고 있는 클래스
class DualTemperature : public Temperature {
private:
    double fahrenheitTemperature;
    double celsiusTemperature;

public:
    double getTemperature() const override {
        return fahrenheitTemperature;
    }

    void setTemperature(double temp) override {
        fahrenheitTemperature = temp;
        celsiusTemperature = (temp - 32.0) * 5.0 / 9.0;
    }

    double getCelsiusTemperature() const {
        return celsiusTemperature;
    }
};

// 양방향 어댑터 클래스
class BidirectionalTemperatureAdapter : public Temperature {
private:
    DualTemperature dualTemperatureObject;

public:
    double getTemperature() const override {
        // 여기서는 화씨 값을 반환
        return dualTemperatureObject.getTemperature();
    }

    void setTemperature(double temp) override {
        // 여기서는 화씨 값을 설정하고, 동시에 섭씨 값을 업데이트
        dualTemperatureObject.setTemperature(temp);
    }

    double getCelsiusTemperature() const {
        // 섭씨 값을 반환
        return dualTemperatureObject.getCelsiusTemperature();
    }

    void setCelsiusTemperature(double temp) {
        // 섭씨 값을 설정하고, 동시에 화씨 값을 업데이트
        dualTemperatureObject.setTemperature(temp * 9.0 / 5.0 + 32.0);
    }
};

// 사용자로부터 화씨 또는 섭씨 온도를 입력받아 변환하는 함수
void convertTemperature(BidirectionalTemperatureAdapter& adapter) {
    std::string scale;
    double temperature;

    std::cout << " temperature scale(C for Celsius, F for Fahrenheit) : ";
    std::cin >> scale;

    if (scale == "C" || scale == "c") {
        std::cout << "Celsius: ";
        std::cin >> temperature;
        adapter.setCelsiusTemperature(temperature);
        std::cout << "Fagrenhet: " << adapter.getTemperature() << "°F" << std::endl;
    }
    else if (scale == "F" || scale == "f") {
        std::cout << "Fahrenheit: ";
        std::cin >> temperature;
        adapter.setTemperature(temperature);
        std::cout << "Celsius: " << adapter.getCelsiusTemperature() << "°C" << std::endl;
    }
    else {
        std::cerr << "올바르지 않은 값" << std::endl;
    }
}

int main() {
    // 양방향 어댑터를 사용하여 화씨와 섭씨를 변환
    BidirectionalTemperatureAdapter adapter;

    // 사용자로부터 입력을 받아 변환
    convertTemperature(adapter);

    return 0;
}
