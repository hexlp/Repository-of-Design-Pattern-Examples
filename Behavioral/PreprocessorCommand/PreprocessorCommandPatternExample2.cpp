#include <iostream>
#include <vector>

// Command interface
class Task {
public:
    virtual ~Task() {}
    virtual void execute() = 0;
};

// Concrete command classes
class LightOnCommand : public Task {
public:
    void execute() override {
        std::cout << "Turning the light on." << std::endl;
        // Code to turn the light on
    }
};

class LightOffCommand : public Task {
public:
    void execute() override {
        std::cout << "Turning the light off." << std::endl;
        // Code to turn the light off
    }
};

class FanOnCommand : public Task {
public:
    void execute() override {
        std::cout << "Turning the fan on." << std::endl;
        // Code to turn the fan on
    }
};

class FanOffCommand : public Task {
public:
    void execute() override {
        std::cout << "Turning the fan off." << std::endl;
        // Code to turn the fan off
    }
};

// Invoker class
class RemoteControl {
private:
    std::vector<Task*> tasks;

public:
    void setTask(Task* task) {
        tasks.push_back(task);
    }

    void executeTasks() {
        for (Task* task : tasks) {
            task->execute();
        }
        tasks.clear();
    }
};

int main() {
    RemoteControl remoteControl;

    // Create commands
    Task* lightOn = new LightOnCommand();
    Task* lightOff = new LightOffCommand();
    Task* fanOn = new FanOnCommand();
    Task* fanOff = new FanOffCommand();

    // Set commands on the remote control
    remoteControl.setTask(lightOn);
    remoteControl.setTask(fanOn);
    remoteControl.setTask(lightOff);
    remoteControl.setTask(fanOff);

    // Execute the commands
    remoteControl.executeTasks();

    // Clean up
    delete lightOn;
    delete lightOff;
    delete fanOn;
    delete fanOff;

    return 0;
}
