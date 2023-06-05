#include <iostream>
#include <string>

// Order class representing the order information
class Order {
public:
    std::string customerName;
    double orderAmount;

    Order(const std::string& customer, double amount) : customerName(customer), orderAmount(amount) {}
};

// Abstract base class for order processors
class OrderProcessor {
protected:
    OrderProcessor* nextProcessor;  // Reference to the next processor in the chain

public:
    explicit OrderProcessor(OrderProcessor* next) : nextProcessor(next) {}

    virtual void ProcessOrder(Order& order) = 0;

    // Set the next processor in the chain
    void SetNextProcessor(OrderProcessor* next) {
        nextProcessor = next;
    }
};

// Concrete order processor for payment validation
class PaymentProcessor : public OrderProcessor {
public:
    explicit PaymentProcessor(OrderProcessor* next) : OrderProcessor(next) {}

    void ProcessOrder(Order& order) override {
        if (order.orderAmount > 0) {
            std::cout << "PaymentProcessor: Payment validated for customer " << order.customerName << std::endl;
            // Proceed to the next processor in the chain
            if (nextProcessor) {
                nextProcessor->ProcessOrder(order);
            }
        } else {
            std::cout << "PaymentProcessor: Invalid order amount for customer " << order.customerName << std::endl;
        }
    }
};

// Concrete order processor for inventory check
class InventoryProcessor : public OrderProcessor {
public:
    explicit InventoryProcessor(OrderProcessor* next) : OrderProcessor(next) {}

    void ProcessOrder(Order& order) override {
        if (order.orderAmount <= 10) {
            std::cout << "InventoryProcessor: Sufficient inventory available for customer " << order.customerName << std::endl;
            // Proceed to the next processor in the chain
            if (nextProcessor) {
                nextProcessor->ProcessOrder(order);
            }
        } else {
            std::cout << "InventoryProcessor: Insufficient inventory for customer " << order.customerName << std::endl;
        }
    }
};

// Concrete order processor for order confirmation
class ConfirmationProcessor : public OrderProcessor {
public:
    explicit ConfirmationProcessor(OrderProcessor* next) : OrderProcessor(next) {}

    void ProcessOrder(Order& order) override {
        std::cout << "ConfirmationProcessor: Sending order confirmation to customer " << order.customerName << std::endl;
        // No need to proceed to the next processor as this is the last in the chain
    }
};

int main() {
    // Create the order processors in the chain
    OrderProcessor* paymentProcessor = new PaymentProcessor(nullptr);
    OrderProcessor* inventoryProcessor = new InventoryProcessor(nullptr);
    OrderProcessor* confirmationProcessor = new ConfirmationProcessor(nullptr);

    // Set the next processors in the chain
    paymentProcessor->SetNextProcessor(inventoryProcessor);
    inventoryProcessor->SetNextProcessor(confirmationProcessor);

    // Create an order
    Order order("John Doe", 8.5);

    // Process the order
    paymentProcessor->ProcessOrder(order);

    // Cleanup
    delete paymentProcessor;
    delete inventoryProcessor;
    delete confirmationProcessor;

    return 0;
}
