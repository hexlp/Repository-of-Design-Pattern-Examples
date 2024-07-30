#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

// Forward declaration
class EventHandler;

// Event class to represent different types of events
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

// Event handler class
class EventHandler {
public:
    using EventCallback = std::function<void(const Event&)>;

    // Register a callback for a specific event type
    void registerCallback(Event::Type type, EventCallback callback) {
        callbacks_[type].push_back(std::move(callback));
    }

    // Dispatch an event to all registered callbacks
    void dispatchEvent(const Event& event) const {
        auto it = callbacks_.find(event.getType());
        if (it != callbacks_.end()) {
            for (const auto& callback : it->second) {
                callback(event);
            }
        }
    }

    // Remove all callbacks for a specific event type
    void clearCallbacks(Event::Type type) {
        callbacks_.erase(type);
    }

    // Remove all callbacks
    void clearAllCallbacks() {
        callbacks_.clear();
    }

private:
    std::unordered_map<Event::Type, std::vector<EventCallback>> callbacks_;
};

// EventQueue class for handling multiple events
class EventQueue {
public:
    // Add an event to the queue
    void pushEvent(std::unique_ptr<Event> event) {
        events_.push_back(std::move(event));
    }

    // Process all events in the queue
    void processEvents(const EventHandler& handler) {
        for (const auto& event : events_) {
            handler.dispatchEvent(*event);
        }
        events_.clear();
    }

private:
    std::vector<std::unique_ptr<Event>> events_;
};

// Example usage
int main() {
    EventHandler handler;
    EventQueue queue;

    // Register callbacks
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

    // Add events to the queue
    queue.pushEvent(std::make_unique<MouseClickEvent>(10, 20));
    queue.pushEvent(std::make_unique<KeyPressEvent>('A'));
    queue.pushEvent(std::make_unique<WindowResizeEvent>(800, 600));

    // Process events
    queue.processEvents(handler);

    return 0;
}