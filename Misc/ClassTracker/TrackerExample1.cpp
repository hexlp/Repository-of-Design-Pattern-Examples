#include <iostream>
#include <vector>
#include <typeinfo>
#include <mutex>

class TrackerBase {
public:
    virtual ~TrackerBase() = default;
    virtual const std::type_info& GetType() const = 0;
};

class Tracker {
public:
    static Tracker& GetInstance() {
        static Tracker instance;
        return instance;
    }

    void AddInstance(TrackerBase* instance) {
        std::lock_guard<std::mutex> lock(mutex_);
        instances_.push_back(instance);
    }

    void RemoveInstance(TrackerBase* instance) {
        std::lock_guard<std::mutex> lock(mutex_);
        instances_.erase(std::remove(instances_.begin(), instances_.end(), instance), instances_.end());
    }

    void PrintInstances() const {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& instance : instances_) {
            std::cout << instance->GetType().name() << std::endl;
        }
    }

private:
    Tracker() = default;
    ~Tracker() = default;
    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;

    mutable std::mutex mutex_;
    std::vector<TrackerBase*> instances_;
};

template<typename T>
class Trackable : public TrackerBase {
public:
    Trackable() {
        Tracker::GetInstance().AddInstance(this);
    }

    virtual ~Trackable() {
        Tracker::GetInstance().RemoveInstance(this);
    }

    const std::type_info& GetType() const override {
        return typeid(T);
    }
};

class MyClass1 : public Trackable<MyClass1> {
    // Class implementation
};

class MyClass2 : public Trackable<MyClass2> {
    // Class implementation
};


int main() {
    MyClass1 obj1;
    MyClass2 obj2;

    std::cout << "Current instances:" << std::endl;
    Tracker::GetInstance().PrintInstances();

    // Create a new scope to test the destructor of MyClass1
    {
        MyClass1 obj3;
        std::cout << "After creating obj3:" << std::endl;
        Tracker::GetInstance().PrintInstances();
    }

    std::cout << "After obj3 goes out of scope:" << std::endl;
    Tracker::GetInstance().PrintInstances();

    return 0;
}
