#include <stdexcept>
#include <utility>
#include <iostream>
#include <atomic>

template <typename Derived>
class InitializableThreadSafeSingletone {
protected:
    std::atomic<bool> initialized{ false };

    void CheckAndSetInitialized() {
        bool expected = false;
        if (!initialized.compare_exchange_strong(expected, true)) {
            throw std::runtime_error("Already initialized");
        }
    }


    // Protected default constructor and destructor to prevent direct instantiation or deletion.
    InitializableThreadSafeSingletone() = default;
    ~InitializableThreadSafeSingletone() = default;

    // Delete copy constructor and copy assignment operator to prevent copying.
    InitializableThreadSafeSingletone(const InitializableThreadSafeSingletone&) = delete;
    InitializableThreadSafeSingletone& operator=(const InitializableThreadSafeSingletone&) = delete;

    // Delete move constructor and move assignment operator to prevent moving.
    InitializableThreadSafeSingletone(InitializableThreadSafeSingletone&&) = delete;
    InitializableThreadSafeSingletone& operator=(InitializableThreadSafeSingletone&&) = delete;


public:


    template <typename... Args>
    void Initialize(Args&&... args) {
        this->CheckAndSetInitialized();
        static_cast<Derived*>(this)->doInitialize(std::forward<Args>(args)...);
    }

    bool IsInitialized() const {
        return initialized;
    }




    // Provides a global access point to the singleton instance.
    // The instance is created on first use and guaranteed to be destroyed.
    static Derived& Instance() {
        static Derived instance; // Local static variable is initialized once in a thread-safe manner.
        return instance;
    }

};


class MyClass : public InitializableThreadSafeSingletone<MyClass> {

    int x, y;

public:

    void doInitialize(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int GetX() const {
        return x;
    }

    int GetY() const {
        return y;
    }

};


int main() {

    try {

        MyClass& obj = MyClass::Instance();
        obj.Initialize(1, 2);
        obj.Initialize(3, 4); // throws

        std::cout << obj.GetX() << " " << obj.GetY() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}



