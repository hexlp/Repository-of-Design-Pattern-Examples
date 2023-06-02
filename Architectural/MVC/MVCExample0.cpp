#include <iostream>
#include <vector>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Model {

    int data;

    std::vector<std::weak_ptr<Observer>> observers;

public:
    Model(int data = 0) : data(data) {}

    int getData() const { return data; }

    void attach(std::shared_ptr<Observer> observer) {
        observers.emplace_back(observer);
    }

    void setData(int data) {
        this->data = data;
        notify();
    }

    void notify() {
        for (auto& observer : observers) {
            if (auto observer_shared = observer.lock()) {
                observer_shared->update();
            }
        }
    }
    void print() {
        std::cout << "Model data = " << data << std::endl;
    }
};

class View : public std::enable_shared_from_this<View>, public Observer {
    std::shared_ptr<Model> model;
public:
    View(std::shared_ptr<Model> model) : model(model) {
      
    }

    void update() override {
        // Render the data from the model
    }
    void print() {
        std::cout << "View connected to Model with data = " << model->getData() << std::endl;
    }
};

class Controller {

    std::shared_ptr<Model> model;

public:

    Controller(std::shared_ptr<Model> model) : model(model) {}

    void handleInput() {
        int newData;
        std::cout << "Enter new data: ";
        std::cin >> newData;
        model->setData(newData);
    }

    void print() {
        std::cout << "Controller connected to Model" << std::endl;
    }
};


class Application {

    std::shared_ptr<Model> model;
    std::shared_ptr<View> view;
    std::shared_ptr<Controller> controller;

public:

    Application() {
        model = std::make_shared<Model>();
        view = std::make_shared<View>(model); 
        model->attach(view);
        controller = std::make_shared<Controller>(model);
    }

    void run() {

        while (true) {
            controller->handleInput();

            //testing purpose
            print();
        }

    }

    void print() {
        model->print();
        view->print();
        controller->print();
    }

};


int main() {
    Application app;
    app.run();
    app.print();
    return 0;
}
