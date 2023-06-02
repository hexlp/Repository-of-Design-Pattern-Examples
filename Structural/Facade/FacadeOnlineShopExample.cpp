#include <iostream>

// Subsystem 1: Payment Gateway
class PaymentGateway {
public:
    void processPayment(const std::string& paymentInfo) {
        std::cout << "Processing payment: " << paymentInfo << std::endl;
        // Additional payment processing logic goes here
    }
};

// Subsystem 2: Shipping Service
class ShippingService {
public:
    void shipOrder(const std::string& address) {
        std::cout << "Shipping order to: " << address << std::endl;
        // Additional shipping logic goes here
    }
};

// Facade
class OnlineShop {
private:
    PaymentGateway paymentGateway;
    ShippingService shippingService;

public:
    void checkout(const std::string& paymentInfo, const std::string& shippingAddress) {
        std::cout << "Starting checkout process..." << std::endl;

        // Process payment
        paymentGateway.processPayment(paymentInfo);

        // Ship order
        shippingService.shipOrder(shippingAddress);

        std::cout << "Checkout complete." << std::endl;
    }
};

int main() {
    // Client code interacts with the online shop using the Facade
    OnlineShop onlineShop;

    // Simulate a checkout process
    onlineShop.checkout("Credit Card: 1234 5678 9012 3456", "123 Main St, City");

    return 0;
}
