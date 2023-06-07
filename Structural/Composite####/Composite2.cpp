#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Employee {
public:
    virtual void print() const = 0;
    virtual ~Employee() = default;
};

class Developer : public Employee {
private:
    std::string name;
    std::string role;

public:
    Developer(const std::string& name, const std::string& role) : name(name), role(role) {}

    void print() const override {
        std::cout << "Developer: " << name << ", Role: " << role << std::endl;
    }
};

class Manager : public Employee {
private:
    std::string name;
    std::string department;
    std::vector<std::unique_ptr<Employee>> subordinates;

public:
    Manager(const std::string& name, const std::string& department) : name(name), department(department) {}

    void print() const override {
        std::cout << "Manager: " << name << ", Department: " << department << std::endl;
        for (const auto& subordinate : subordinates) {
            subordinate->print();
        }
    }

    void addSubordinate(std::unique_ptr<Employee> employee) {
        subordinates.push_back(std::move(employee));
    }
};

int main() {
    // Create developers
    std::unique_ptr<Employee> developer1 = std::make_unique<Developer>("John Doe", "Backend Developer");
    std::unique_ptr<Employee> developer2 = std::make_unique<Developer>("Jane Smith", "Frontend Developer");

    // Create managers
    std::unique_ptr<Employee> manager1 = std::make_unique<Manager>("Alice Johnson", "Engineering Manager");
    std::unique_ptr<Employee> manager2 = std::make_unique<Manager>("Bob Thompson", "Product Manager");

    // Compose organizational structure
    static_cast<Manager*>(manager1.get())->addSubordinate(std::move(developer1));
    static_cast<Manager*>(manager1.get())->addSubordinate(std::move(developer2));
    static_cast<Manager*>(manager2.get())->addSubordinate(std::move(manager1));

    // Print organizational structure
    static_cast<Manager*>(manager2.get())->print();

    return 0;
}
