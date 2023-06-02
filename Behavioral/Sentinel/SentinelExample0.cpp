/*

Imagine you have a messaging system where multiple processes are communicating through 
a shared message queue.Each process reads messages from the queue and performs some 
actions based on the content of the message.However, there needs to be a way to signal 
the end of the message stream and indicate that the processes should stop consuming messages.

In this scenario, the sentinel or poison pill pattern can be used.A special sentinel message,
also known as a poison pill, is placed at the end of the message stream to indicate that there 
are no more valid messages and the processes should terminate gracefully.

Here's a simplified example to illustrate this:
*/

#include <iostream>
#include <queue>
#include <string>

class Message {
public:
    explicit Message(const std::string& content) : content_(content) {}

    bool isSentinel() const {
        // Check if the message is a sentinel (poison pill)
        return content_ == "STOP";
    }

    std::string getContent() const {
        return content_;
    }

private:
    std::string content_;
};

int main() {
    std::queue<Message> messageQueue;

    // Simulate receiving messages and adding them to the queue
    messageQueue.push(Message("Hello"));
    messageQueue.push(Message("World"));
    messageQueue.push(Message("STOP")); // Sentinel message

    // Process the messages
    while (!messageQueue.empty()) {
        Message message = messageQueue.front();
        messageQueue.pop();

        if (message.isSentinel()) {
            // Detected sentinel message, stop processing
            std::cout << "Received sentinel message. Stopping processing." << std::endl;
            break;
        }

        // Process the valid message
        std::cout << "Received message: " << message.getContent() << std::endl;
    }

    return 0;
}

/*
In this example, the program simulates receiving messages and adding them to 
a message queue.The sentinel message with the content "STOP" is placed at 
the end of the queue to indicate the termination condition.

The program then processes the messages in the queue using a loop.
When a message is dequeued, it checks if the message is a sentinel 
using the `isSentinel()` function.If a sentinel message is detected,
it stops processing the messages and terminates gracefully.Otherwise,
it processes the valid message.

The sentinel or poison pill pattern in this context provides a way to 
explicitly indicate the end of the message stream, allowing the processes
to stop consuming messages when they encounter the sentinel message.
It simplifies the termination logic and ensures that all processes can 
gracefully exit without the need for external signaling mechanisms.
*/