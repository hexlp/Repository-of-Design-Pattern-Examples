/*
The Composite pattern is a structural design pattern 
that allows you to compose objects into tree-like 
structures and work with them as if they were individual 
objects. It lets clients treat individual objects and 
compositions of objects uniformly.

The main idea behind the Composite pattern is to create 
a common interface or abstract class that both individual 
objects and composite objects implement. This interface 
defines operations that can be performed on the objects, 
such as accessing properties, performing actions, or 
navigating through the structure. This way, clients can 
interact with the objects using the same interface, regardless 
of whether they are dealing with individual objects or compositions.

*/


#include <iostream>
#include <vector>

class UIComponent {
public:
    virtual void render() = 0;
    virtual void click() = 0;
    virtual void addChild(UIComponent* component) = 0;
};

class Button : public UIComponent {
public:
    void render() override {
        std::cout << "Rendering button" << std::endl;
    }

    void click() override {
        std::cout << "Button clicked" << std::endl;
    }

    void addChild(UIComponent* component) override {
        // Cannot add child to a button
    }
};

class Panel : public UIComponent {
private:
    std::vector<UIComponent*> children;

public:
    void render() override {
        std::cout << "Rendering panel" << std::endl;
        for (auto child : children) {
            child->render();
        }
    }

    void click() override {
        std::cout << "Panel clicked" << std::endl;
    }

    void addChild(UIComponent* component) override {
        children.push_back(component);
    }
};

int main() {
    // Create UI components
    UIComponent* button1 = new Button();
    UIComponent* button2 = new Button();
    UIComponent* panel = new Panel();

    // Compose UI structure
    panel->addChild(button1);
    panel->addChild(button2);

    // Render and handle clicks
    std::cout << "=== Rendering UI ===" << std::endl;
    panel->render();
    std::cout << "=== Handling click ===" << std::endl;
    panel->click();

    // Clean up
    delete panel;
    delete button1;
    delete button2;

    return 0;
}
