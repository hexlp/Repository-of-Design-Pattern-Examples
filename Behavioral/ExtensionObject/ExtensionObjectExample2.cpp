#include <iostream>
#include <string>

// Base class: Vehicle
class Vehicle {
public:
    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
};

// Extension interface: GPSNavigator
class GPSNavigator {
public:
    virtual void navigate(const std::string& destination) = 0;
};

// Concrete extension class: CarGPSNavigator
class CarGPSNavigator : public GPSNavigator {
public:
    void navigate(const std::string& destination) override {
        std::cout << "Navigating to " << destination << " using GPS." << std::endl;
    }
};

// TextEditor class modified for the Extension Object Pattern
class Car : public Vehicle {
public:
    void startEngine() override {
        std::cout << "Car engine started." << std::endl;
    }

    void stopEngine() override {
        std::cout << "Car engine stopped." << std::endl;
    }

    void setGPSNavigator(GPSNavigator* navigator) {
        this->navigator = navigator;
    }

    void navigateTo(const std::string& destination) {
        if (navigator) {
            navigator->navigate(destination);
        }
        else {
            std::cout << "GPS navigation not available." << std::endl;
        }
    }

private:
    GPSNavigator* navigator = nullptr;
};

int main() {
    Car car;
    CarGPSNavigator gpsNavigator;
    car.setGPSNavigator(&gpsNavigator);

    car.startEngine();
    car.navigateTo("Destination A");
    car.stopEngine();

    return 0;
}