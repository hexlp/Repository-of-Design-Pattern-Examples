/*
The API Gateway pattern acts as a single entry point 
for client applications to access various microservices 
within a system. It provides a centralized endpoint that 
handles requests from clients, performs authentication 
and authorization, and routes the requests to the appropriate 
microservices. It can also perform additional functionalities 
like request/response transformation, rate limiting, caching, and logging.
*/


#include <iostream>
#include <string>

// Microservice 1
class Service1 {
public:
    std::string processRequest(const std::string& data) {
        // Simulating processing of request
        return "Service 1 processed request: " + data;
    }
};

// Microservice 2
class Service2 {
public:
    std::string processRequest(const std::string& data) {
        // Simulating processing of request
        return "Service 2 processed request: " + data;
    }
};

// API Gateway
class ApiGateway {
public:
    ApiGateway() : service1(), service2() {}

    std::string processRequest(const std::string& service, const std::string& data) {
        if (service == "service1") {
            return service1.processRequest(data);
        } else if (service == "service2") {
            return service2.processRequest(data);
        } else {
            return "Service not found";
        }
    }

private:
    Service1 service1;
    Service2 service2;
};

int main() {
    // Client making requests through the API Gateway
    ApiGateway apiGateway;

    // Simulating client requests
    std::cout << apiGateway.processRequest("service1", "Request 1") << std::endl;
    std::cout << apiGateway.processRequest("service2", "Request 2") << std::endl;
    std::cout << apiGateway.processRequest("service3", "Request 3") << std::endl;

    return 0;
}
