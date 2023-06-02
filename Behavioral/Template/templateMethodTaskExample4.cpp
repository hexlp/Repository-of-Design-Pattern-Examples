
/*
The Template Method Pattern is a behavioral design pattern that defines 
the skeleton of an algorithm in a base class and allows derived classes to
provide implementation details. The main idea behind the pattern is to define 
a template method in the base class that outlines the steps of the algorithm,
while allowing derived classes to override certain steps to provide their own implementation.
*/

#include <iostream>
#include <vector>

// Abstract base class for a generic task
class Task {
public:
    virtual ~Task() {}

    // This is the template method that defines the high-level algorithm
    void runTask() {
        std::cout << "Starting task...\n";
        initialize();
        for (int i = 0; i < getNumIterations(); i++) {
            processIteration(i);
        }
        finalize();
        std::cout << "Task completed.\n\n";
    }

protected:
    // These are the steps that will be implemented by the derived classes
    virtual void initialize() = 0;
    virtual int getNumIterations() = 0;
    virtual void processIteration(int iteration) = 0;
    virtual void finalize() = 0;
};

// Concrete implementation of a task that iteratively adds elements to a vector
class VectorTask : public Task {
public:
    VectorTask(int numIterations) : m_numIterations(numIterations) {}

protected:
    void initialize() override {
        std::cout << "Initializing vector...\n";
        m_vector.clear();
    }

    int getNumIterations() override {
        return m_numIterations;
    }

    void processIteration(int iteration) override {
        std::cout << "Adding element " << iteration << " to vector...\n";
        m_vector.push_back(iteration);
    }

    void finalize() override {
        std::cout << "Finalizing vector:\n";
        for (int i : m_vector) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

private:
    int m_numIterations;
    std::vector<int> m_vector;
};

int main() {
    // Create and run a concrete task
    VectorTask task(5);
    task.runTask();

    return 0;
}
