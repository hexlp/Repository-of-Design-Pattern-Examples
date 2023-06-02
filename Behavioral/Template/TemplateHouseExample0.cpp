#include <iostream>

// Abstract base class
class HouseBuilder {
public:
    // Template method
    void buildHouse() {
        buildFoundation();
        buildWalls();
        buildRoof();
        furnishHouse();
        if (hasGarden()) {
            buildGarden();
        }
    }

    // Abstract methods
    virtual void buildFoundation() = 0;
    virtual void buildWalls() = 0;
    virtual void buildRoof() = 0;
    virtual void furnishHouse() = 0;

    // Hook method
    virtual bool hasGarden() {
        return true;
    }

    // Hook method
    virtual void buildGarden() {
        std::cout << "Building a garden" << std::endl;
    }
};

// Concrete subclass
class WoodenHouseBuilder : public HouseBuilder {
public:
    void buildFoundation() override {
        std::cout << "Building a wooden foundation" << std::endl;
    }

    void buildWalls() override {
        std::cout << "Building wooden walls" << std::endl;
    }

    void buildRoof() override {
        std::cout << "Building a wooden roof" << std::endl;
    }

    void furnishHouse() override {
        std::cout << "Furnishing the wooden house" << std::endl;
    }

    bool hasGarden() override {
        return false;
    }
};

// Concrete subclass
class BrickHouseBuilder : public HouseBuilder {
public:
    void buildFoundation() override {
        std::cout << "Building a brick foundation" << std::endl;
    }

    void buildWalls() override {
        std::cout << "Building brick walls" << std::endl;
    }

    void buildRoof() override {
        std::cout << "Building a brick roof" << std::endl;
    }

    void furnishHouse() override {
        std::cout << "Furnishing the brick house" << std::endl;
    }
};

int main() {
    HouseBuilder* woodenHouseBuilder = new WoodenHouseBuilder();
    woodenHouseBuilder->buildHouse();
    std::cout << "-------------" << std::endl;
    HouseBuilder* brickHouseBuilder = new BrickHouseBuilder();
    brickHouseBuilder->buildHouse();

    delete woodenHouseBuilder;
    delete brickHouseBuilder;

    return 0;
}

