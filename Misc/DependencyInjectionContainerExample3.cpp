#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <mutex>
#include <iostream>

// Interfacce
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

class IDatabase {

public:
    virtual void save(const std::string& data) = 0;
    virtual ~IDatabase() = default;

};

class Database : public IDatabase {

public:
    void save(const std::string& data) override {
        std::cout << "Saving data to database: " << data << std::endl;
    }

};

class UserService {
public:
    UserService(std::shared_ptr<ILogger> logger, std::shared_ptr<IEmailSender> emailSender, std::shared_ptr<IDatabase> database)
        : logger(logger), emailSender(emailSender), database(database) {}

    void registerUser(const std::string& email) {
        logger->log("Registering user: " + email);
        emailSender->sendEmail(email, "Welcome to our service!");
        database->save(email);
    }

private:
    std::shared_ptr<ILogger> logger;
    std::shared_ptr<IEmailSender> emailSender;
    std::shared_ptr<IDatabase> database;
};


class StockService {

public:
    StockService(std::shared_ptr<ILogger> logger, std::shared_ptr<IDatabase> database)
        : logger(logger), database(database) {}

    void saveStock(const std::string& stock) {
        logger->log("Saving stock: " + stock);
        database->save(stock);
    }

private:
    std::shared_ptr<ILogger> logger;
    std::shared_ptr<IDatabase> database;

};



enum class Lifetime {
    Transient,
    Scoped,
    Singleton
};

constexpr const char* lifetimeToString(Lifetime lifetime) {
    switch (lifetime) {
    case Lifetime::Transient: return "Transient";
    case Lifetime::Scoped:  return "Scoped";
    case Lifetime::Singleton: return "Singleton";
    default: return "Unknown";
    }
}


class Scope {
public:
    std::map<std::string, std::shared_ptr<void>> instances;
};

class DependencyInjector {


public:
    template<typename T>
    void AddTransient(const std::string& serviceName, std::function<std::shared_ptr<T>()> factory) {
        registerServiceFactory<T>(serviceName, factory, Lifetime::Transient);
    }

    template<typename T>
    void AddScoped(const std::string& serviceName, std::function<std::shared_ptr<T>()> factory) {
        registerServiceFactory<T>(serviceName, factory, Lifetime::Scoped);
    }

    template<typename T>
    void AddSingleton(const std::string& serviceName, std::function<std::shared_ptr<T>()> factory) {
        registerServiceFactory<T>(serviceName, factory, Lifetime::Singleton);
    }

    template<typename T>
    std::shared_ptr<T> Resolve(const std::string& serviceName, std::shared_ptr<Scope> scope = nullptr) {
        return resolveService<T>(serviceName, scope);
    }

    std::shared_ptr<Scope> CreateScope() {
        return std::make_shared<Scope>();
    }




    // -- Methods to clear singleton and scope instances -- 

    // Clear all singleton instances registered with the container    
    void ClearSingletons() {
        clearSingletons();
    }

    // Clear a specific singleton instance registered with the container
    void ClearSingleton(const std::string& serviceName) {
        clearSingleton(serviceName);
    }

    // Clear all scope instances registered with the container
    void ClearScopeInstances(std::shared_ptr<Scope> scope) {
        clearScopeInstances(scope);
    }

    // Clear a specific scope instance registered with the container
    void ClearScopeInstance(std::shared_ptr<Scope> scope, const std::string& serviceName) {
        clearScopeInstance(scope, serviceName);
    }

    // Clear all factory and lifetime registrations
    void ClearRegistrations() {
        clearRegistrations();
    }

    // Clear all singleton instances and registrations (factory and lifetime registrations) 
    void ClearAll() {
        clearAll();
    }


protected:
    template<typename T>
    void registerServiceFactory(const std::string& serviceName, std::function<std::shared_ptr<T>()> factory, Lifetime lifetime = Lifetime::Transient) {
        if (factoryRegistry.find(serviceName) != factoryRegistry.end()) {
            throw std::runtime_error("Service already registered: " + serviceName);
        }

        factoryRegistry[serviceName] = [factory]() -> std::shared_ptr<void> {
            return factory();
            };
        lifetimeRegistry[serviceName] = lifetime;
    }


    template<typename T>
    std::shared_ptr<T> resolveService(const std::string& serviceName, std::shared_ptr<Scope> scope = nullptr) {

        // Check if service is registered with the container
        auto factoryIt = factoryRegistry.find(serviceName);
        if (factoryIt == factoryRegistry.end()) {
            throw std::runtime_error("Service not registered: " + serviceName);
        }

        // Check if service lifetime is registered with the container
        auto lifetimeIt = lifetimeRegistry.find(serviceName);
        if (lifetimeIt == lifetimeRegistry.end()) {
            throw std::runtime_error("Service lifetime not found: " + serviceName);
        }

        // Resolve service based on its lifetime
        switch (lifetimeIt->second) {
        case Lifetime::Singleton:
            return resolveSingleton<T>(serviceName, factoryIt->second);
        case Lifetime::Scoped:
            if (!scope) {
                throw std::runtime_error("Scope required for scoped service: " + serviceName);
            }
            return resolveScoped<T>(serviceName, factoryIt->second, scope);
        case Lifetime::Transient:
        default:
            return resolveTransient<T>(serviceName, factoryIt->second);
        }
    }





    // -- Methods to clear singleton and scope instances --

    // Clear all singleton instances
    void clearSingletons() {
        std::lock_guard<std::mutex> lock(singletonMutex);
        singletonInstances.clear();
    }

    // Clear a specific singleton instance
    void clearSingleton(const std::string& serviceName) {

        std::lock_guard<std::mutex> lock(singletonMutex);

        // Check if service is registered with the container
        auto instanceIt = singletonInstances.find(serviceName);
        if (instanceIt == singletonInstances.end()) {
            throw std::runtime_error("Singleton instance not found: " + serviceName);
        }

        // Clear the singleton instance
        singletonInstances.erase(serviceName);

    }

    // Clear all scope instances
    void clearScopeInstances(std::shared_ptr<Scope> scope) {
        scope->instances.clear();
    }

    // Clear a specific scope instance
    void clearScopeInstance(std::shared_ptr<Scope> scope, const std::string& serviceName) {

        // Check if service is registered with the container
        auto instanceIt = scope->instances.find(serviceName);
        if (instanceIt == scope->instances.end()) {
            throw std::runtime_error("Scope instance not found: " + serviceName);
        }

        // Clear the scope instance
        scope->instances.erase(serviceName);
    }

    // Clear all factory and lifetime registrations
    void clearRegistrations() {
        factoryRegistry.clear();
        lifetimeRegistry.clear();
    }

    // Clear all singleton instances and registrations
    void clearAll() {
        clearSingletons();
        clearRegistrations();
    }



private:

    // Resolve service instance for Singleton lifetime services 
    // If the service instance is not found in the singletonInstances map, it is created and added to the map
    // If the service instance is found in the singletonInstances map, it is returned
    template<typename T>
    std::shared_ptr<T> resolveSingleton(const std::string& serviceName, const std::function<std::shared_ptr<void>()>& factory) {

        std::lock_guard<std::mutex> lock(singletonMutex); // Ensure only one thread can access this at a time  

        auto instanceIt = singletonInstances.find(serviceName);
        if (instanceIt == singletonInstances.end()) {
            auto instance = factory();
            singletonInstances[serviceName] = instance;
            return std::static_pointer_cast<T>(instance);
        }
        return std::static_pointer_cast<T>(instanceIt->second);
    }

    // Resolve service instance for Scoped lifetime services
    // If the service instance is not found in the scope instances map, it is created and added to the map
    // If the service instance is found in the scope instances map, it is returned
    template<typename T>
    std::shared_ptr<T> resolveScoped(const std::string& serviceName, const std::function<std::shared_ptr<void>()>& factory, std::shared_ptr<Scope> scope) {
        auto& instances = scope->instances;
        auto instanceIt = instances.find(serviceName);
        if (instanceIt == instances.end()) {
            auto instance = factory();
            instances[serviceName] = instance;
            return std::static_pointer_cast<T>(instance);
        }
        return std::static_pointer_cast<T>(instanceIt->second);
    }

    // Resolve service instance for Transient lifetime services
    // The factory function is called to create a new instance each time
    template<typename T>
    std::shared_ptr<T> resolveTransient(const std::string& serviceName, const std::function<std::shared_ptr<void>()>& factory) {
        return std::static_pointer_cast<T>(factory());
    }


    std::map<std::string, std::function<std::shared_ptr<void>()>> factoryRegistry;
    std::map<std::string, Lifetime> lifetimeRegistry;
    std::map<std::string, std::shared_ptr<void>> singletonInstances;

    // A mutex (short for "mutual exclusion") is a synchronization primitive used to prevent multiple threads from accessing a shared resource simultaneously, ensuring thread safety.
    // By using a std::mutex and std::lock_guard, we ensure that only one thread can create the singleton instance at a time, preserving the integrity and uniqueness of the singleton instance.
    std::mutex singletonMutex;  // Mutex to protect singletonInstances map from concurrent access. 
};


int main() {

    try {

        DependencyInjector container;

        container.AddSingleton<ILogger>("logger", []() {
            return std::make_shared<ConsoleLogger>();
            });


        container.AddSingleton<IEmailSender>("emailSender", []() {
            return std::make_shared<EmailSender>();
            });

        container.AddTransient<IDatabase>("database", []() {
            return std::make_shared<Database>();
            });


        container.AddScoped<UserService>("userService", [&container]() {
            return std::make_shared<UserService>(
                container.Resolve<ILogger>("logger"),
                container.Resolve<IEmailSender>("emailSender"),
                container.Resolve<IDatabase>("database")
            );
            });

        container.AddScoped<StockService>("stockService", [&container]() {
            auto logger = container.Resolve<ILogger>("logger");
            auto database = container.Resolve<IDatabase>("database");
            return std::make_shared<StockService>(logger, database);
            });



        auto scope = container.CreateScope();

        auto userService1 = container.Resolve<UserService>("userService", scope);
        userService1->registerUser("Alice"); // Registering user: Alice

        auto userService2 = container.Resolve<UserService>("userService", scope);
        userService2->registerUser("Bob"); // Registering user: Bob

        auto stockService = container.Resolve<StockService>("stockService", scope);
        stockService->saveStock("AAPL"); // Saving stock: AAPL




        // Examine scope instances map to see if the service instances are scoped correctly 
        std::cout << "Scope instances: " << scope->instances.size() << std::endl;                       // Scope instances: 2 (UserService, StockService)

        // Print the keys of the scope instances map along with the reference count of the service instances 
        std::cout << "Scope instances values: " << std::endl;
        for (const auto& [key, value] : scope->instances) {
            std::cout << "\t" << key << ": " << value.use_count() << std::endl;                                 // UserService: 3, StockService: 2    (One instance held by the scope map)
        }




        // Clear a specific scope instance
        std::cout << "Clearing scope instance: userService" << std::endl;
        container.ClearScopeInstance(scope, "userService");
        // Examine scope instances map to see if the service instances are cleared
        std::cout << "Scope instances: " << scope->instances.size() << std::endl;                       // Scope instances: 1 (StockService)


        // Clear the scope instances map
        std::cout << "Clearing all scope instances" << std::endl;
        container.ClearScopeInstances(scope);
        // Examine scope instances map to see if the service instances are cleared
        std::cout << "Scope instances: " << scope->instances.size() << std::endl;                       // Scope instances: 0


        // Clear a specific scope instance
        std::cout << "Clearing singleton instance: logger" << std::endl;
        container.ClearSingleton("logger");


        // Clear all singleton instances
        std::cout << "Clearing all singleton instances" << std::endl;
        container.ClearSingletons();

        // Examine singleton instances map to see if the service instances are cleared
        // std::cout << "Singleton instances: " << container.singletonInstances.size() << std::endl;       // Singleton instances: 0

        // Clear all factory and lifetime registrations
        std::cout << "Clearing all factory and lifetime registrations" << std::endl;
        container.ClearRegistrations();

        // Examine factory and lifetime registrations to see if they are cleared
        // std::cout << "Factory registrations: " << container.factoryRegistry.size() << std::endl;       // Factory registrations: 0


        // Clear all singleton instances and registrations
        std::cout << "Clearing all singleton instances and registrations" << std::endl;
        container.ClearAll();

        // Examine singleton instances map and factory and lifetime registrations to see if they are cleared
        //	std::cout << "Singleton instances: " << container.singletonInstances.size() << std::endl;       // Singleton instances: 0
        //	std::cout << "Factory registrations: " << container.factoryRegistry.size() << std::endl;       // Factory registrations: 0



    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}

