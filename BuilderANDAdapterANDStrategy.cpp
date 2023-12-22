#include <iostream>
#include <vector>
using namespace std;

// 합계 금액
int total = 0;

// ######################################### 빌더 패턴
class Product
{
public:
    vector<string> items;
    vector<int> prices;

    void showDetails() const {
        cout << "Selected items and prices:" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i] << " - $" << prices[i] << endl;
        }
        cout << endl;
        cout << "Total Price: $" << TotalPrice() << endl;
        cout << "Total Quantity : " << items.size() << "ea\n" << endl << endl << endl;
    }

    int TotalPrice() const {
        total = 0;
        for (int price : prices) {
            total += price;
        }
        return total;
    }
};

class ProductBuilder {
public:
    Product product;

    ProductBuilder& selectItem(int itemNumber) {
        switch (itemNumber) {
        case 1:
            product.items.push_back("Egg");
            product.prices.push_back(4000);
            break;
        case 2:
            product.items.push_back("wheat flour");
            product.prices.push_back(3000);
            break;
        case 3:
            product.items.push_back("carrot");
            product.prices.push_back(800);
            break;
        case 4:
            product.items.push_back("potato");
            product.prices.push_back(1800);
            break;
        default:
            cout << "Invalid item number." << endl;
            break;
        }
        return *this;
    }

    Product build() const {
        return product;
    }
};

// ######################################### 전략 패턴
class PaymentClass
{
public:
    int retentionPoint = 0;

    virtual void pay()
    {
        cout << "Retention points: " << retentionPoint << endl;
    }
};

// 신용 카드 결제 전략
class CreditCardPayment : public PaymentClass
{
public:
    void pay() override
    {
        cout << "Credit Card" << endl;
        cout << "Payment Amount: " << total << endl << endl;
    }
};

// 무통장 입금 결제 전략
class DepositPayment : public PaymentClass
{
public:
    void pay() override
    {
        cout << "Deposit" << endl;
        cout << "Payment Amount: " << total << endl << endl;
    }
};

// 휴대폰 결제 전략
class PhonePayment : public PaymentClass {
public:
    void pay() override
    {
        cout << "Phone plan" << endl;
        cout << "Payment Amount: " << total << endl << endl;
    }
};

// 카카오페이 결제 전략
class KakaoPayment : public PaymentClass {
public:
    void pay() override
    {
        cout << "Kakao Pay" << endl;
        cout << "Payment Amount: " << total << endl << endl;
    }
};

// 외부 결제 시스템
class ExternalPaymentSystem {
public:
    void externalPay() {
        cout << "External Payment System" << endl;
        cout << "Payment Amount: " << total << endl << endl;
    }
};

// ######################################### 어댑터 패턴
// 어댑터 패턴을 사용한 외부 결제 시스템 어댑터
class ExternalPaymentAdapter : public PaymentClass {
private:
    ExternalPaymentSystem* externalPaymentSystem;

public:
    ExternalPaymentAdapter(ExternalPaymentSystem* externalSystem) : externalPaymentSystem(externalSystem) {}

    void pay() override {
        externalPaymentSystem->externalPay();
    }
};

// 결제를 처리하는 클래스
class PaymentContext
{
private:
    PaymentClass* paymentStrategy;

public:
    PaymentContext(PaymentClass* strategy) : paymentStrategy(strategy) {}

    void setPaymentStrategy(PaymentClass* strategy)
    {
        paymentStrategy = strategy;
    }

    void processPayment()
    {
        paymentStrategy->pay();
    }
};

// ######################################### main 함수
int main() {
    ProductBuilder builder;

    cout << "==========================================================================" << endl;
    cout << "Choose an item" << endl;
    string ingredients[] = { "Egg", "wheat flour", "carrot", "potato" };
    int quantities[] = { 10, 3, 1, 2 };
    int prices[] = { 4000, 3000, 800, 1800 };
    for (int i = 0; i < 4; ++i) {
        cout << i + 1 << ". " << ingredients[i] << ": " << quantities[i] << "ea, price: " << prices[i] << endl;
    }
    cout << "==========================================================================" << endl;

    do {
        cout << "Enter the item number (1-4) to add to the cart (or 0 to finish): ";
        int input;
        cin >> input;

        if (input == 0) {
            break;
        }

        builder.selectItem(input);
    } while (true);

    cout << endl;

    Product shoppingCart = builder.build();
    shoppingCart.showDetails();

    // 결제 방법 선택
    CreditCardPayment creditCardStrategy;
    DepositPayment depositStrategy;
    PhonePayment phoneStrategy;
    KakaoPayment kakaoStrategy;
    ExternalPaymentSystem externalSystem;
    ExternalPaymentAdapter externalPaymentAdapter(&externalSystem);

    cout << "==========================================================================" << endl;
    cout << "Choose the Payment Strategy" << endl;

    cout << "1. Credit Card" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Phone Plan" << endl;
    cout << "4. KakaoPay" << endl;
    cout << "5. External Payment" << endl;
    cout << "==========================================================================" << endl;

    cout << "Enter the payment strategy number (1-5): ";

    int input;
    cin >> input;

    PaymentContext paymentContext(&creditCardStrategy); // paymentContext 초기화

    switch (input)
    {
    case 1:
        cout << "Credit Card" << endl;
        cout << "Payment Amount : " << total << endl << endl;
        // 신용 카드로 결제
        paymentContext.processPayment();
        break;
    case 2:
        cout << "Deposit" << endl;
        cout << "Payment Amount : " << total << endl << endl;
        // 무통장 입금으로 결제
        paymentContext.setPaymentStrategy(&depositStrategy);
        paymentContext.processPayment();
        break;
    case 3:
        cout << "Phone Plan" << endl;
        cout << "Payment Amount : " << total << endl << endl;
        // 휴대폰으로 결제
        paymentContext.setPaymentStrategy(&phoneStrategy);
        paymentContext.processPayment();
        break;
    case 4:
        cout << "KakaoPay" << endl;
        cout << "Payment Amount : " << total << endl << endl;
        // 카카오페이로 결제
        paymentContext.setPaymentStrategy(&kakaoStrategy);
        paymentContext.processPayment();
        break;
    case 5:
        cout << "External Payment" << endl;
        cout << "Payment Amount : " << total << endl << endl;
        // 외부 결제 시스템으로 결제
        paymentContext.setPaymentStrategy(&externalPaymentAdapter);
        paymentContext.processPayment();
        break;
    default:
        cout << "Fail: Retry" << endl << endl;
        break;
    }

    return 0;
}
