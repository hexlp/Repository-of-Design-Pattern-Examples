// Receiver interface
class IDevice {
public:
    virtual ~IDevice() {}
    virtual void on() = 0;
    virtual void off() = 0;
};

// Receiver implementation: Lights
class Lights : public IDevice {
public:
    virtual void on() override { std::cout << "Lights are on." << std::endl; }
    virtual void off() override { std::cout << "Lights are off." << std::endl; }
};

// Receiver implementation: Heater
class Heater : public IDevice {
public:
    virtual void on() override { std::cout << "Heater is on." << std::endl; }
    virtual void off() override { std::cout << "Heater is off." << std::endl; }
    void setTemperature(float temperature) { std::cout << "Temperature set to " << temperature << " degrees." << std::endl; }
};

// Command interface
class ICommand {
public:
    virtual ~ICommand() {}
    virtual void execute() = 0;
};

// Concrete command implementation: TurnOnLights
class TurnOnLights : public ICommand {
public:
    TurnOnLights(IDevice& device) : m_device(device) {}
    virtual void execute() override { m_device.on(); }
private:
    IDevice& m_device;
};

// Concrete command implementation: TurnOffLights
class TurnOffLights : public ICommand {
public:
    TurnOffLights(IDevice& device) : m_device(device) {}
    virtual void execute() override { m_device.off(); }
private:
    IDevice& m_device;
};

// Concrete command implementation: SetTemperature
class SetTemperature : public ICommand {
public:
    SetTemperature(Heater& device, float temperature) : m_device(device), m_temperature(temperature) {}
    virtual void execute() override { m_device.setTemperature(m_temperature); }
private:
    Heater& m_device;
    float m_temperature;
};

// Invoker
class RemoteControl {
public:
    void setCommand(std::shared_ptr<ICommand> command) {
        m_command = command;
    }
    void pressButton() {
        m_command->execute();
    }
private:
    std::shared_ptr<ICommand> m_command;
};

// Client code
int main() {
    Lights lights;
    Heater heater;
    RemoteControl remoteControl;

    // Turn on the lights
    auto turnOnLightsCommand = std::make_shared<TurnOnLights>(lights);
    remoteControl.setCommand(turnOnLightsCommand);
    remoteControl.pressButton();

    // Turn off the lights
    auto turnOffLightsCommand = std::make_shared<TurnOffLights>(lights);
    remoteControl.setCommand(turnOffLightsCommand);
    remoteControl.pressButton();

    // Set the heater temperature
    auto setTemperatureCommand = std::make_shared<SetTemperature>(heater, 25.0f);
    remoteControl.setCommand(setTemperatureCommand);
    remoteControl.pressButton();

    return 0;
}