#include <iostream>
#include <string>
#include <vector>

class Prototype {
public:
    virtual Prototype* clone() const = 0;
    virtual void printInfo() const = 0;
    virtual char getState() const = 0;
    virtual void setState(char) = 0;
};

class ConcretePrototypeA : public Prototype {
public:
    Prototype* clone() const override {
        return new ConcretePrototypeA(*this);
    }
    void printInfo() const override {
        std::cout << "This is Concrete Prototype A" << std::endl;
        std::cout << "State: " << state_ << "\n";
    }
    char getState() const override { return state_; };
    void setState(char c) override { state_ = c; };
private:
    char state_ = 'A'; 
};

class ConcretePrototypeB : public Prototype {
public:
    Prototype* clone() const override {
        return new ConcretePrototypeB(*this);
    }
    void printInfo() const override {
        std::cout << "This is Concrete Prototype B" << std::endl;
        std::cout << "State: " << state_ << "\n";
    }
    char getState() const override { return state_; };
    void setState(char c) override { state_ = c; };

private:
    char state_ = 'B';
};

class Client {
public:
    Client(Prototype* prototype) : prototype_(prototype) {}
    void createObject() {
        Prototype* newObject = prototype_->clone();
        objects_.push_back(newObject);
    }
    void printObjects() const {
        for (Prototype* obj : objects_) {
            obj->printInfo();           
        }
    }
private:
    Prototype* prototype_;
    std::vector<Prototype*> objects_;
};

int main() {
    ConcretePrototypeA* prototypeA = new ConcretePrototypeA();
 
    ConcretePrototypeB* prototypeB = new ConcretePrototypeB();

    Client* client1 = new Client(prototypeA);
    Client* client2 = new Client(prototypeB);

    prototypeA->setState('S'); 

    client1->createObject();
    client2->createObject();
    client1->createObject();

    client1->printObjects();
    client2->printObjects();

    delete prototypeA;
    delete prototypeB;
    delete client1;
    delete client2;

    return 0;
}
