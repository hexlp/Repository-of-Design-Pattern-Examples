/*
The Bridge pattern is a design pattern that decouples an abstraction from its implementation so that the two can vary independently.
 The Bridge pattern allows the abstraction and the implementation to be developed and changed independently.
 This is useful when you want to develop an application with multiple implementations of an abstraction.
*/

#include <iostream>
#include <string>

// Implementor Interface
class TV {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setChannel(int channel) = 0;
};

// Concrete Implementor 1
class SonyTV : public TV {
public:
    void on() override {
        std::cout << "Sony TV is on\n";
    }

    void off() override {
        std::cout << "Sony TV is off\n";
    }

    void setChannel(int channel) override {
        std::cout << "Sony TV set channel to " << channel << std::endl;
    }
};

// Concrete Implementor 2
class SamsungTV : public TV {
public:
    void on() override {
        std::cout << "Samsung TV is on\n";
    }

    void off() override {
        std::cout << "Samsung TV is off\n";
    }

    void setChannel(int channel) override {
        std::cout << "Samsung TV set channel to " << channel << std::endl;
    }
};

// Abstraction Interface
class RemoteControl {
public:
    RemoteControl(TV* tv) : m_tv(tv) {}
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setChannel(int channel) = 0;

protected:
    TV* m_tv;
};

// Refined Abstraction
class BasicRemoteControl : public RemoteControl {
public:
    BasicRemoteControl(TV* tv) : RemoteControl(tv) {}

    void on() override {
        m_tv->on();
    }

    void off() override {
        m_tv->off();
    }

    void setChannel(int channel) override {
        m_tv->setChannel(channel);
    }
};

int main() {
    TV* sony = new SonyTV();
    TV* samsung = new SamsungTV();

    RemoteControl* basicRemote1 = new BasicRemoteControl(sony);
    RemoteControl* basicRemote2 = new BasicRemoteControl(samsung);

    basicRemote1->on(); // Output: Sony TV is on
    basicRemote1->setChannel(1); // Output: Sony TV set channel to 1
    basicRemote1->off(); // Output: Sony TV is off

    basicRemote2->on(); // Output: Samsung TV is on
    basicRemote2->setChannel(2); // Output: Samsung TV set channel to 2
    basicRemote2->off(); // Output: Samsung TV is off

    delete sony;
    delete samsung;
    delete basicRemote1;
    delete basicRemote2;

    return 0;
}