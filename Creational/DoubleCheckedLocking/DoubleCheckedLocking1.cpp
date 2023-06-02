#include <iostream>
#include <mutex>

class Resource {
private:
    static Resource* instance;
    static std::mutex mutex;

    Resource() {
        std::cout << "Resource created." << std::endl;
    }

public:
    static Resource* getInstance() {
        if (instance == nullptr) {  // First check without acquiring the lock
            std::lock_guard<std::mutex> lock(mutex);  // Acquire the lock

            if (instance == nullptr) {  // Second check with the lock
                instance = new Resource();  // Create the resource
            }
        }

        return instance;
    }

    void doSomething() {
        std::cout << "Resource in use." << std::endl;
    }
};

Resource* Resource::instance = nullptr;
std::mutex Resource::mutex;

int main() {
    Resource* resource = Resource::getInstance();
    resource->doSomething();

    return 0;
}
