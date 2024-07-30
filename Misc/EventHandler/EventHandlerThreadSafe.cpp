#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <queue>

class Event {
public:
    enum class Type {
        MouseClick,
        KeyPress,
        WindowResize,
        Custom
    };

    explicit Event(Type type) : type_(type) {}
    virtual ~Event() = default;

    Type getType() const { return type_; }

private:
    Type type_;
};

// Specialized event classes
class MouseClickEvent : public Event {
public:
    MouseClickEvent(int x, int y) : Event(Type::MouseClick), x_(x), y_(y) {}
    int getX() const { return x_; }
    int getY() const { return y_; }

private:
    int x_, y_;
};

class KeyPressEvent : public Event {
public:
    explicit KeyPressEvent(char key) : Event(Type::KeyPress), key_(key) {}
    char getKey() const { return key_; }

private:
    char key_;
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(int width, int height) : Event(Type::WindowResize), width_(width), height_(height) {}
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

private:
    int width_, height_;
};

class EventHandler {
public:
    using EventCallback = std::function<void(const Event&)>;

    void registerCallback(Event::Type type, EventCallback callback) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        callbacks_[type].push_back(std::move(callback));
    }

    void dispatchEvent(const Event& event) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto it = callbacks_.find(event.getType());
        if (it != callbacks_.end()) {
            for (const auto& callback : it->second) {
                callback(event);
            }
        }
    }

    void clearCallbacks(Event::Type type) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        callbacks_.erase(type);
    }

    void clearAllCallbacks() {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        callbacks_.clear();
    }

private:
    mutable std::shared_mutex mutex_;
    std::unordered_map<Event::Type, std::vector<EventCallback>> callbacks_;
};

class EventQueue {
public:
    EventQueue() : running_(false) {}

    void start(EventHandler& handler) {
        running_ = true;
        worker_thread_ = std::thread(&EventQueue::processEvents, this, std::ref(handler));
    }

    void stop() {
        running_ = false;
        cv_.notify_one();
        if (worker_thread_.joinable()) {
            worker_thread_.join();
        }
    }

    void pushEvent(std::unique_ptr<Event> event) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            events_.push(std::move(event));
        }
        cv_.notify_one();
    }

private:
    void processEvents(EventHandler& handler) {
        while (running_) {
            std::unique_ptr<Event> event;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                cv_.wait(lock, [this] { return !events_.empty() || !running_; });
                if (!running_ && events_.empty()) {
                    return;
                }
                event = std::move(events_.front());
                events_.pop();
            }
            handler.dispatchEvent(*event);
        }
    }

    std::queue<std::unique_ptr<Event>> events_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::atomic<bool> running_;
    std::thread worker_thread_;
};

int main() {
    EventQueue queue;
    EventHandler handler;

    // Register callbacks for different event types
    handler.registerCallback(Event::Type::MouseClick, [](const Event& e) {
        const auto& mouseEvent = static_cast<const MouseClickEvent&>(e);
        std::cout << "Mouse clicked at (" << mouseEvent.getX() << ", " << mouseEvent.getY() << ")\n";
        });

    handler.registerCallback(Event::Type::KeyPress, [](const Event& e) {
        const auto& keyEvent = static_cast<const KeyPressEvent&>(e);
        std::cout << "Key pressed: " << keyEvent.getKey() << "\n";
        });

    handler.registerCallback(Event::Type::WindowResize, [](const Event& e) {
        const auto& resizeEvent = static_cast<const WindowResizeEvent&>(e);
        std::cout << "Window resized to " << resizeEvent.getWidth() << "x" << resizeEvent.getHeight() << "\n";
        });

    // Start the event processing thread, passing the handler
    queue.start(handler);

    // Simulate events occurring over time
    for (int i = 0; i < 5; ++i) {
        queue.pushEvent(std::make_unique<MouseClickEvent>(i * 10, i * 20));
        queue.pushEvent(std::make_unique<KeyPressEvent>('A' + i));
        queue.pushEvent(std::make_unique<WindowResizeEvent>(800 + i * 10, 600 + i * 10));

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Allow some time for all events to be processed
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Stop the event queue
    queue.stop();

    std::cout << "Event processing completed.\n";

    return 0;
}
