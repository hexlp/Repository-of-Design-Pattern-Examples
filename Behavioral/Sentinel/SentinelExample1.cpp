
#include <iostream>
#include <queue>
#include <thread>
#include <atomic>

// Define the Poison Pill message
const int POISON_PILL = -1;

// Define a shared queue for communication between threads
std::queue<int> messageQueue;
std::atomic<bool> isTerminated(false);

// Producer thread function
void producerThread() {
    // Simulate producing some messages
    for (int i = 1; i <= 10; ++i) {
        // Add message to the queue
        messageQueue.push(i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Add poison pill to signal termination
    messageQueue.push(POISON_PILL);
    isTerminated = true;
}

// Consumer thread function
void consumerThread() {
    while (true) {
        // Check if termination signal received
        if (isTerminated) {
            std::cout << "Termination signal received. Exiting..." << std::endl;
            break;
        }

        // Check if there are messages in the queue
        if (!messageQueue.empty()) {
            // Get the next message from the queue
            int message = messageQueue.front();
            messageQueue.pop();

            // Check if it is the poison pill
            if (message == POISON_PILL) {
                // Signal termination
                isTerminated = true;
                std::cout << "Termination signal received. Exiting..." << std::endl;
                break;
            }

            // Process the message
            std::cout << "Consumed: " << message << std::endl;
        }
    }
}

int main() {
    // Create producer and consumer threads
    std::thread producer(producerThread);
    std::thread consumer(consumerThread);

    // Wait for both threads to finish
    producer.join();
    consumer.join();

    return 0;
}

