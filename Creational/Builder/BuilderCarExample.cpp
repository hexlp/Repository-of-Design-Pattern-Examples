
#include <iostream>
#include <string>


/*

The Builder pattern can be used to build complex objects step by step. In the case of building a car,
we can imagine that there are many different parts that need to be assembled in order to create a complete car.
Each of these parts can be seen as a separate object that needs to be created, 
and the Builder pattern can be used to create these objects and then assemble them into a final car.

*/

    // Car parts classes
class Engine {
public:
    void setType(std::string type) { type_ = type; }
    std::string getType() const { return type_; }
private:
    std::string type_;
};

class Wheel {
public:
    void setSize(int size) { size_ = size; }
    int getSize() const { return size_; }
private:
    int size_;
};

class Body {
public:
    void setColor(std::string color) { color_ = color; }
    std::string getColor() const { return color_; }
private:
    std::string color_;
};


// Car class (product)
class Car {
public:
    void setEngineType(std::string type) { engine_.setType(type); }
    std::string getEngineType() const { return engine_.getType(); }
    void setWheelSize(int size) { wheel_.setSize(size); }
    int getWheelSize() const { return wheel_.getSize(); }
    void setColor(std::string color) { body_.setColor(color); }
    std::string getColor() const { return body_.getColor(); }
private:
    Engine engine_;
    Wheel wheel_;
    Body body_;
};



// Car builder class
class CarBuilder {
public:
    virtual void buildEngine() = 0;
    virtual void buildWheels() = 0;
    virtual void buildBody() = 0;
    virtual Car* getCar() = 0;
    virtual ~CarBuilder() {}
    
};

// Car builder for a sports car
class SportsCarBuilder : public CarBuilder {
public:
    SportsCarBuilder() : car_(new Car) {}
    ~SportsCarBuilder() { delete car_; }
    void buildEngine() { car_->setEngineType("V8"); }
    void buildWheels() { car_->setWheelSize(19); }
    void buildBody() { car_->setColor("red"); }
    Car* getCar() { return car_; }
private:
    Car* car_;
};

// Car builder for a family car
class FamilyCarBuilder : public CarBuilder {
public:
    FamilyCarBuilder() : car_(new Car) {}
    ~FamilyCarBuilder() { delete car_; }
    void buildEngine() { car_->setEngineType("V6"); }
    void buildWheels() { car_->setWheelSize(16); }
    void buildBody() { car_->setColor("blue"); }
    Car* getCar() { return car_; }
private:
    Car* car_;
};

// Car director class
class CarDirector {
public:
    CarDirector(CarBuilder* builder) : builder_(builder) {}
    void buildCar() {
        builder_->buildEngine();
        builder_->buildWheels();
        builder_->buildBody();
    }
private:
    CarBuilder* builder_;
};


// Client code
int main() {
    // Build a sports car
    CarBuilder* sportsCarBuilder = new SportsCarBuilder;
    CarDirector sportsCarDirector(sportsCarBuilder);
    sportsCarDirector.buildCar();
    Car* sportsCar = sportsCarBuilder->getCar();
    std::cout << "Sports car built with engine type " << sportsCar->getEngineType() << "\n";
    std::cout << "Sports car built with wheel size " << sportsCar->getWheelSize() << "\n";
    std::cout << "Sports car color " << sportsCar->getColor() << "\n";
   

}
