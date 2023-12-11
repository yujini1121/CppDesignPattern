#include <iostream>
using namespace std;

// 도형 추상 클래스
class Shape {
public:
    virtual void draw() = 0;
};

// 원 클래스
class Circle : public Shape {
public:
    void draw() override {
        cout << "원을 그립니다." << endl;
    }
};

// 사각형 클래스
class Rectangle : public Shape {
public:
    void draw() override {
        cout << "사각형을 그립니다." << endl;
    }
};

// 도형 팩토리 인터페이스
class ShapeFactory {
public:
    virtual Shape* createShape() = 0;
};

// 원 팩토리 클래스
class CircleFactory : public ShapeFactory {
public:
    Shape* createShape() override {
        return new Circle();
    }
};

// 사각형 팩토리 클래스
class RectangleFactory : public ShapeFactory {
public:
    Shape* createShape() override {
        return new Rectangle();
    }
};

int main() {
    // 팩토리를 이용하여 도형 생성
    ShapeFactory* circleFactory = new CircleFactory();
    Shape* circle = circleFactory->createShape();
    circle->draw();

    ShapeFactory* rectangleFactory = new RectangleFactory();
    Shape* rectangle = rectangleFactory->createShape();
    rectangle->draw();

    // 메모리 해제
    delete circleFactory;
    delete circle;
    delete rectangleFactory;
    delete rectangle;

    return 0;
}
