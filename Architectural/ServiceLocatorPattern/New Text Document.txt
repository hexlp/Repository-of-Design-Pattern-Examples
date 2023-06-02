// Service Interface
class Logger {
public:
    virtual void log(const std::string& message) = 0;
};

// Concrete Service Implementations
class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "[ConsoleLogger] " << message << std::endl;
    }
};

class FileLogger : public Logger {
public:
    void log(const std::string& message) override {
        // Write the message to a file
    }
};

// Service Locator
class ServiceLocator {
public:
    template <typename T>
    void registerService(std::shared_ptr<T> service) {
        services[std::type_index(typeid(T))] = service;
    }

    template <typename T>
    std::shared_ptr<T> getService() {
        auto iter = services.find(std::type_index(typeid(T)));
        if (iter != services.end()) {
            return std::dynamic_pointer_cast<T>(iter->second);
        }
        return nullptr;
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> services;
};

// Usage
int main() {
    // Create service instances
    auto consoleLogger = std::make_shared<ConsoleLogger>();
    auto fileLogger = std::make_shared<FileLogger>();

    // Register services with the Service Locator
    ServiceLocator serviceLocator;
    serviceLocator.registerService(consoleLogger);
    serviceLocator.registerService(fileLogger);

    // Obtain services from the Service Locator
    auto logger = serviceLocator.getService<Logger>();
    if (logger) {
        logger->log("Logging a message");
    }

    return 0;
}
