#include <iostream>
#include <string>

// Component interface
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
};

// Concrete component
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }

    double getCost() const override {
        return 1.0;
    }
};

// Decorator base class
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;

public:
    CoffeeDecorator(Coffee* coffee) : coffee(coffee) {}

    std::string getDescription() const override {
        return coffee->getDescription();
    }

    double getCost() const override {
        return coffee->getCost();
    }
};

// Concrete decorators
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double getCost() const override {
        return coffee->getCost() + 0.5;
    }
};

class CaramelDecorator : public CoffeeDecorator {
public:
    CaramelDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Caramel";
    }

    double getCost() const override {
        return coffee->getCost() + 0.75;
    }
};

class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Whipped Cream";
    }

    double getCost() const override {
        return coffee->getCost() + 0.6;
    }
};

int main() {
    // Create a simple coffee
    Coffee* coffee = new SimpleCoffee();
    std::cout << "Description: " << coffee->getDescription() << std::endl;
    std::cout << "Cost: $" << coffee->getCost() << std::endl;

    // Decorate with milk
    coffee = new MilkDecorator(coffee);
    std::cout << "Description: " << coffee->getDescription() << std::endl;
    std::cout << "Cost: $" << coffee->getCost() << std::endl;

    // Decorate with caramel
    coffee = new CaramelDecorator(coffee);
    std::cout << "Description: " << coffee->getDescription() << std::endl;
    std::cout << "Cost: $" << coffee->getCost() << std::endl;

    // Decorate with whipped cream
    coffee = new WhippedCreamDecorator(coffee);
    std::cout << "Description: " << coffee->getDescription() << std::endl;
    std::cout << "Cost: $" << coffee->getCost() << std::endl;

    // Cleanup
    delete coffee;

    return 0;
}
