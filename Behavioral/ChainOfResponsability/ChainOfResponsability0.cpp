/*
The Chain of Responsibility pattern is a behavioral design pattern that allows an 
object to pass a request along a chain of potential handlers until the request is 
handled or reaches the end of the chain. Each handler in the chain has the ability 
to handle the request or pass it to the next handler in the chain.

The key components of this pattern are:
- Request: Represents a request to be processed. It contains the necessary 
  information for the handlers to make a decision on how to handle it.
  
- Handler: Defines an interface for handling requests. It has a reference 
  to the next handler in the chain and handles the request if it is capable of doing so.
  Otherwise, it delegates the request to the next handler in the chain.
  
- Concrete Handlers: Implement the Handler interface and provide the actual 
  implementation for handling the requests. Each concrete handler decides whether 
  to handle the request or pass it to the next handler.

The Chain of Responsibility pattern promotes loose coupling between the sender 
of a request and its receivers. It allows multiple objects to have a chance to 
handle the request without the sender having knowledge of the specific handlers 
or their order in the chain. It also provides flexibility in dynamically changing 
the chain of handlers during runtime.

This pattern is commonly used in scenarios where a request needs to be processed 
by multiple objects in a predefined order, and the specific handler for a request 
may vary based on the runtime conditions or the nature of the request itself. 
Examples include request handling pipelines, event handling systems, and logging systems with different log levels.

The benefits of using the Chain of Responsibility pattern include improved flexibility, extensibility, and reusability of the code. 
It enables the addition or removal of handlers without affecting the client code, and allows handlers to be reused in different chains or combinations.

*/


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
