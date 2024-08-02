#include <iostream>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <optional>

template <typename T>
class DependencyContainer {
    std::unordered_map<std::string, std::shared_ptr<T>> dependencies;
public:
    void register_dependency(const std::string& name, std::shared_ptr<T> dependency) {
        dependencies[name] = std::move(dependency);
    }

    void unregister_dependency(const std::string& name) {
        dependencies.erase(name);
    }

    std::optional<std::shared_ptr<T>> get_dependency(const std::string& name) const {
        auto it = dependencies.find(name);
        if (it != dependencies.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    const std::unordered_map<std::string, std::shared_ptr<T>>& get_dependencies() const {
        return dependencies;
    }
};

template <typename T>
class Observer {
public:
    virtual void notify(const T& data) = 0;
    virtual ~Observer() = default;
};

template <typename T>
class Subject {
public:
    void add_observer(const std::string& name, std::shared_ptr<Observer<T>> observer) {
        container.register_dependency(name, std::move(observer));
    }

    void remove_observer(const std::string& name) {
        container.unregister_dependency(name);
    }

    void notify_observers(const T& data) const {
        for (const auto& [name, observer] : container.get_dependencies()) {
            observer->notify(data);
        }
    }

    virtual void set_data(const T& data) = 0;
    virtual ~Subject() = default;

protected:
    DependencyContainer<Observer<T>> container;
};

class ConcreteObserver : public Observer<std::string> {
public:
    void notify(const std::string& data) override {
        std::cout << "Observer notified with data: " << data << std::endl;
    }
};

class AnotherObserver : public Observer<std::string> {
public:
    void notify(const std::string& data) override {
        std::cout << "Another Observer notified with data: " << data << std::endl;
    }
};

template <typename T>
class ObserverFactory {
public:
    virtual std::unique_ptr<Observer<T>> create_observer() = 0;
    virtual ~ObserverFactory() = default;
};

class ConcreteObserverFactory : public ObserverFactory<std::string> {
public:
    std::unique_ptr<Observer<std::string>> create_observer() override {
        return std::make_unique<ConcreteObserver>();
    }
};

class AnotherObserverFactory : public ObserverFactory<std::string> {
public:
    std::unique_ptr<Observer<std::string>> create_observer() override {
        return std::make_unique<AnotherObserver>();
    }
};

class ConcreteSubject : public Subject<std::string> {
public:

    // Passing the observer factories to the constructor is a better approach than creating them inside the class itself. 
    // It allows to create different types of observers and pass them to the subject without modifying the subject class.
    ConcreteSubject(std::unique_ptr<ObserverFactory<std::string>> factory1,
        std::unique_ptr<ObserverFactory<std::string>> factory2) {
        add_observer("ConcreteObserver", factory1->create_observer());
        add_observer("AnotherObserver", factory2->create_observer());
    }

    void set_data(const std::string& new_data) override {
        data = new_data;
        notify_observers(data);
    }

private:
    std::string data;
};

int main() {
    auto subject = std::make_unique<ConcreteSubject>(
        std::make_unique<ConcreteObserverFactory>(),
        std::make_unique<AnotherObserverFactory>()
    );

    subject->set_data("Hello World");
    return 0;
}
