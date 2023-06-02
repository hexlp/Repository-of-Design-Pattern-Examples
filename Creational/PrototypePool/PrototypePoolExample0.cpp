/*
The Prototype Pool Pattern is a design pattern that combines the Prototype Pattern and the Object Pool Pattern.
It is used when you need to create and manage a pool of pre-initialized objects (prototypes) to improve performance and resource utilization.
 
By utilizing the Prototype Pool Pattern, we can avoid the overhead of repeatedly creating and initializing new objects.
Instead, we create a pool of pre-initialized prototype objects and clone them as needed. 
This approach can be particularly beneficial when creating new objects is expensive or time-consuming.
 
 
The Prototype Pool Pattern is especially useful in scenarios where objects with similar characteristics are required 
frequently, and the cost of creating new objects is high. By reusing pre-initialized prototypes, we can achieve better
performance and resource utilization in such situations. 
 
*/


#include <iostream>
#include <unordered_map>

class Shape {
public:
    virtual void draw() = 0;
    virtual Shape* clone() = 0;
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a rectangle." << std::endl;
    }

    Shape* clone() override {
        return new Rectangle(*this);
    }
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle." << std::endl;
    }

    Shape* clone() override {
        return new Circle(*this);
    }
};

class PrototypePool {
private:
    std::unordered_map<std::string, Shape*> pool;

public:
    void addPrototype(const std::string& key, Shape* prototype) {
        pool[key] = prototype;
    }

    Shape* getClone(const std::string& key) {
        if (pool.find(key) != pool.end()) {
            return pool[key]->clone();
        }
        return nullptr;
    }
};

int main() {
    PrototypePool pool;

    Rectangle rectangle;
    Circle circle;

    pool.addPrototype("rectangle", &rectangle);
    pool.addPrototype("circle", &circle);

    Shape* clonedRectangle = pool.getClone("rectangle");
    Shape* clonedCircle = pool.getClone("circle");

    if (clonedRectangle != nullptr) {
        clonedRectangle->draw();
        delete clonedRectangle;
    }

    if (clonedCircle != nullptr) {
        clonedCircle->draw();
        delete clonedCircle;
    }

    return 0;
}
