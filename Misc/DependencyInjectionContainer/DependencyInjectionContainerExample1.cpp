#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

// Interfaces
class ILogger {
public:
    virtual void log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};

class IEmailSender {
public:
    virtual void sendEmail(const std::string& to, const std::string& message) = 0;
    virtual ~IEmailSender() = default;
};

// Implementations
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "LOG: " << message << std::endl;
    }
};


class FileLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "LOG: " << message << std::endl;
    }
};

class EmailSender : public IEmailSender {
public:
    void sendEmail(const std::string& to, const std::string& message) override {
        std::cout << "Sending email to " << to << ": " << message << std::endl;
    }
};
 
class Printer {

public:

    std::string ink = "black";

    void print(const std::string& message) {
		std::cout << "PRINT: " << message << std::endl;
        std::cout << "Ink: " << ink << std::endl;
	}

};
 


class UserService {
private:
    std::shared_ptr<ILogger> logger;
    std::shared_ptr<IEmailSender> emailSender;


public:
    UserService(std::shared_ptr<ILogger> logger, std::shared_ptr<IEmailSender> emailSender)
        : logger(logger), emailSender(emailSender) {}

    void registerUser(const std::string& email) {
        logger->log("Registering user: " + email);
        emailSender->sendEmail(email, "Welcome to our service!");
    }
};

class PrintService {

    std::shared_ptr<ILogger> logger;
    std::shared_ptr<Printer> printer;

    public:
        PrintService(std::shared_ptr<ILogger> logger, std::shared_ptr<Printer> printer)
		: logger(logger), printer(printer) {}

        void printMessage(const std::string& message) {
		logger->log("Printing message: " + message);
		printer->print(message);
	}

};

class ServiceContainer {

 public:

    // Register a service instance
    template<typename T>
    void registerService(const std::string& serviceName, std::shared_ptr<T> service) {
        if (!service) {
            throw std::runtime_error("Service cannot be null.");
        }

        if (serviceName.empty()) {
            throw std::runtime_error("Service name cannot be empty.");
        }

        if (serviceRegistry.find(serviceName) != serviceRegistry.end()) {
            throw std::runtime_error("Service already registered.");
        }

        if (serviceName.find(" ") != std::string::npos) {
            throw std::runtime_error("Service name cannot contain spaces.");
        }

        serviceRegistry[serviceName] = service;
    }
     
    
    template<typename TInterface, typename TImplementation>
    void registerService(const std::string& serviceName) {
        registerService<TInterface>(serviceName, std::make_shared<TImplementation>());
    }
    
    template<typename TImplementation>
    void registerService(const std::string& serviceName) {
		registerService<TImplementation>(serviceName, std::make_shared<TImplementation>());
	}

    // Register a service factory
    template<typename T>
    void registerServiceFactory(const std::string& serviceName, std::function<std::shared_ptr<T>()> factory) {

        if (!factory) {
            throw std::runtime_error("Factory cannot be null.");
        }

        if (serviceName.empty()) {
            throw std::runtime_error("Service name cannot be empty.");
        }

        if (factoryRegistry.find(serviceName) != factoryRegistry.end()) {
            throw std::runtime_error("Factory already registered.");
        }

        if (serviceName.find(" ") != std::string::npos) {
            throw std::runtime_error("Service name cannot contain spaces.");
        }

        factoryRegistry[serviceName] = [factory]() -> std::shared_ptr<void> {
            return factory();
            };
    }


    template<typename T>
    std::shared_ptr<T> resolveService(const std::string& serviceName) {
        if (serviceRegistry.find(serviceName) != serviceRegistry.end()) {
            try {
                return std::any_cast<std::shared_ptr<T>>(serviceRegistry[serviceName]);
            }
            catch (const std::bad_any_cast&) {
                throw std::runtime_error("Service type mismatch for: " + serviceName);
            }
        }

        if (factoryRegistry.find(serviceName) != factoryRegistry.end()) {
            auto service = std::static_pointer_cast<T>(factoryRegistry[serviceName]());
            serviceRegistry[serviceName] = service;
            return service;
        }

        throw std::runtime_error("Service not registered: " + serviceName);
    }


private:
    std::map<std::string, std::any> serviceRegistry;
    std::map<std::string, std::function<std::shared_ptr<void>()>> factoryRegistry;
};


// Funzione esterna per creare UserService
std::shared_ptr<UserService> createUserService(ServiceContainer& container) {
    auto logger = container.resolveService<ILogger>("fileLogger");
    auto emailSender = container.resolveService<IEmailSender>("emailSender");    
    return std::make_shared<UserService>(logger, emailSender);
}


// Funzione esterna per creare PrintService
std::shared_ptr<PrintService> createPrintService(ServiceContainer& container) {
	auto logger = container.resolveService<ILogger>("fileLogger");
	auto printer = container.resolveService<Printer>("printer");
	return std::make_shared<PrintService>(logger, printer);
}


int main() {

    ServiceContainer container;

    // Register services directly       

    // Register service instance 
    auto printer = std::make_shared<Printer>();     
    printer->ink = "blue";    
    container.registerService<Printer>("printer_blue_ink", printer);   

    // Register service type 
    container.registerService<Printer>("printer");                

     // Register service type with interface
     container.registerService<ILogger, FileLogger>("fileLogger");    
     container.registerService<ILogger, ConsoleLogger>("consoleLogger");
     container.registerService<IEmailSender, EmailSender>("emailSender");


    // Register service factories
    container.registerServiceFactory<UserService>("userService", [&container]() -> std::shared_ptr<UserService> {
            return createUserService(container);         
        });

    container.registerServiceFactory<PrintService>("printService", [&container]() -> std::shared_ptr<PrintService> {
			return createPrintService(container);         
		});


    // Resolve and use PrintService
    try {
		auto printService = container.resolveService<PrintService>("printService");
		printService->printMessage("Hello, world!");
	}
    catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
        
    // Resolve and use UserService
    try {
        auto userService = container.resolveService<UserService>("userService");
        userService->registerUser("example@example.com");
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return 0;
}
