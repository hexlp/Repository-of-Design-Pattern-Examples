#include <iostream>
#include <string>

// House class represents the product being built
class House {
public:
    void setFoundation(const std::string& foundation) {
        foundation_ = foundation;
    }

    void setStructure(const std::string& structure) {
        structure_ = structure;
    }

    void setRoof(const std::string& roof) {
        roof_ = roof;
    }

    void setInterior(const std::string& interior) {
        interior_ = interior;
    }

    void showInfo() {
        std::cout << "House Info:" << std::endl;
        std::cout << "Foundation: " << foundation_ << std::endl;
        std::cout << "Structure: " << structure_ << std::endl;
        std::cout << "Roof: " << roof_ << std::endl;
        std::cout << "Interior: " << interior_ << std::endl;
    }

private:
    std::string foundation_;
    std::string structure_;
    std::string roof_;
    std::string interior_;
};

// Abstract Builder class
class HouseBuilder {
public:
    virtual void buildFoundation() = 0;
    virtual void buildStructure() = 0;
    virtual void buildRoof() = 0;
    virtual void buildInterior() = 0;
    virtual House* getHouse() = 0;
};

// Concrete Builder class implementing HouseBuilder
class SimpleHouseBuilder : public HouseBuilder {
public:
    void buildFoundation() override {
        house_->setFoundation("Simple Foundation");
    }

    void buildStructure() override {
        house_->setStructure("Simple Structure");
    }

    void buildRoof() override {
        house_->setRoof("Simple Roof");
    }

    void buildInterior() override {
        house_->setInterior("Simple Interior");
    }

    House* getHouse() override {
        return house_;
    }

private:
    House* house_ = new House();
};

// Fluent Builder class for building a house
class FluentHouseBuilder {
public:
    FluentHouseBuilder* buildFoundation(const std::string& foundation) {
        house_->setFoundation(foundation);
        return this;
    }

    FluentHouseBuilder* buildStructure(const std::string& structure) {
        house_->setStructure(structure);
        return this;
    }

    FluentHouseBuilder* buildRoof(const std::string& roof) {
        house_->setRoof(roof);
        return this;
    }

    FluentHouseBuilder* buildInterior(const std::string& interior) {
        house_->setInterior(interior);
        return this;
    }

    House* getHouse() {
        return house_;
    }

private:
    House* house_ = new House();
};

int main() {
    // Using the Builder pattern
    HouseBuilder* simpleHouseBuilder = new SimpleHouseBuilder();
    simpleHouseBuilder->buildFoundation();
    simpleHouseBuilder->buildStructure();
    simpleHouseBuilder->buildRoof();
    simpleHouseBuilder->buildInterior();
    House* simpleHouse = simpleHouseBuilder->getHouse();
    simpleHouse->showInfo();

    std::cout << "-----------------" << std::endl;

    // Using the Fluent Builder pattern
    House* fluentHouse = FluentHouseBuilder()
        ->buildFoundation("Fluent Foundation")
        ->buildStructure("Fluent Structure")
        ->buildRoof("Fluent Roof")
        ->buildInterior("Fluent Interior")
        ->getHouse();
    fluentHouse->showInfo();

    delete simpleHouseBuilder;
    delete simpleHouse;
    delete fluentHouse;

    return 0;
}
