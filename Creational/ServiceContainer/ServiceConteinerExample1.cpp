#include <iostream>
#include <unordered_map>
#include <functional>

// Some example services/interfaces

class EmailService {
public:
    virtual void sendEmail(const std::string& recipient, const std::string& message) = 0;
};

class SMSService {
public:
    virtual void sendSMS(const std::string& recipient, const std::string& message) = 0;
};

// Concrete implementations of services

class MockEmailService : public EmailService {
public:
    void sendEmail(const std::string& recipient, const std::string& message) override {
        std::cout << "Mock Email Service: Sending email to " << recipient << std::endl;
        std::cout << "Message: " << message << std::endl;
    }
};

class TwilioSMSService : public SMSService {
public:
    void sendSMS(const std::string& recipient, const std::string& message) override {
        std::cout << "Twilio SMS Service: Sending SMS to " << recipient << std::endl;
        std::cout << "Message: " << message << std::endl;
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
    container.registerService<MockEmailService>("EmailService");
    container.registerService<TwilioSMSService>("SMSService");

    // Resolve services
    EmailService* emailService = container.resolveService<EmailService>("EmailService");
    SMSService* smsService = container.resolveService<SMSService>("SMSService");

    // Use the resolved services
    if (emailService) {
        emailService->sendEmail("john@example.com", "Hello from the Email Service!");
    }

    if (smsService) {
        smsService->sendSMS("+123456789", "Hello from the SMS Service!");
    }

    // Clean up
    delete emailService;
    delete smsService;

    return 0;
}
