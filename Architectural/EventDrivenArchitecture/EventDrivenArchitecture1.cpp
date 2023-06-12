#include <iostream>
#include <vector>
#include <string>

class MessageConsumer {
public:
    void consumeMessage(const std::string& message) {
        // Process the consumed message
        std::cout << "Consumed message: " << message << std::endl;
    }
};


class MessageBroker {
private:
    std::vector<MessageConsumer*> consumers;

public:
    static MessageBroker& getInstance() {
        static MessageBroker instance;
        return instance;
    }

    void subscribeConsumer(MessageConsumer* consumer) {
        // Add the consumer to the list of subscribers
        consumers.push_back(consumer);
    }

    void publishMessage(const std::string& message) {
        // Notify all the subscribers about the published message
        for (auto consumer : consumers) {
            consumer->consumeMessage(message);
        }
    }

private:
    MessageBroker() {}  // Private constructor to enforce singleton pattern
};



class MessageProducer {
public:
	void produceMessage(const std::string& message) {
		// Publish the message to the message broker
		MessageBroker::getInstance().publishMessage(message);
	}
};


int main() {
    // Create instances of MessageProducer and MessageConsumer
    MessageProducer producer;
    MessageConsumer consumer;

    // Subscribe the consumer to the message broker
    MessageBroker::getInstance().subscribeConsumer(&consumer);

    // Produce a message
    producer.produceMessage("Hello, world!");

    return 0;
}
