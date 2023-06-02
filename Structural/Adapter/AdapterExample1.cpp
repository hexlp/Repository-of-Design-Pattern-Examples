#include <iostream>
#include <string>

// PaymentGateway is the target interface that the client expects to interact with
class PaymentGateway {
public:
    virtual void processPayment(float amount) = 0;
};

// PayPalGateway is a concrete implementation of the PaymentGateway interface
class PayPalGateway : public PaymentGateway {
public:
    void processPayment(float amount) override {
        std::cout << "Processing payment of $" << amount << " via PayPal." << std::endl;
        // Actual PayPal payment processing code here
        std::cout << "Payment processed successfully." << std::endl;
    }
};

// StripeGateway is a concrete implementation of the PaymentGateway interface
class StripeGateway : public PaymentGateway {
public:
    void processPayment(float amount) override {
        std::cout << "Processing payment of $" << amount << " via Stripe." << std::endl;
        // Actual Stripe payment processing code here
        std::cout << "Payment processed successfully." << std::endl;
    }
};

// ThirdPartyPaymentGateway is the interface for a third-party payment gateway
class ThirdPartyPaymentGateway {
public:
    virtual void executePayment(float amount) = 0;
};

// Adapting the PayPalGateway to the ThirdPartyPaymentGateway interface
class PayPalGatewayAdapter : public ThirdPartyPaymentGateway {
public:
    PayPalGatewayAdapter(PaymentGateway* paymentGateway) : paymentGateway_(paymentGateway) {}

    void executePayment(float amount) override {
        paymentGateway_->processPayment(amount);
    }

private:
    PaymentGateway* paymentGateway_;
};

int main() {
    // Client code
    PaymentGateway* paypalGateway = new PayPalGateway();
    ThirdPartyPaymentGateway* adapter = new PayPalGatewayAdapter(paypalGateway);
    adapter->executePayment(100.0f);

    std::cout << "-----------------" << std::endl;

    PaymentGateway* stripeGateway = new StripeGateway();
    adapter = new PayPalGatewayAdapter(stripeGateway);
    adapter->executePayment(200.0f);

    delete paypalGateway;
    delete adapter;
    delete stripeGateway;

    return 0;
}
