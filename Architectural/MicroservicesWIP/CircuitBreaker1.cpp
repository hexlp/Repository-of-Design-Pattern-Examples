/*
The Circuit Breaker pattern is used to handle and prevent cascading 
failures in a distributed system. It acts as a safety mechanism by 
monitoring the availability and responsiveness of a service. 
When the service is experiencing issues or becomes unresponsive, 
the circuit breaker trips and redirects the calls to a fallback 
or alternative path to prevent further degradation of the system.
*/


#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <functional>

// Circuit Breaker states
enum class CircuitBreakerState {
    Closed,
    Open,
    HalfOpen
};

class CircuitBreaker {
private:
    CircuitBreakerState state;
    int failureThreshold;
    int failureCount;
    int recoveryTime;
    std::chrono::time_point<std::chrono::steady_clock> lastFailureTime;

public:
    CircuitBreaker(int threshold, int recoveryTime)
        : state(CircuitBreakerState::Closed), failureThreshold(threshold),
        failureCount(0), recoveryTime(recoveryTime) {}

    void execute(std::function<void()> riskyOperation, std::function<void()> fallback) {
        if (state == CircuitBreakerState::Open) {
            std::chrono::duration<double> elapsedTime = std::chrono::steady_clock::now() - lastFailureTime;
            if (elapsedTime.count() >= recoveryTime) {
                state = CircuitBreakerState::HalfOpen;
            }
            else {
                fallback(); // Use fallback operation
                return;
            }
        }

        try {
            riskyOperation(); // Execute the risky operation
            state = CircuitBreakerState::Closed;
            failureCount = 0;
        }
        catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
            handleFailure();
            fallback(); // Use fallback operation
        }
    }

private:
    void handleFailure() {
        failureCount++;

        if (failureCount >= failureThreshold) {
            state = CircuitBreakerState::Open;
            lastFailureTime = std::chrono::steady_clock::now();
        }
    }
};

// Example usage
int main() {
    CircuitBreaker circuitBreaker(3, 5); // Threshold: 3 failures, Recovery Time: 5 seconds

    // Risky operation
    auto riskyOperation = []() {
        // Simulate an operation that may fail
        throw std::runtime_error("Something went wrong!");
    };

    // Fallback operation
    auto fallbackOperation = []() {
        // Fallback logic to handle the failure
        std::cout << "Fallback operation executed." << std::endl;
    };

    // Execute the risky operation using the circuit breaker
    for (int i = 1; i <= 5; i++) {
        std::cout << "Executing operation " << i << std::endl;
        circuitBreaker.execute(riskyOperation, fallbackOperation);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
