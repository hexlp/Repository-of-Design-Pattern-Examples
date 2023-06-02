#include <iostream>
#include <string>

class Mediator;

class Colleague {
protected:
    Mediator* mediator;

public:
    Colleague(Mediator* m) : mediator(m) {}

    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& message) = 0;
};

class ConcreteColleagueA;
class ConcreteColleagueB;

class Mediator {
private:
    ConcreteColleagueA* colleagueA;
    ConcreteColleagueB* colleagueB;

public:
    void setColleagueA(ConcreteColleagueA* colleague);
    void setColleagueB(ConcreteColleagueB* colleague);
    void send(const std::string& message, Colleague* sender);
};

class ConcreteColleagueA : public Colleague {
public:
    ConcreteColleagueA(Mediator* m) : Colleague(m) {}

    void send(const std::string& message) override {
        mediator->send(message, this);
    }

    void receive(const std::string& message) override {
        std::cout << "ConcreteColleagueA received: " << message << std::endl;
    }
};

class ConcreteColleagueB : public Colleague {
public:
    ConcreteColleagueB(Mediator* m) : Colleague(m) {}

    void send(const std::string& message) override {
        mediator->send(message, this);
    }

    void receive(const std::string& message) override {
        std::cout << "ConcreteColleagueB received: " << message << std::endl;
    }
};

void Mediator::setColleagueA(ConcreteColleagueA* colleague) {
    colleagueA = colleague;
}

void Mediator::setColleagueB(ConcreteColleagueB* colleague) {
    colleagueB = colleague;
}

void Mediator::send(const std::string& message, Colleague* sender) {
    if (sender == colleagueA) {
        colleagueB->receive(message);
    }
    else if (sender == colleagueB) {
        colleagueA->receive(message);
    }
}

int main() {
    Mediator mediator;

    ConcreteColleagueA colleagueA(&mediator);
    ConcreteColleagueB colleagueB(&mediator);

    mediator.setColleagueA(&colleagueA);
    mediator.setColleagueB(&colleagueB);

    colleagueA.send("Hello from Colleague A!");
    colleagueB.send("Hi from Colleague B!");

    return 0;
}



