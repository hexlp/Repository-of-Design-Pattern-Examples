/*

The Service Container Pattern, also known as the Dependency Injection Container or IoC 
(Inversion of Control) Container, is a design pattern used in software development to 
manage the instantiation and resolution of dependencies throughout an application.

The pattern revolves around a central container or registry that holds and provides access to 
instances of various services or dependencies needed by the application. It promotes loose 
coupling and improves modularity by separating the responsibility of object creation and 
dependency management from the individual components.


By using the Service Container Pattern, the application components can have their 
dependencies resolved and injected automatically, reducing the coupling between
components and promoting modularity and testability. The container takes care of 
managing the lifetime and creation of the service instances, making it easier to switch 
implementations or mock dependencies for testing purposes.

*/




#include <iostream>
#include <unordered_map>
#include <functional>

// Some example services/interfaces

class Logger {
public:
    virtual void log(const std::string& message) = 0;
};

class Database {
public:
    virtual void query(const std::string& sql) = 0;
};

// Concrete implementations of services

class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "Logging: " << message << std::endl;
    }
};

class MySqlConnection : public Database {
public:
    void query(const std::string& sql) override {
        std::cout << "Executing SQL query: " << sql << std::endl;
        // Logic to perform the database query
    }
};

// Service container/dependency injection container

class ServiceContainer {
private:
    std::unordered_map<std::string, std::function<void*()>> services;

public:
    template<typename T>
    void registerService(const std::string& serviceName) {
        services[serviceName] = []() -> void* {
            return new T();
        };
    }

    template<typename T>
    T* resolveService(const std::string& serviceName) {
        auto service = services.find(serviceName);
        if (service != services.end()) {
            auto instanceCreator = service->second;
            return static_cast<T*>(instanceCreator());
        }
        return nullptr;
    }
};

// Usage example

int main() {
    ServiceContainer container;

    // Register services
    container.registerService<ConsoleLogger>("Logger");
    container.registerService<MySqlConnection>("Database");

    // Resolve services
    Logger* logger = container.resolveService<Logger>("Logger");
    Database* database = container.resolveService<Database>("Database");

    // Use the resolved services
    if (logger) {
        logger->log("Logging message");
    }

    if (database) {
        database->query("SELECT * FROM users");
    }

    // Clean up
    delete logger;
    delete database;

    return 0;
}
