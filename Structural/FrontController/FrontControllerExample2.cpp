#include <iostream>
#include <string>
#include <unordered_set>

// Abstract base class for handling requests
class DeviceController {
public:
    virtual void handleRequest(const std::string& request) = 0;
};

// Concrete device controllers
class LightController : public DeviceController {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Controlling Lights: " << request << std::endl;
    }
};

class ThermostatController : public DeviceController {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Controlling Thermostat: " << request << std::endl;
    }
};

class SecuritySystemController : public DeviceController {
public:
    void handleRequest(const std::string& request) override {
        std::cout << "Controlling Security System: " << request << std::endl;
    }
};

// Front Controller
class SmartHomeController {
private:
    DeviceController* lightController;
    DeviceController* thermostatController;
    DeviceController* securitySystemController;
    std::unordered_set<std::string> adminCommands;

public:
    SmartHomeController() {
        lightController = new LightController();
        thermostatController = new ThermostatController();
        securitySystemController = new SecuritySystemController();
        adminCommands.insert("lights");
        adminCommands.insert("thermostat");
        adminCommands.insert("security");
    }

    void dispatchRequest(const std::string& command, bool isAdmin) {
        if (command == "lights") {
            lightController->handleRequest(command);
        } else if (command == "thermostat") {
            thermostatController->handleRequest(command);
        } else if (command == "security" && isAdmin) {
            securitySystemController->handleRequest(command);
        } else {
            std::cout << "Access Denied" << std::endl;
        }
    }

    ~SmartHomeController() {
        delete lightController;
        delete thermostatController;
        delete securitySystemController;
    }
};

// Client
int main() {
    SmartHomeController smartHomeController;

    // Simulate user commands with different access levels
    smartHomeController.dispatchRequest("lights", false);         // Access granted: Control lights
    smartHomeController.dispatchRequest("thermostat", false);     // Access granted: Control thermostat
    smartHomeController.dispatchRequest("security", false);       // Access denied: Control security system
    smartHomeController.dispatchRequest("security", true);        // Access granted: Control security system

    return 0;
}
