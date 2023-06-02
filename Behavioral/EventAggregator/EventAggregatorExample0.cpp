/*

The Event Aggregator pattern is a messaging pattern that facilitates communication between multiple objects or 
components in a loosely coupled manner. It acts as a central hub or broker for events, allowing publishers to
 publish events and subscribers to subscribe to specific events of interest.

*/


#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

// Event data structure
struct EventData {
    std::string eventName;
    std::string eventData;
};

// Event subscriber interface
class IEventSubscriber {
public:
    virtual ~IEventSubscriber() {}
    virtual void onEvent(const EventData& eventData) = 0;
};

// Event aggregator
class EventAggregator {
public:
    // Publish an event
    void publishEvent(const std::string& eventName, const std::string& eventData) {
        EventData event{ eventName, eventData };
        for (auto& subscriber : subscribers_[eventName]) {
            subscriber->onEvent(event);
        }
    }

    // Subscribe to an event
    void subscribeToEvent(const std::string& eventName, IEventSubscriber* subscriber) {
        subscribers_[eventName].push_back(subscriber);
    }

    // Unsubscribe from an event
    void unsubscribeFromEvent(const std::string& eventName, IEventSubscriber* subscriber) {
        auto& subscribers = subscribers_[eventName];
        subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
    }

private:
    std::unordered_map<std::string, std::vector<IEventSubscriber*>> subscribers_;
};

// Event subscriber implementations

class EventSubscriberA : public IEventSubscriber {
public:
    void onEvent(const EventData& eventData) override {
        std::cout << "EventSubscriberA received event: " << eventData.eventName << " - " << eventData.eventData << std::endl;
    }
};

class EventSubscriberB : public IEventSubscriber {
public:
    void onEvent(const EventData& eventData) override {
        std::cout << "EventSubscriberB received event: " << eventData.eventName << " - " << eventData.eventData << std::endl;
    }
};

int main() {
    // Create the event aggregator
    EventAggregator eventAggregator;

    // Create event subscribers
    EventSubscriberA subscriberA;
    EventSubscriberB subscriberB;

    // Subscribe subscribers to specific events
    eventAggregator.subscribeToEvent("Event1", &subscriberA);
    eventAggregator.subscribeToEvent("Event2", &subscriberB);
    eventAggregator.subscribeToEvent("Event2", &subscriberA);

    // Publish events
    eventAggregator.publishEvent("Event1", "Event1 Data");
    eventAggregator.publishEvent("Event2", "Event2 Data");

    // Unsubscribe subscriberA from Event2
    eventAggregator.unsubscribeFromEvent("Event2", &subscriberA);

    // Publish Event2 again
    eventAggregator.publishEvent("Event2", "Event2 Data");

    return 0;
}

/*

The Event Aggregator pattern shares similarities with the Observer pattern. 
Both patterns involve the communication between multiple objects in a loosely coupled manner.

The Observer pattern establishes a one-to-many dependency relationship where 
multiple observers (also known as subscribers or listeners) are interested in 
being notified when the state of a subject (also known as publisher or observable) changes. 
The subject maintains a list of observers and notifies them automatically when a change occurs.

Similarly, the Event Aggregator pattern allows multiple subscribers to register 
their interest in specific events and receive notifications when those events occur. 
The event aggregator acts as a centralized hub or broker that manages the communication 
between publishers and subscribers. Publishers publish events to the aggregator, 
and the aggregator forwards those events to the appropriate subscribers.

However, there are some differences between the two patterns:

1. Event Aggregator is typically used for decoupling components and
facilitating event-based communication across a system, while the Observer
pattern focuses on establishing a direct relationship between a subject 
and its observers.

2. In the Observer pattern, observers are aware of the subject they are 
observing, and they receive notifications directly from the subject. 
In contrast, in the Event Aggregator pattern, subscribers are not aware 
of the publishers directly. They only interact with the event aggregator, 
which handles the event distribution.

3. The Event Aggregator pattern allows multiple publishers and subscribers 
to participate in the event system, while the Observer pattern typically 
involves a single subject and multiple observers.

In summary, while the Event Aggregator pattern and the Observer pattern share 
some similarities in terms of facilitating communication between components, 
they have different goals and usage scenarios. The Event Aggregator pattern is 
more focused on managing events and decoupling publishers and subscribers, while 
the Observer pattern is focused on establishing a direct relationship between 
a subject and its observers.
*/