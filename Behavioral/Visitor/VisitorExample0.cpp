/*
The Double Dispatch Pattern, also known as the Visitor Pattern, is a design pattern that enables 
dynamic dispatch of method calls based on the runtime types of two objects. It is particularly useful 
when you have a hierarchy of classes and want to perform different operations based on combinations of object types.

The Double Dispatch Pattern allows us to achieve dynamic method dispatch 
based on both the runtime type of the shape object and the visitor object. 
This enables us to perform different operations based on combinations of 
object types without the need for complex type checking or casting.
*/

#include <iostream>

class Shape;

class Visitor {
public:
    virtual void visit(Shape& shape) = 0;
};

class Shape {
public:
    virtual void accept(Visitor& visitor) = 0;
};

class Circle : public Shape {
public:
    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

class Rectangle : public Shape {
public:
    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
};

class AreaCalculator : public Visitor {
public:
    void visit(Shape& shape) override {
        std::cout << "Calculating area for unknown shape." << std::endl;
    }

    void visit(Circle& circle) override {
        std::cout << "Calculating area for circle." << std::endl;
    }

    void visit(Rectangle& rectangle) override {
        std::cout << "Calculating area for rectangle." << std::endl;
    }
};

int main() {
    Circle circle;
    Rectangle rectangle;

    AreaCalculator areaCalculator;
    circle.accept(areaCalculator);
    rectangle.accept(areaCalculator);

    return 0;
}
