#include <iostream>
#include <string>
#include <unordered_map>

// Product Microservice
class ProductService {
public:
    std::string getProductInfo(const std::string& productId) {
        // Simulating product information retrieval
        std::unordered_map<std::string, std::string> products = {
            {"1", "iPhone 13"},
            {"2", "Samsung Galaxy S21"},
            {"3", "Google Pixel 6"},
        };

        if (products.find(productId) != products.end()) {
            return products[productId];
        }
        else {
            return "Product not found";
        }
    }
};

// Order Microservice
class OrderService {
public:
    std::string createOrder(const std::string& productId, const std::string& userId) {
        // Simulating order creation
        return "Order created for product: " + productId + ", user: " + userId;
    }
};

// Authentication Microservice
class AuthService {
public:
    bool isAuthenticated(const std::string& userId) {
        // Simulating user authentication
        std::unordered_map<std::string, std::string> users = {
            {"1", "John Doe"},
            {"2", "Jane Smith"},
        };

        return users.find(userId) != users.end();
    }
};

// API Gateway
class ApiGateway {
public:
    ApiGateway() : productService(), orderService(), authService() {}

    std::string processRequest(const std::string& endpoint, const std::string& userId, const std::string& data) {
        if (endpoint == "/product/info") {
            if (authService.isAuthenticated(userId)) {
                std::string productId = data;
                return productService.getProductInfo(productId);
            }
            else {
                return "User not authenticated";
            }
        }
        else if (endpoint == "/order/create") {
            if (authService.isAuthenticated(userId)) {
                std::string productId = data;
                return orderService.createOrder(productId, userId);
            }
            else {
                return "User not authenticated";
            }
        }
        else {
            return "Endpoint not found";
        }
    }

private:
    ProductService productService;
    OrderService orderService;
    AuthService authService;
};

int main() {
    // Client making requests through the API Gateway
    ApiGateway apiGateway;

    // Simulating client requests
    std::cout << apiGateway.processRequest("/product/info", "1", "2") << std::endl;
    std::cout << apiGateway.processRequest("/order/create", "2", "1") << std::endl;
    std::cout << apiGateway.processRequest("/product/info", "3", "4") << std::endl;

    return 0;
}
