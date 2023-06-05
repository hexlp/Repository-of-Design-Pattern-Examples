#include <iostream>
#include <string>

class PurchaseRequest {
public:
    PurchaseRequest(const std::string& description, double amount)
        : description_(description), amount_(amount) {}

    std::string GetDescription() const {
        return description_;
    }

    double GetAmount() const {
        return amount_;
    }

private:
    std::string description_;
    double amount_;
};

class Approver {
public:
    Approver(Approver* successor)
        : successor_(successor) {}

    virtual void ProcessRequest(const PurchaseRequest& request) = 0;

protected:
    Approver* successor_;
};

class Manager : public Approver {
public:
    Manager(Approver* successor)
        : Approver(successor) {}

    void ProcessRequest(const PurchaseRequest& request) override {
        if (request.GetAmount() <= 1000.0) {
            std::cout << "Manager approved the purchase: " << request.GetDescription() << std::endl;
        } else if (successor_) {
            successor_->ProcessRequest(request);
        }
    }
};

class Director : public Approver {
public:
    Director(Approver* successor)
        : Approver(successor) {}

    void ProcessRequest(const PurchaseRequest& request) override {
        if (request.GetAmount() <= 5000.0) {
            std::cout << "Director approved the purchase: " << request.GetDescription() << std::endl;
        } else if (successor_) {
            successor_->ProcessRequest(request);
        }
    }
};

class CEO : public Approver {
public:
    CEO()
        : Approver(nullptr) {}

    void ProcessRequest(const PurchaseRequest& request) override {
        std::cout << "CEO approved the purchase: " << request.GetDescription() << std::endl;
    }
};

int main() {
    // Create the chain of approvers
    CEO ceo;
    Director director(&ceo);
    Manager manager(&director);

    // Create purchase requests
    PurchaseRequest request1("Office supplies", 800.0);
    PurchaseRequest request2("New equipment", 3500.0);
    PurchaseRequest request3("Conference sponsorship", 10000.0);

    // Process the purchase requests
    manager.ProcessRequest(request1);
    manager.ProcessRequest(request2);
    manager.ProcessRequest(request3);

    return 0;
}
