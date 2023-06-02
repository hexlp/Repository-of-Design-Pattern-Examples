class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override {
        // Draw circle
        std::cout << "Drawing circle.\n";
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        // Draw rectangle
        std::cout << "Drawing rectangle.\n";
    }
};

class Triangle : public Shape {
public:
    void draw() override {
        // Draw triangle
        std::cout << "Drawing triangle.\n";
    }
};

class DrawingTool {
public:
    virtual void drawShape(Shape* shape) = 0;
};

class Pencil : public DrawingTool {
public:
    void drawShape(Shape* shape) override {
        // Use pencil to draw shape
        shape->draw();
    }
};

class Brush : public DrawingTool {
public:
    void drawShape(Shape* shape) override {
        // Use brush to draw shape
        shape->draw();
    }
};

class Eraser : public DrawingTool {
public:
    void drawShape(Shape* shape) override {
        // Use eraser to erase shape
        std::cout << "Erase shape.\n";
    }
};

int main() {

    Shape* circle = new Circle();
    Shape* rectangle = new Rectangle();
    Shape* triangle = new Triangle();

    DrawingTool* pencil = new Pencil();
    DrawingTool* brush = new Brush();
    DrawingTool* eraser = new Eraser();

    pencil->drawShape(circle);
    brush->drawShape(rectangle);
    eraser->drawShape(triangle);

    return 0;
}

