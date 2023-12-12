#include <iostream>
using namespace std;

//외부 결제 시스템 인터페이스
class ExternalPaymentSystem {
public:
    virtual void processPayment() = 0;
};

//외부 결제 시스템
class ConcreteExternalPaymentSystem : public ExternalPaymentSystem {
public:
    void processPayment() override {
        cout << "외부 결제 시스템 성공" << endl;
    }
};

//내부 결제 시스템 인터페이스
class InternalPaymentSystem {
public:
    virtual void makePayment() = 0;
};

//내부 결제 시스템
class ConcreteInternalPaymentSystem : public InternalPaymentSystem {
public:
    void makePayment() override {
        cout << "내부 결제 시스템 성공" << endl;
    }
};

//Adapter 클래스: 외부 결제 시스템을 내부 결제 시스템에 통합
class ExternalToInternalPaymentAdapter : public InternalPaymentSystem {
private:
    ExternalPaymentSystem* externalPaymentSystem;

public:
    ExternalToInternalPaymentAdapter(ExternalPaymentSystem* externalSystem) : externalPaymentSystem(externalSystem) {}

    void makePayment() override {
        externalPaymentSystem->processPayment();
    }
};

int main() {
    //내부 결제 시스템을 사용
    InternalPaymentSystem* internalPayment = new ConcreteInternalPaymentSystem();
    internalPayment->makePayment();

    //외부 결제 시스템을 내부 시스템에 통합하여 사용하는 경우 (Adapter 사용)
    ExternalPaymentSystem* externalPayment = new ConcreteExternalPaymentSystem();
    InternalPaymentSystem* adapter = new ExternalToInternalPaymentAdapter(externalPayment);
    adapter->makePayment();

    delete internalPayment;
    delete externalPayment;
    delete adapter;

    return 0;
}
