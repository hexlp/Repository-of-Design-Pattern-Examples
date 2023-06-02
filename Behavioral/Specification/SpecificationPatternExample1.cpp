#include <iostream>
#include <vector>
#include <string>

// Person class representing an individual
class Person {
public:
    std::string name;
    int age;
    bool isEmployed;

    Person(const std::string& name, int age, bool isEmployed)
        : name(name), age(age), isEmployed(isEmployed) {}
};

// Specification interface defining the rule
class Specification {
public:
    virtual bool isSatisfied(const Person& person) const = 0;
};

// Concrete specification for filtering persons by age
class AgeSpecification : public Specification {
private:
    int minAge;
    int maxAge;

public:
    AgeSpecification(int minAge, int maxAge)
        : minAge(minAge), maxAge(maxAge) {}

    bool isSatisfied(const Person& person) const override {
        return person.age >= minAge && person.age <= maxAge;
    }
};

// Concrete specification for filtering employed persons
class EmploymentSpecification : public Specification {
public:
    bool isSatisfied(const Person& person) const override {
        return person.isEmployed;
    }
};

// Composite specification for combining multiple specifications with OR operator
class OrSpecification : public Specification {
private:
    const Specification& spec1;
    const Specification& spec2;

public:
    OrSpecification(const Specification& spec1, const Specification& spec2)
        : spec1(spec1), spec2(spec2) {}

    bool isSatisfied(const Person& person) const override {
        return spec1.isSatisfied(person) || spec2.isSatisfied(person);
    }
};

// PersonFilter class for filtering persons based on specifications
class PersonFilter {
public:
    std::vector<Person> filter(const std::vector<Person>& persons, const Specification& spec) {
        std::vector<Person> result;
        for (const auto& person : persons) {
            if (spec.isSatisfied(person)) {
                result.push_back(person);
            }
        }
        return result;
    }
};

int main() {
    // Creating some sample persons
    Person p1("Alice", 25, true);
    Person p2("Bob", 30, false);
    Person p3("Charlie", 40, true);
    Person p4("Dave", 35, true);

    std::vector<Person> persons = {p1, p2, p3, p4};

    // Creating specifications
    Specification* ageSpec = new AgeSpecification(30, 50);
    Specification* employedSpec = new EmploymentSpecification();

    // Using the PersonFilter to filter persons based on specifications
    PersonFilter filter;
    std::vector<Person> filteredPersons = filter.filter(persons, *ageSpec);
    std::cout << "Persons between the ages of 30 and 50:" << std::endl;
    for (const auto& person : filteredPersons) {
        std::cout << person.name << " - Age: " << person.age << std::endl;
    }

    filteredPersons = filter.filter(persons, *employedSpec);
    std::cout << "\nEmployed persons:" << std::endl;
    for (const auto& person : filteredPersons) {
        std::cout << person.name << " - Age: " << person.age << std::endl;
    }

    // Creating a composite specification using OR operator
    Specification* ageOrEmployedSpec = new OrSpecification(*ageSpec, *employedSpec);
    filteredPersons = filter.filter(persons, *ageOrEmployedSpec);
    std::cout << "\nPersons between the ages of 30 and 50 or employed:" << std::endl;
    for (const auto& person : filteredPersons) {
        std::cout << person.name << " - Age: " << person.age << std::endl;
    }

    // Clean up dynamically allocated memory
    delete ageSpec;
    delete employedSpec;
    delete ageOrEmployedSpec;

    return 0;
}
