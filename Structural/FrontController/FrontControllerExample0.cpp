/*

The Front Controller pattern is a design pattern that provides a centralized 
entry point for handling requests in a web application. It acts as a single point
of contact for all incoming requests and delegates the request handling to appropriate
handlers or controllers.



*/


#include <iostream>
#include <string>

// Abstract base class for handling requests
class RequestHandler {
public:
    virtual void handleRequest(const std::string& request) = 0;
};

// Concrete request handlers
class HomeHandler : public RequestHandler {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Home Page: " << request << std::endl;
    }
};

class AboutHandler : public RequestHandler {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "About Page: " << request << std::endl;
    }
};

class ContactHandler : public RequestHandler {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Contact Page: " << request << std::endl;
    }
};

// Front Controller
class FrontController {
private:
    HomeHandler homeHandler;
    AboutHandler aboutHandler;
    ContactHandler contactHandler;

public:
    void dispatchRequest(const std::string& page) {
        if (page == "home") {
            homeHandler.handleRequest(page);
        }
        else if (page == "about") {
            aboutHandler.handleRequest(page);
        }
        else if (page == "contact") {
            contactHandler.handleRequest(page);
        }
        else {
            std::cout << "404 Not Found" << std::endl;
        }
    }
};

// Client
int main() {
    FrontController frontController;

    // Simulate incoming requests
    frontController.dispatchRequest("home");
    frontController.dispatchRequest("about");
    frontController.dispatchRequest("contact");
    frontController.dispatchRequest("services");

    return 0;
}
