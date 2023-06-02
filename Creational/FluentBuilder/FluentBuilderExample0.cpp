/*
The Step Builder Pattern, also known as the Fluent Builder Pattern, is a creational design
pattern that aims to simplify the construction of complex objects by dividing the 
construction process into a series of individual steps. It allows you to construct objects by
chaining method calls, providing a more readable and intuitive way to configure object properties.


The Step Builder Pattern provides a clear and readable way to construct objects with many 
properties, especially when some properties are optional or have default values. It eliminates
the need for complex constructors with numerous parameters and enhances code readability and maintainability.

By dividing the object construction process into individual steps, the Step Builder Pattern
allows for more flexibility and ease of use. It also allows for the creation of immutable objects
by enforcing proper initialization through the builder steps.

*/


#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;
    std::string address;
    std::string phoneNumber;

    class Builder {
    private:
        Person person;

    public:
        Builder(const std::string& name) {
            person.name = name;
        }

        Builder& setAge(int age) {
            person.age = age;
            return *this;
        }

        Builder& setAddress(const std::string& address) {
            person.address = address;
            return *this;
        }

        Builder& setPhoneNumber(const std::string& phoneNumber) {
            person.phoneNumber = phoneNumber;
            return *this;
        }

        Person build() {
            return person;
        }
    };
};

int main() {
    Person person = Person::Builder("John")
        .setAge(30)
        .setAddress("123 Main St")
        .setPhoneNumber("555-1234")
        .build();

    std::cout << "Name: " << person.name << std::endl;
    std::cout << "Age: " << person.age << std::endl;
    std::cout << "Address: " << person.address << std::endl;
    std::cout << "Phone Number: " << person.phoneNumber << std::endl;

    return 0;
}
