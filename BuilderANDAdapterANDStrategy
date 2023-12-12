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
    virtual void pay() = 0;
};

// 신용 카드 결제 전략
class CreditCardPayment : public PaymentClass
{
public:
    void pay() override
    {
        cout << "Credit Card" << endl;
        cout << "Payment Amount : " << total << endl << endl;
    }
};

// 카카오페이 결제 전략
class KakaoPayment : public PaymentClass {
public:
    void pay() override
    {
        cout << "Kakao Pay" << endl;
        cout << "Payment Amount : " << total << endl << endl;
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
    string ingredients[] = { "Egg", "wheat flour", "carrot", "potato"};
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
    KakaoPayment kakaoStrategy;

    cout << "==========================================================================" << endl;
    cout << "Payment Strategy" << endl;
    cout << "==========================================================================" << endl;

    // 신용 카드로 결제
    PaymentContext paymentContext(&creditCardStrategy);
    paymentContext.processPayment();

    // 카카오페이로 변경
    paymentContext.setPaymentStrategy(&kakaoStrategy);
    paymentContext.processPayment();

    return 0;
}
