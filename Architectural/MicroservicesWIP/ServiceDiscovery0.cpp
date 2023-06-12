#include <iostream>
#include <unordered_map>
#include <string>

// Service Registry
class ServiceRegistry {
private:
    std::unordered_map<std::string, std::string> registry;

public:
    void registerService(const std::string& serviceName, const std::string& serviceEndpoint) {
        registry[serviceName] = serviceEndpoint;
        std::cout << "Registered service: " << serviceName << " at endpoint: " << serviceEndpoint << std::endl;
    }

    void unregisterService(const std::string& serviceName) {
        registry.erase(serviceName);
        std::cout << "Unregistered service: " << serviceName << std::endl;
    }

    std::string getServiceEndpoint(const std::string& serviceName) {
        return registry[serviceName];
    }
};

// Service Discovery
class ServiceDiscovery {
private:
    ServiceRegistry& registry;

public:
    explicit ServiceDiscovery(ServiceRegistry& registry) : registry(registry) {}

    std::string discoverService(const std::string& serviceName) {
        std::string serviceEndpoint = registry.getServiceEndpoint(serviceName);
        std::cout << "Discovered service: " << serviceName << " at endpoint: " << serviceEndpoint << std::endl;
        return serviceEndpoint;
    }
};

// Example usage
int main() {
    ServiceRegistry registry;
    ServiceDiscovery discovery(registry);

    // Register services
    registry.registerService("ProductService", "http://product-service.com");
    registry.registerService("OrderService", "http://order-service.com");
    registry.registerService("PaymentService", "http://payment-service.com");

    // Discover services
    std::string productServiceEndpoint = discovery.discoverService("ProductService");
    std::string orderServiceEndpoint = discovery.discoverService("OrderService");
    std::string paymentServiceEndpoint = discovery.discoverService("PaymentService");

    // Use the discovered services
    std::cout << "Using ProductService at endpoint: " << productServiceEndpoint << std::endl;
    std::cout << "Using OrderService at endpoint: " << orderServiceEndpoint << std::endl;
    std::cout << "Using PaymentService at endpoint: " << paymentServiceEndpoint << std::endl;

    // Unregister a service
    registry.unregisterService("ProductService");

    // Attempt to discover the unregistered service
    std::string invalidServiceEndpoint = discovery.discoverService("ProductService");
    std::cout << "Attempting to use ProductService at endpoint: " << invalidServiceEndpoint << std::endl;

    return 0;
}
