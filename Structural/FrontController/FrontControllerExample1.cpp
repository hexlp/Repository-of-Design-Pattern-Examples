#include <iostream>
#include <string>
#include <unordered_set>

// Abstract base class for handling requests
class RequestHandler {
public:
    virtual void handleRequest(const std::string& request) = 0;
};

// Concrete request handlers
class HomeController : public RequestHandler {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Home Page: " << request << std::endl;
    }
};

class AdminController : public RequestHandler {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Admin Page: " << request << std::endl;
    }
};

class ProfileController : public RequestHandler {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Profile Page: " << request << std::endl;
    }
};

// Front Controller
class FrontController {
private:
    RequestHandler* homeController;
    RequestHandler* adminController;
    RequestHandler* profileController;
    std::unordered_set<std::string> adminPages;

public:
    FrontController() {
        homeController = new HomeController();
        adminController = new AdminController();
        profileController = new ProfileController();
        adminPages.insert("admin");
        adminPages.insert("users");
        adminPages.insert("reports");
    }

    void dispatchRequest(const std::string& page, const std::string& username, bool isAdmin) {
        if (page == "home") {
            homeController->handleRequest(page);
        } else if (page == "admin" && isAdmin) {
            adminController->handleRequest(page);
        } else if (page == "profile" && username != "") {
            profileController->handleRequest(page);
        } else {
            std::cout << "Access Denied" << std::endl;
        }
    }

    ~FrontController() {
        delete homeController;
        delete adminController;
        delete profileController;
    }
};

// Client
int main() {
    FrontController frontController;

    // Simulate incoming requests with different user roles
    frontController.dispatchRequest("home", "", false);              // Access granted: Home page
    frontController.dispatchRequest("admin", "", false);             // Access denied: Admin page
    frontController.dispatchRequest("admin", "", true);              // Access granted: Admin page
    frontController.dispatchRequest("profile", "user1", false);      // Access denied: Profile page
    frontController.dispatchRequest("profile", "user1", true);       // Access granted: Profile page

    return 0;
}
