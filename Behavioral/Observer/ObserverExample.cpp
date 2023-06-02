
/*

The Observer Pattern is a behavioral design pattern that defines a one-to-many dependency between objects,
 so that when one object (called the subject or observable) changes its state, all its dependents (called observers)
 are notified and updated automatically. The pattern promotes loose coupling between objects, allowing them to interact without having explicit knowledge of each other.

Key Components of the Observer Pattern:

Subject: The subject is the object that holds the state and maintains a list of observers.
 It provides methods to attach, detach, and notify observers of any changes in its state.

Observer: The observer is the interface or base class that defines the contract for the observers.
Observers register themselves with the subject and receive updates when the subject's state changes.

Concrete Subject: The concrete subject is the implementation of the subject interface. It maintains the
 state and sends notifications to the registered observers when the state changes.

Concrete Observer: The concrete observer is the implementation of the observer interface.
 It registers itself with the subject and receives updates from the subject when there are state changes.

Benefits of the Observer Pattern:

Loose Coupling: The pattern decouples the subject and observers, allowing them to evolve
independently. They are only dependent on the subject's interface, promoting flexibility and maintainability.

Scalability: The pattern supports multiple observers, making it easy to add or remove observers
without impacting the subject or other observers. This makes the pattern scalable to handle varying numbers of observers.

Reusability: Observers can be reused across different subjects, allowing for greater code reuse and modular design.

Simplified Event Handling: The pattern simplifies the management of event-driven systems. Instead of explicit
event handling and callbacks, observers can be used to receive notifications and update their state accordingly.

*/

#include <iostream>
#include <vector>
#include <algorithm>

class WeatherObserver; // Forward declaration

// Subject (WeatherStation) interface
class WeatherStation {
public:
    virtual void attach(WeatherObserver* observer) = 0;
    virtual void detach(WeatherObserver* observer) = 0;
    virtual void notify() = 0;
    virtual int getTemperature() const = 0;
};

// Observer interface
class WeatherObserver {
public:
    virtual void update() = 0;
};

// Concrete Subject (WeatherStation) implementation
class WeatherStationImpl : public WeatherStation {
    std::vector<WeatherObserver*> observers;
    int temperature;

public:
    void attach(WeatherObserver* observer) override {
        observers.push_back(observer);
    }

    void detach(WeatherObserver* observer) override {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notify() override {
        for (auto observer : observers) {
            observer->update();
        }
    }

    int getTemperature() const override {
        return temperature;
    }

    void setTemperature(int temp) {
        temperature = temp;
        notify();
    }
};

// Concrete Observer (MobileDevice) implementation
class MobileDevice : public WeatherObserver {
    WeatherStation* weatherStation;

public:
    explicit MobileDevice(WeatherStation* station) : weatherStation(station) {
        weatherStation->attach(this);
    }

    void update() override {
        int temperature = weatherStation->getTemperature();
        std::cout << "Mobile Device: Temperature updated. Current temperature: " << temperature << " degrees." << std::endl;
    }
};

// Concrete Observer (WebApplication) implementation
class WebApplication : public WeatherObserver {
    WeatherStation* weatherStation;

public:
    explicit WebApplication(WeatherStation* station) : weatherStation(station) {
        weatherStation->attach(this);
    }

    void update() override {
        int temperature = weatherStation->getTemperature();
        std::cout << "Web Application: Weather update received. Current temperature: " << temperature << " degrees." << std::endl;
    }
};

int main() {
    // Create the weather station
    WeatherStationImpl weatherStation;

    // Create observers (mobile device and web application)
    MobileDevice mobileDevice(&weatherStation);
    WebApplication webApp(&weatherStation);

    // Simulate a temperature update
    weatherStation.setTemperature(25);

    return 0;
}
