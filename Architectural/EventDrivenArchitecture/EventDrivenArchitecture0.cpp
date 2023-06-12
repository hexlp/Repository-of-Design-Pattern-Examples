#include <iostream>
#include <functional>
#include <unordered_map>


// Event Manager
class EventManager {
private:
    std::unordered_map<std::string, std::vector<std::function<void()>>> eventListeners;

public:
    void subscribe(const std::string& eventName, std::function<void()> eventListener) {
        eventListeners[eventName].push_back(eventListener);
    }

    void unsubscribe(const std::string& eventName, std::function<void()> eventListener) {
        auto it = eventListeners.find(eventName);
        if (it != eventListeners.end()) {
            auto& listeners = it->second;
            listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                [&eventListener](const auto& listener) {
                    return listener.target<void()>() == eventListener.target<void()>();
                }), listeners.end());
        }
    }

    void publish(const std::string& eventName) {
        auto it = eventListeners.find(eventName);
        if (it != eventListeners.end()) {
            auto& listeners = it->second;
            for (const auto& listener : listeners) {
                listener();
            }
        }
    }
};

// Event Consumers
class EventConsumer1 {
public:
    void handleEvent() {
        std::cout << "EventConsumer1 handled the event." << std::endl;
    }
};

class EventConsumer2 {
public:
    void handleEvent() {
        std::cout << "EventConsumer2 handled the event." << std::endl;
    }
};

int main() {
    EventManager eventManager;

    // Create event consumers
    EventConsumer1 consumer1;
    EventConsumer2 consumer2;

    // Subscribe event listeners
    eventManager.subscribe("event1", [&consumer1]() { consumer1.handleEvent(); });
    eventManager.subscribe("event2", [&consumer2]() { consumer2.handleEvent(); });

    // Publish events
    eventManager.publish("event1");
    eventManager.publish("event2");

    // Unsubscribe event listeners
    eventManager.unsubscribe("event1", [&consumer1]() { consumer1.handleEvent(); });

    // Publish event after unsubscribing
    eventManager.publish("event1");

    return 0;
}
