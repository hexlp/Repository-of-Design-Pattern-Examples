#include <iostream>
#include <string>
#include <vector>

// Abstract Component
class UIComponent {
public:
    virtual void render() = 0;
};

// Leaf Component
class Button : public UIComponent {
private:
    std::string label;

public:
    Button(const std::string& label) : label(label) {}

    void render() override {
        std::cout << "Render Button: " << label << std::endl;
    }
};

// Composite Component
class Panel : public UIComponent {
private:
    std::vector<UIComponent*> components;

public:
    void addComponent(UIComponent* component) {
        components.push_back(component);
    }

    void render() override {
        std::cout << "Render Panel" << std::endl;
        for (UIComponent* component : components) {
            component->render();
        }
    }
};

// Client
int main() {
    // Create UI components
    Button* button1 = new Button("OK");
    Button* button2 = new Button("Cancel");

    Panel* panel = new Panel();
    panel->addComponent(button1);
    panel->addComponent(button2);

    // Render the UI
    panel->render();

    // Clean up
    delete button1;
    delete button2;
    delete panel;

    return 0;
}
