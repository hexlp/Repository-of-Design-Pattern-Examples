/*

The Object Pool Pattern is a creational design pattern that aims to improve performance and 
resource utilization by reusing objects instead of creating new ones. It maintains a pool of
initialized objects that are available for use and eliminates the overhead of object creation and destruction.

The Object Pool Pattern is particularly useful in scenarios where creating and destroying 
objects is expensive, such as database connections, network connections, threads, or any 
resource-intensive operations. By maintaining a pool of initialized objects, the pattern allows 
for efficient resource utilization and can significantly improve the overall performance of an application.

*/

#include <iostream>
#include <vector>
#include <memory>

class Resource {
public:
    void doSomething() {
        std::cout << "Resource: Do something." << std::endl;
    }
};

class ResourcePool {
private:
    std::vector<std::shared_ptr<Resource>> resources;
    int maxSize;

public:
    ResourcePool(int size) : maxSize(size) {
        initializePool();
    }

    std::shared_ptr<Resource> acquireResource() {
        if (resources.empty()) {
            std::cout << "No available resources. Creating a new one." << std::endl;
            return std::make_shared<Resource>();
        } else {
            std::cout << "Reusing an existing resource." << std::endl;
            auto resource = resources.back();
            resources.pop_back();
            return resource;
        }
    }

    void releaseResource(std::shared_ptr<Resource> resource) {
        if (resources.size() < maxSize) {
            std::cout << "Returning the resource to the pool." << std::endl;
            resources.push_back(resource);
        }
    }

    void initializePool() {
        std::cout << "Initializing the resource pool." << std::endl;
        for (int i = 0; i < maxSize; ++i) {
            resources.push_back(std::make_shared<Resource>());
        }
    }
};

int main() {
    ResourcePool pool(3);

    auto resource1 = pool.acquireResource();
    resource1->doSomething();

    auto resource2 = pool.acquireResource();
    resource2->doSomething();

    pool.releaseResource(resource1);

    auto resource3 = pool.acquireResource();
    resource3->doSomething();

    return 0;
}
