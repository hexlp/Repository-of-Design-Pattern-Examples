
#include <iostream>
#include <vector>

// Base class
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw() const = 0;
};

// Concrete shape class
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// Extension class
class ShapeExtension {
public:
    virtual ~ShapeExtension() {}
    virtual void extendedDraw() const = 0;
};

// Concrete extension class
class ColorExtension : public ShapeExtension {
public:
    void extendedDraw() const override {
        std::cout << "Drawing the shape with color." << std::endl;
    }
};

// Extended shape class using the extension object pattern
class ExtendedShape : public Shape {
public:
    ExtendedShape(Shape* shape) : shape(shape) {}
    ~ExtendedShape() {
        delete shape;
        for (ShapeExtension* extension : extensions) {
            delete extension;
        }
    }

    void addExtension(ShapeExtension* extension) {
        extensions.push_back(extension);
    }

    void draw() const override {
        shape->draw();
        for (ShapeExtension* extension : extensions) {
            extension->extendedDraw();
        }
    }

private:
    Shape* shape;
    std::vector<ShapeExtension*> extensions;
};


int main() {
    Shape* circle = new Circle();

    // Wrap the circle shape with extensions
    ExtendedShape* extendedCircle = new ExtendedShape(circle);
    extendedCircle->addExtension(new ColorExtension());

    // Draw the extended shape
    extendedCircle->draw();

    // Clean up
    delete extendedCircle;

    return 0;
}