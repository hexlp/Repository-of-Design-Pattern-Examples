#include <iostream>
#include <functional>

class CircuitBreaker {
private:
    bool isOpen;

public:
    CircuitBreaker() : isOpen(false) {}

    void execute(std::function<void()> riskyOperation, std::function<void()> fallback) {
        if (isOpen) {
            fallback(); // Use fallback operation
            return;
        }

        try {
            riskyOperation(); // Execute the risky operation
        }
        catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
            handleFailure();
            fallback(); // Use fallback operation
        }
    }

private:
    void handleFailure() {
        isOpen = true;
        std::cout << "Circuit Breaker tripped! Switching to fallback mode." << std::endl;
    }
};

// Example usage
int main() {
    CircuitBreaker circuitBreaker;

    // Risky operation
    auto riskyOperation = []() {
        throw std::runtime_error("Something went wrong!");
    };

    // Fallback operation
    auto fallbackOperation = []() {
        std::cout << "Fallback operation executed." << std::endl;
    };

    // Execute the risky operation using the circuit breaker
    circuitBreaker.execute(riskyOperation, fallbackOperation);

    return 0;
}

