#include <iostream>
#include <string>

// Abstract component class
class Shape {
public:
    virtual std::string draw() const = 0;
};

// Concrete component class
class Circle : public Shape {
public:
    std::string draw() const override {
        return "Drawing a circle";
    }
};

// Abstract decorator class
class ShapeDecorator : public Shape {
protected:
    Shape* shape; // Pointer to the wrapped component

public:
    ShapeDecorator(Shape* shape) : shape(shape) {}

    std::string draw() const override = 0;
};

// Concrete decorator class
class RedShapeDecorator : public ShapeDecorator {
public:
    RedShapeDecorator(Shape* shape) : ShapeDecorator(shape) {}

    std::string draw() const override {
        return shape->draw() + " in red color";
    }
};

int main() {
    // Create a circle object
    Shape* circle = new Circle();

    // Decorate it with red color
    Shape* redCircle = new RedShapeDecorator(circle);

    // Display the drawing description
    std::cout << redCircle->draw() << std::endl;

    // Cleanup
    delete redCircle;
    delete circle;

    return 0;
}
