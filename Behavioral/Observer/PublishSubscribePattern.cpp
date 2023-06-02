#include <iostream>
#include <vector>

// Forward declaration of Subscriber
class Subscriber;

// Publisher class
class Publisher {
    std::vector<Subscriber*> subscribers;

public:
    void subscribe(Subscriber* subscriber) {
        subscribers.push_back(subscriber);
    }

    void unsubscribe(Subscriber* subscriber) {
        // Find and remove the subscriber from the list
        auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void publishEvent(const std::string& event) {
        // Notify all subscribers about the event
        for (auto subscriber : subscribers) {
            subscriber->receiveEvent(event);
        }
    }
};

// Subscriber class
class Subscriber {
    std::string name;

public:
    explicit Subscriber(const std::string& name) : name(name) {}

    void receiveEvent(const std::string& event) {
        std::cout << "Subscriber " << name << " received event: " << event << std::endl;
    }
};

int main() {
    // Create publisher and subscribers
    Publisher publisher;
    Subscriber subscriber1("Subscriber 1");
    Subscriber subscriber2("Subscriber 2");
    Subscriber subscriber3("Subscriber 3");

    // Subscribe subscribers to the publisher
    publisher.subscribe(&subscriber1);
    publisher.subscribe(&subscriber2);
    publisher.subscribe(&subscriber3);

    // Publish an event
    publisher.publishEvent("New event!");

    // Unsubscribe one subscriber
    publisher.unsubscribe(&subscriber2);

    // Publish another event
    publisher.publishEvent("Another event!");

    return 0;
}
