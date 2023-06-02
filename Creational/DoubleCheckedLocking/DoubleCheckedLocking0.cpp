/*

The Double-Checked Locking (DCL) pattern is used to optimize the performance of thread-safe initialization 
of an object while minimizing the synchronization overhead. It allows multiple threads to check the
initialization status of an object without always acquiring the lock, improving efficiency in scenarios
where the object has already been initialized.
*/


#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;
    
    Singleton() {}  // Private constructor to prevent instantiation
    
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {  // First check without acquiring the lock
            std::lock_guard<std::mutex> lock(mutex);  // Acquire the lock

            if (instance == nullptr) {  // Second check with the lock
                instance = new Singleton();  // Create the singleton instance
                std::cout << "Singleton instance created." << std::endl;
            }
        }

        return instance;
    }

    void doSomething() {
        std::cout << "Singleton instance doing something." << std::endl;
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->doSomething();

    return 0;
}
