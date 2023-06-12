#include <iostream>

// Service interface
class Service {
public:
    virtual void doSomething() = 0;
};

// Concrete implementation of Service
class ConcreteService : public Service {
public:
    void doSomething() override {
        std::cout << "Doing something in ConcreteService" << std::endl;
    }
};

// Client class that depends on the Service
class Client {
private:
    Service* service;  // Dependency

public:
    // Constructor injection
    Client(Service* service) : service(service) {}

    void execute() {
        service->doSomething();
    }
};

// Dependency injector
class Injector {
public:
    // Method to create and inject the dependencies
    Client* createClient() {
        Service* service = createService();
        return new Client(service);
    }

private:
    // Method to create the concrete service
    Service* createService() {
        return new ConcreteService();
    }
};

int main() {
    // Create the injector
    Injector injector;

    // Create the client with injected dependencies
    Client* client = injector.createClient();

    // Execute the client
    client->execute();

    // Clean up
    delete client;

    return 0;
}