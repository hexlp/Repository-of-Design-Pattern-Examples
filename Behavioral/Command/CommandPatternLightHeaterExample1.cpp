
#include <iostream>
#include <vector>
#include <memory>

// Command interface
class Command {
public:
    virtual void execute() = 0;
};

// Receiver class for the lights
class Light {
public:
    void on() { std::cout << "Light is on\n"; }
    void off() { std::cout << "Light is off\n"; }
};

// Receiver class for the heater
class Heater {
private:
    int temperature_;
public:
    void on() { std::cout << "Heater is on\n"; }
    void off() { std::cout << "Heater is off\n"; }
    void setTemperature(int temperature) { temperature_ = temperature; std::cout << "Heater temperature set to " << temperature_ << " degrees Celsius\n"; }
};

// Command for turning on the light
class LightOnCommand : public Command {
private:
    Light& light_;
public:
    LightOnCommand(Light& light) : light_(light) {}
    void execute() override { light_.on(); }
};

// Command for turning off the light
class LightOffCommand : public Command {
private:
    Light& light_;
public:
    LightOffCommand(Light& light) : light_(light) {}
    void execute() override { light_.off(); }
};

// Command for turning on the heater
class HeaterOnCommand : public Command {
private:
    Heater& heater_;
public:
    HeaterOnCommand(Heater& heater) : heater_(heater) {}
    void execute() override { heater_.on(); }
};

// Command for turning off the heater
class HeaterOffCommand : public Command {
private:
    Heater& heater_;
public:
    HeaterOffCommand(Heater& heater) : heater_(heater) {}
    void execute() override { heater_.off(); }
};

// Command for setting the temperature of the heater
class HeaterSetTemperatureCommand : public Command {
private:
    Heater& heater_;
    int temperature_;
public:
    HeaterSetTemperatureCommand(Heater& heater, int temperature) : heater_(heater), temperature_(temperature) {}
    void execute() override { heater_.setTemperature(temperature_); }
};

// Invoker class for the remote control
class RemoteControl {
private:
    std::vector<std::shared_ptr<Command>> commands_;
public:
    void addCommand(std::shared_ptr<Command> command) { commands_.push_back(command); }
    void executeAll() {
        for (auto& command : commands_) {
            command->execute();
        }
    }
};

// Client code
int main() {
    // Create the receiver objects
    Light light;
    Heater heater;

    // Create the command objects
    std::shared_ptr<Command> lightOnCommand = std::make_shared<LightOnCommand>(light);
    std::shared_ptr<Command> lightOffCommand = std::make_shared<LightOffCommand>(light);
    std::shared_ptr<Command> heaterOnCommand = std::make_shared<HeaterOnCommand>(heater);
    std::shared_ptr<Command> heaterOffCommand = std::make_shared<HeaterOffCommand>(heater);
    std::shared_ptr<Command> heaterSetTemperatureCommand = std::make_shared<HeaterSetTemperatureCommand>(heater, 25);

    // Create the remote control and add the commands
    RemoteControl remoteControl;
    remoteControl.addCommand(lightOnCommand);
    remoteControl.addCommand(lightOffCommand);
    remoteControl.addCommand(heaterOnCommand);
    remoteControl.addCommand(heaterOffCommand);
    remoteControl.addCommand(heaterSetTemperatureCommand);


    remoteControl.executeAll(); 

    return 0;
}
