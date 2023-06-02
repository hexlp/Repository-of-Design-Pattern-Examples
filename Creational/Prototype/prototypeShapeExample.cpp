
#include <iostream>
#include <string>



/*
The Prototype pattern is a creational design pattern that allows you
to clone an existing object instead of creating a new one. 
The key idea behind the Prototype pattern is to create new objects by
copying or cloning existing objects, rather than by creating objects from scratch.

*/

    // Prototype class
class Shape {
public:
    virtual ~Shape() {}
    virtual Shape* clone() const = 0;

    void setColor(const std::string& color) {
        m_color = color;
    }

    void setSize(const int size) {
        m_size = size;
    }

    void setPosition(const int x, const int y) {
        m_x = x;
        m_y = y;
    }

    virtual void draw() const = 0;

protected:
    std::string m_color;
    int m_size;
    int m_x;
    int m_y;
};

// Concrete prototype class: Circle
class Circle : public Shape {
public:
    Circle(const int radius) : m_radius(radius) {}

    Shape* clone() const override {
        return new Circle(*this);
    }

    void draw() const override {
        std::cout << "Drawing a circle at (" << m_x << ", " << m_y << ") with radius " << m_radius << " and color " << m_color << std::endl;
    }

private:
    int m_radius;
};

// Concrete prototype class: Square
class Square : public Shape {
public:
    Square(const int sideLength) : m_sideLength(sideLength) {}

    Shape* clone() const override {
        return new Square(*this);
    }

    void draw() const override {
        std::cout << "Drawing a square at (" << m_x << ", " << m_y << ") with side length " << m_sideLength << " and color " << m_color << std::endl;
    }

private:
    int m_sideLength;
};

// Client code
int main() {
    // Create a prototype circle and clone it to make a new circle
    Circle* circlePrototype = new Circle(10);
    circlePrototype->setColor("red");
    circlePrototype->setSize(2);
    circlePrototype->setPosition(100, 100);

    Shape* circle = circlePrototype->clone();
    circle->setPosition(200, 200);

    circlePrototype->draw(); // Drawing a circle at (100, 100) with radius 10 and color red
    circle->draw(); // Drawing a circle at (200, 200) with radius 10 and color red

    // Create a prototype square and clone it to make a new square
    Square* squarePrototype = new Square(20);
    squarePrototype->setColor("blue");
    squarePrototype->setSize(3);
    squarePrototype->setPosition(300, 300);

    Shape* square = squarePrototype->clone();
    square->setPosition(400, 400);

    squarePrototype->draw(); // Drawing a square at (300, 300) with side length 20 and color blue
    square->draw(); // Drawing a square at (400, 400) with side length 20 and color blue

    // Clean up
    delete circlePrototype;
    delete circle;
    delete squarePrototype;
    delete square;

    return 0;
}
