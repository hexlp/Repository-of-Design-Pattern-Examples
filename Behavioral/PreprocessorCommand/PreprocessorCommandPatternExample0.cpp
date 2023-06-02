/*
The Command Processor Pattern is a behavioral design pattern that focuses on encapsulating a 
request as an object, thereby decoupling the sender of the request from the object that
performs the actual action. This pattern allows for the abstraction of commands as objects,
which can be stored, manipulated, and executed as needed.

The key components of the Command Processor Pattern are:

1. Command: This is an interface or abstract class that defines the 
common operations that all commands must implement. It typically includes
a method like `execute()` that performs the specific action associated with the command.

2. Concrete Command: These are the concrete implementations of the Command
interface. Each Concrete Command class encapsulates a specific action or
operation and provides the necessary logic to execute that action.

3. Invoker: This is the object that invokes the commands without knowing 
the specifics of how the commands are executed. It typically maintains a
reference to a Command object and can trigger the execution of the 
command by calling the `execute()` method.

4. Receiver: This represents the object that performs the actual action 
associated with the command. The Receiver has the necessary business logic
to carry out the requested operation.

5. Client: The client is responsible for creating the Command objects and
configuring them with the appropriate Receiver. It sets up the commands 
and provides them to the Invoker for execution.

The Command Processor Pattern promotes loose coupling between the sender 
of the command (Invoker) and the receiver of the command, as the Invoker 
does not need to know the details of how the Receiver executes the command.
It provides a way to encapsulate requests as objects, enabling the 
manipulation and management of commands in a flexible and extensible manner.

This pattern is particularly useful in scenarios where you need to queue, log,
undo/redo, or schedule commands. It allows for the implementation of features 
like command history, macro recording, and transactional behavior.

Overall, the Command Processor Pattern helps in structuring and managing complex
operations, promoting flexibility, extensibility, and decoupling in the design of the system.
 
*/
#include <iostream>
#include <vector>

class Vector3 {
public:
    float x, y, z;   
    Vector3(float px = 0.0f, float py = 0.0f, float pz = 0.0f)
        : x(px), y(py), z(pz) {}
};

class Quaternion {
public:
    float w, x, y, z;   
    Quaternion(float pw = 1.0f, float px = 0.0f, float py = 0.0f, float pz = 0.0f)
        : w(pw), x(px), y(py), z(pz) {}
};


class Object {
private:
    Vector3 position;
    Quaternion orientation;

public:
    Object() = default;


    void translate(const Vector3& translation) {
        // Apply translation to the object's position
        position.x += translation.x;
        position.y += translation.y;
        position.z += translation.z;
        std::cout << "Object translated" << std::endl;
    }

    void rotate(const Quaternion& rotation) {
        // Apply rotation to the object's orientation
        orientation.w *= rotation.w;
        orientation.x *= rotation.x;
        orientation.y *= rotation.y;
        orientation.z *= rotation.z;
        std::cout << "Object rotated" << std::endl;
    }

    // Other methods for scaling, changing materials, etc.
};




class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};
class TranslateCommand : public Command {
private:
    Object* object;
    Vector3 translation;

public:
    TranslateCommand(Object* obj, const Vector3& trans)
        : object(obj), translation(trans) {}

    void execute() override {
        object->translate(translation);
    }
};

class RotateCommand : public Command {
private:
    Object* object;
    Quaternion rotation;

public:
    RotateCommand(Object* obj, const Quaternion& rot)
        : object(obj), rotation(rot) {}

    void execute() override {
        object->rotate(rotation);
    }
};

class CommandInvoker {
private:
    std::vector<Command*> commands;

public:
    void addCommand(Command* cmd) {
        commands.push_back(cmd);
    }

    void executeCommands() {
        for (Command* cmd : commands) {
            cmd->execute();
        }
        commands.clear();
    }
};


int main() {
    // Create objects and setup the scene

    CommandInvoker invoker;
    Object* object1 = new Object();
    Object* object2 = new Object();

    // Create commands
    Command* translateCmd = new TranslateCommand(object1, Vector3(1.0f, 0.0f, 0.0f));
    Command* rotateCmd = new RotateCommand(object2, Quaternion(0.0f, 0.0f, 1.0f, 0.0f));

    // Add commands to the invoker
    invoker.addCommand(translateCmd);
    invoker.addCommand(rotateCmd);

    // Execute the commands
    invoker.executeCommands();

    // The objects have been translated and rotated

    // Clean up
    delete object1;
    delete object2;
    delete translateCmd;
    delete rotateCmd;

    return 0;
}