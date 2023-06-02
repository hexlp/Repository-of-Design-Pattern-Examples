/*

The Null Object Pattern is a behavioral design pattern that provides an alternative way to
handle null or absent objects. It aims to eliminate the need for explicit null checks and 
improve code maintainability by providing a default or "null" implementation of an interface or class.

The key idea behind the Null Object Pattern is to define a class that implements the same 
interface as the expected object but represents a null or no-op behavior. This null object can
be used in place of actual objects, allowing the code to continue executing without the need for null checks.

By using the Null Object Pattern, we can simplify our code by avoiding null checks and ensuring that the behavior
of absent objects is handled gracefully. It can improve code readability, reduce the chances of null reference exceptions,
and make the system more maintainable by providing default behavior in the absence of real objects.

*/

#include <iostream>
#include <string>

// Abstract base class defining the interface
class Logger {
public:
    virtual void log(const std::string& message) = 0;
};

// Concrete implementation of Logger
class ConsoleLogger : public Logger {
public:
    void log(const std::string& message) override {
        std::cout << "Logging to console: " << message << std::endl;
    }
};

// NullObjectLogger representing a null or no-op behavior
class NullObjectLogger : public Logger {
public:
    void log(const std::string& message) override {
        // Do nothing (null behavior)
    }
};

int main() {
    Logger* logger = nullptr;

    // Create a ConsoleLogger if needed
    bool enableLogging = true;
    if (enableLogging) {
        logger = new ConsoleLogger();
    } else {
        logger = new NullObjectLogger();
    }

    // Perform logging
    logger->log("Log message");

    delete logger;

    return 0;
}
