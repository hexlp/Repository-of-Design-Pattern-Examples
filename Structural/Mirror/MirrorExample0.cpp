#include <iostream>
#include <string>

// Forward declaration of Twin class
class Twin;

// Base class representing a distributed system component
class DistributedComponent {
public:
    virtual void updateState(const std::string& newState) = 0;
    virtual void syncState(Twin* twin) = 0;
};

// Twin class representing a synchronized twin component
class Twin : public DistributedComponent {
private:
    std::string state_;
    Twin* twin_;

public:
    void updateState(const std::string& newState) override {
        state_ = newState;
        std::cout << "Twin state updated to: " << state_ << std::endl;
    }

    void syncState(Twin* twin) override {
        twin_ = twin;
        twin_->updateState(state_);
        std::cout << "Twin state synchronized" << std::endl;
    }

    void sendData(const std::string& data) {
        if (twin_) {
            std::cout << "Sending data to twin: " << data << std::endl;
            twin_->receiveData(data);
        }
    }

    void receiveData(const std::string& data) {
        std::cout << "Received data from twin: " << data << std::endl;
    }
};

int main() {
    Twin twin1;
    Twin twin2;

    twin1.syncState(&twin2);
    twin2.syncState(&twin1);

    twin1.updateState("State 1");
    twin2.updateState("State 2");

    twin1.sendData("Data from twin1");
    twin2.sendData("Data from twin2");

    return 0;
}
