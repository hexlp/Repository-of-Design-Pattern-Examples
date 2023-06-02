#include <iostream>
#include <vector>

// Command interface
class Task {
public:
    virtual ~Task() {}
    virtual void execute() = 0;
};

// Concrete command classes
class EmailTask : public Task {
public:
    void execute() override {
        std::cout << "Sending an email..." << std::endl;
        // Code to send an email
    }
};

class PrintTask : public Task {
public:
    void execute() override {
        std::cout << "Printing a document..." << std::endl;
        // Code to print a document
    }
};

class SaveTask : public Task {
public:
    void execute() override {
        std::cout << "Saving a file..." << std::endl;
        // Code to save a file
    }
};

// Invoker class
class TaskManager {
private:
    std::vector<Task*> tasks;

public:
    void addTask(Task* task) {
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
    TaskManager taskManager;

    // Create commands
    Task* emailTask = new EmailTask();
    Task* printTask = new PrintTask();
    Task* saveTask = new SaveTask();

    // Add commands to the task manager
    taskManager.addTask(emailTask);
    taskManager.addTask(printTask);
    taskManager.addTask(saveTask);

    // Execute the commands
    taskManager.executeTasks();

    // Clean up
    delete emailTask;
    delete printTask;
    delete saveTask;

    return 0;
}
