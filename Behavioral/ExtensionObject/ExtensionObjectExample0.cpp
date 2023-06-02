#include <iostream>
#include <memory>

// Core object interface
class Shape {
public:
    virtual void draw() const = 0;
};

// Extension object interface
class ColorExtension {
public:
    virtual void setColor(const std::string& color) = 0;
};

// Concrete core object
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle" << std::endl;
    }
};

// Concrete extension object
class ColorExtensionImpl : public ColorExtension {
public:
    void setColor(const std::string& color) override {
        std::cout << "Setting color: " << color << std::endl;
    }
};

// Extension object factory
class ColorExtensionFactory {
public:
    std::shared_ptr<ColorExtension> createColorExtension() {
        return std::make_shared<ColorExtensionImpl>();
    }
};

int main() {
    // Create a core object
    std::unique_ptr<Shape> circle = std::make_unique<Circle>();

    // Attach extension object to the core object
    ColorExtensionFactory colorExtensionFactory;
    std::shared_ptr<ColorExtension> colorExtension = colorExtensionFactory.createColorExtension();
    // Set color using the extension object
    colorExtension->setColor("Red");

    // Draw the shape
    circle->draw();

    return 0;
}
/*

In this example, the Extension Object Pattern is implemented without having a pointer to the extension object within the core object itself. Instead, the core object (`Circle`) and the extension object (`ColorExtensionImpl`) are separate entities.

The core object (`Circle`) represents the fundamental functionality of a shape and provides the `draw()` method to draw the circle.

The extension object (`ColorExtensionImpl`) represents an extension that adds color functionality to the core object. It implements the `setColor()` method to set the color of the shape.

The extension object factory (`ColorExtensionFactory`) is responsible for creating instances of the extension object (`ColorExtensionImpl`).

In the `main()` function, the core object is created using `std::make_unique<Circle>()`. Then, the extension object is created by using the `ColorExtensionFactory` to create an instance of `ColorExtensionImpl`. This extension object is responsible for providing the color functionality.

Finally, the `setColor()` method of the extension object is called to set the color of the shape, and the `draw()` method of the core object is called to draw the circle.

By separating the core object and the extension object, we can attach the extension to the core object dynamically and independently. This allows us to extend the functionality of the core object without modifying its implementation. It promotes flexibility and modularity in the design of our code.

*/