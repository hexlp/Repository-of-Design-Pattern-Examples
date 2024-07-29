
#include <iostream>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <mutex>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iomanip>

// This is a cross-platform version of localtime function that is thread-safe and doesn't use static buffer
inline std::tm localtime_xp(const std::time_t* timer)
{
    std::tm bt;
#if defined(__unix__)
    localtime_r(timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(timer);
#endif
    return bt;
}

inline std::tm localtime_xp(std::time_t timer)
{
    return localtime_xp(&timer);
}

// Custom time stamp format with a given time
inline std::string time_stamp(const std::string& fmt, std::tm bt)
{
    char buf[64];
    return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}

// Tracker classes
class TrackerBase {
public:
    virtual ~TrackerBase() = default;
    virtual const std::type_info& GetType() const = 0;
    virtual std::size_t GetSize() const = 0;
    virtual std::chrono::system_clock::time_point GetCreationTime() const = 0;
};

class Tracker {
public:
    static Tracker& GetInstance() {
        static Tracker instance;
        return instance;
    }

    void AddInstance(TrackerBase* instance) {
        std::lock_guard<std::mutex> lock(mutex_);
        instances_[std::type_index(instance->GetType())].push_back(instance);
    }

    void RemoveInstance(TrackerBase* instance) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& vec = instances_[std::type_index(instance->GetType())];
        vec.erase(std::remove(vec.begin(), vec.end(), instance), vec.end());
        if (vec.empty()) {
            instances_.erase(std::type_index(instance->GetType()));
        }
    }

    void PrintInstances() const {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& [type, vec] : instances_) {
            std::cout << "Type: " << type.name() << ", Count: " << vec.size() << std::endl;
        }
    }

    template<typename T>
    std::size_t GetInstanceCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = instances_.find(std::type_index(typeid(T)));
        return (it != instances_.end()) ? it->second.size() : 0;
    }

    std::size_t GetTotalInstanceCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::size_t total = 0;
        for (const auto& [_, vec] : instances_) {
            total += vec.size();
        }
        return total;
    }

    std::size_t GetTotalMemoryUsage() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::size_t total = 0;
        for (const auto& [_, vec] : instances_) {
            for (const auto& instance : vec) {
                total += instance->GetSize();
            }
        }
        return total;
    }

    void PrintDetailedInfo() const {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << std::setw(30) << "Type" << std::setw(10) << "Count" << std::setw(15) << "Total Size" << std::setw(25) << "Oldest Instance" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        for (const auto& [type, vec] : instances_) {
            std::size_t totalSize = 0;
            std::chrono::system_clock::time_point oldestTime = std::chrono::system_clock::now();
            for (const auto& instance : vec) {
                totalSize += instance->GetSize();
                oldestTime = std::min(oldestTime, instance->GetCreationTime());
            }
            std::time_t oldestTimeT = std::chrono::system_clock::to_time_t(oldestTime);
            std::cout << std::setw(30) << type.name()
                << std::setw(10) << vec.size()
                << std::setw(15) << totalSize
                << std::setw(25) << time_stamp("%F %T", localtime_xp(&oldestTimeT))
                << std::endl;
        }
    }

private:
    Tracker() = default;
    ~Tracker() = default;
    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;

    mutable std::mutex mutex_;
    std::unordered_map<std::type_index, std::vector<TrackerBase*>> instances_;
};

template<typename T>
class Trackable : public TrackerBase {
public:
    Trackable() : creationTime_(std::chrono::system_clock::now()) {
        Tracker::GetInstance().AddInstance(this);
    }

    virtual ~Trackable() {
        Tracker::GetInstance().RemoveInstance(this);
    }

    const std::type_info& GetType() const override {
        return typeid(T);
    }

    std::size_t GetSize() const override {
        return sizeof(T);
    }

    std::chrono::system_clock::time_point GetCreationTime() const override {
        return creationTime_;
    }

private:
    std::chrono::system_clock::time_point creationTime_;
};

// Example classes
class MyClass1 : public Trackable<MyClass1> {
    int data[100];

public:
    MyClass1() {
        for (int i = 0; i < 100; ++i) {
            data[i] = i;
        }
    }

};

class MyClass2 : public Trackable<MyClass2> {
    std::string data;
};

int main() {
    std::vector<std::unique_ptr<MyClass1>> vec1;
    std::vector<std::unique_ptr<MyClass2>> vec2;

    for (int i = 0; i < 5; ++i) {
        vec1.push_back(std::make_unique<MyClass1>());
    }

    for (int i = 0; i < 3; ++i) {
        vec2.push_back(std::make_unique<MyClass2>());
    }

    std::cout << "Current instances:" << std::endl;
    Tracker::GetInstance().PrintInstances();

    std::cout << "\nDetailed information:" << std::endl;
    Tracker::GetInstance().PrintDetailedInfo();

    std::cout << "\nTotal instance count: " << Tracker::GetInstance().GetTotalInstanceCount() << std::endl;
    std::cout << "Total memory usage: " << Tracker::GetInstance().GetTotalMemoryUsage() << " bytes" << std::endl;

    std::cout << "\nMyClass1 instance count: " << Tracker::GetInstance().GetInstanceCount<MyClass1>() << std::endl;
    std::cout << "MyClass2 instance count: " << Tracker::GetInstance().GetInstanceCount<MyClass2>() << std::endl;

    return 0;
}