#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person& setName(const std::string& n) {
        name = n;
        return *this;  // Return reference to enable method chaining
    }

    Person& setAge(int a) {
        age = a;
        return *this;  // Return reference to enable method chaining
    }

    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    Person person;
    person.setName("John").setAge(30).display();

    return 0;
}
