#include <iostream>
#include <string>

// Support ticket class representing a customer support request
class SupportTicket {
public:
    std::string customerName;
    std::string issue;
    std::string urgencyLevel;

    SupportTicket(const std::string& customer, const std::string& issue, const std::string& urgency)
        : customerName(customer), issue(issue), urgencyLevel(urgency) {}
};

// Abstract base class for support ticket handlers
class SupportHandler {
protected:
    SupportHandler* nextHandler;  // Reference to the next handler in the chain

public:
    explicit SupportHandler(SupportHandler* next) : nextHandler(next) {}

    virtual void HandleTicket(const SupportTicket& ticket) = 0;

    // Set the next handler in the chain
    void SetNextHandler(SupportHandler* next) {
        nextHandler = next;
    }
};

// Concrete support ticket handler for low urgency level
class LowUrgencyHandler : public SupportHandler {
public:
    explicit LowUrgencyHandler(SupportHandler* next) : SupportHandler(next) {}

    void HandleTicket(const SupportTicket& ticket) override {
        if (ticket.urgencyLevel == "Low") {
            std::cout << "LowUrgencyHandler: Handling support ticket with issue \"" << ticket.issue << "\" for customer "
                << ticket.customerName << std::endl;
        }
        else {
            // Pass the ticket to the next handler in the chain
            if (nextHandler) {
                nextHandler->HandleTicket(ticket);
            }
        }
    }
};

// Concrete support ticket handler for medium urgency level
class MediumUrgencyHandler : public SupportHandler {
public:
    explicit MediumUrgencyHandler(SupportHandler* next) : SupportHandler(next) {}

    void HandleTicket(const SupportTicket& ticket) override {
        if (ticket.urgencyLevel == "Medium") {
            std::cout << "MediumUrgencyHandler: Handling support ticket with issue \"" << ticket.issue << "\" for customer "
                << ticket.customerName << std::endl;
        }
        else {
            // Pass the ticket to the next handler in the chain
            if (nextHandler) {
                nextHandler->HandleTicket(ticket);
            }
        }
    }
};

// Concrete support ticket handler for high urgency level
class HighUrgencyHandler : public SupportHandler {
public:
    explicit HighUrgencyHandler(SupportHandler* next) : SupportHandler(next) {}

    void HandleTicket(const SupportTicket& ticket) override {
        if (ticket.urgencyLevel == "High") {
            std::cout << "HighUrgencyHandler: Handling support ticket with issue \"" << ticket.issue << "\" for customer "
                << ticket.customerName << std::endl;
        }
        else {
            // Pass the ticket to the next handler in the chain
            if (nextHandler) {
                nextHandler->HandleTicket(ticket);
            }
        }
    }
};


int main() {
    // Create the support ticket handlers in the chain
    SupportHandler* lowUrgencyHandler = new LowUrgencyHandler(nullptr);
    SupportHandler* mediumUrgencyHandler = new MediumUrgencyHandler(nullptr);
    SupportHandler* highUrgencyHandler = new HighUrgencyHandler(nullptr);

    // Set the next handlers in the chain
    lowUrgencyHandler->SetNextHandler(mediumUrgencyHandler);
    mediumUrgencyHandler->SetNextHandler(highUrgencyHandler);

    // Create some support tickets
    SupportTicket ticket1("John Doe", "Network connectivity issue", "Medium");
    SupportTicket ticket2("Jane Smith", "Billing discrepancy", "High");
    SupportTicket ticket3("Bob Johnson", "General inquiry", "Low");
    SupportTicket ticket4("Alice Anderson", "Website performance problem", "Medium");
    SupportTicket ticket5("David Brown", "Product feature request", "Low");
    SupportTicket ticket6("Sarah Wilson", "Critical system failure", "High");

    // Process the support tickets
    lowUrgencyHandler->HandleTicket(ticket1);
    lowUrgencyHandler->HandleTicket(ticket2);
    lowUrgencyHandler->HandleTicket(ticket3);
    lowUrgencyHandler->HandleTicket(ticket4);
    lowUrgencyHandler->HandleTicket(ticket5);
    lowUrgencyHandler->HandleTicket(ticket6);

    // Cleanup
    delete lowUrgencyHandler;
    delete mediumUrgencyHandler;
    delete highUrgencyHandler;

    return 0;
}
