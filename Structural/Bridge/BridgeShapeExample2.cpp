/*
The Bridge pattern is a design pattern that decouples an abstraction from its implementation so that the two can vary independently.
 The Bridge pattern allows the abstraction and the implementation to be developed and changed independently.
 This is useful when you want to develop an application with multiple implementations of an abstraction.
*/

class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a square" << std::endl;
    }
};

class Triangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a triangle" << std::endl;
    }
};

class DrawingMode {
public:
    virtual void drawShape(Shape* shape) = 0;
};
class RasterDrawingMode : public DrawingMode {
public:
    void drawShape(Shape* shape) override {
        std::cout << "Drawing shape in raster mode" << std::endl;
        shape->draw();
    }
};

class VectorDrawingMode : public DrawingMode {
public:
    void drawShape(Shape* shape) override {
        std::cout << "Drawing shape in vector mode" << std::endl;
        shape->draw();
    }
};


class Client {
public:
    Client(DrawingMode* drawingMode) : drawingMode_(drawingMode) {}

    void setDrawingMode(DrawingMode* drawingMode) {
        drawingMode_ = drawingMode;
    }

    void drawShape(Shape* shape) {
        drawingMode_->drawShape(shape);
    }

private:
    DrawingMode* drawingMode_;
};

int main() {
    // Create some shapes
    Shape* circle = new Circle();
    Shape* square = new Square();
    Shape* triangle = new Triangle();

    // Create some drawing modes
    DrawingMode* rasterMode = new RasterDrawingMode();
    DrawingMode* vectorMode = new VectorDrawingMode();

    // Create a client
    Client client(rasterMode);

    // Draw some shapes in raster mode
    client.drawShape(circle);
    client.drawShape(square);

    // Switch to vector mode and draw some shapes
    client.setDrawingMode(vectorMode);
    client.drawShape(square);
    client.drawShape(triangle);

    return 0;
}

