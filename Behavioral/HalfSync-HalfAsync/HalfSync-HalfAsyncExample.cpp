#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// Asynchronous task
void executeAsyncTask(const std::string& task) {
    // Simulating a time-consuming operation
    std::cout << "Executing async task: " << task << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Async task completed: " << task << std::endl;
}

// Synchronous layer
class SyncLayer {
public:
    void processRequest(const std::string& request) {
        // Add the request to the task queue
        std::unique_lock<std::mutex> lock(queueMutex_);
        taskQueue_.push(request);
        lock.unlock();
        conditionVariable_.notify_one();

        // Continue processing other tasks synchronously
        std::cout << "Processing request synchronously: " << request << std::endl;
        // ...
    }

    void stopProcessing() {
        stopFlag_ = true;
        conditionVariable_.notify_all();
        if (workerThread_.joinable()) {
            workerThread_.join();
        }
    }

private:
    std::queue<std::string> taskQueue_;
    std::mutex queueMutex_;
    std::condition_variable conditionVariable_;
    std::atomic<bool> stopFlag_{ false };
    std::thread workerThread_;

    void processTasks() {
        while (!stopFlag_) {
            std::unique_lock<std::mutex> lock(queueMutex_);
            conditionVariable_.wait(lock, [this] { return !taskQueue_.empty() || stopFlag_; });

            // Dequeue and execute the async task
            if (!taskQueue_.empty()) {
                std::string task = taskQueue_.front();
                taskQueue_.pop();
                lock.unlock();

                executeAsyncTask(task);
            }
        }
    }

public:
    SyncLayer() {
        workerThread_ = std::thread(&SyncLayer::processTasks, this);
    }

    ~SyncLayer() {
        stopProcessing();
    }
};

int main() {
    SyncLayer syncLayer;

    // Process requests synchronously
    syncLayer.processRequest("Request 1");
    syncLayer.processRequest("Request 2");
    syncLayer.processRequest("Request 3");

    // Allow some time for async tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Stop processing and join worker thread
    syncLayer.stopProcessing();

    return 0;
}
