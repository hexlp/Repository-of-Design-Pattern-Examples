#include <stdexcept>
#include <utility>
#include <iostream>
#include <atomic>


template <typename Derived>
class InitializableThreadSafe {
protected:
    std::atomic<bool> initialized{ false };

    void CheckAndSetInitialized() {
        bool expected = false;
        if (!initialized.compare_exchange_strong(expected, true)) {
            throw std::runtime_error("Already initialized");
        }
    }

public:
    template <typename... Args>
    void Initialize(Args&&... args) {
        this->CheckAndSetInitialized();
        static_cast<Derived*>(this)->doInitialize(std::forward<Args>(args)...);
    }

    bool IsInitialized() const {
        return initialized;
    }

};


class MyClass : public InitializableThreadSafe<MyClass> {

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

        MyClass obj;
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


