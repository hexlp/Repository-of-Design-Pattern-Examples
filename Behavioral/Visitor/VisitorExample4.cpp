#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define normalize(value, min, max) (1.0f - 0.0f) / (max - min) * (value - max) + 1.0f;

float NormalizeToRange(float value, float min, float max)
{
    float rangeMin = 0.0f;
    float rangeMax = 1.0f;
    return (rangeMax - rangeMin) / (max - min) * (value - max) + rangeMax;
}

float Lerp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

//  If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v.
float Clamp(float value, float rangeMin, float rangeMax)
{
    if (value < rangeMin)
        return rangeMin;

    if (value > rangeMax)
        return rangeMax;

    return value;
}

// Our client will only know about this interface, not which specific gamepad it is using.
class IGamepadFunctionality
{
public:
    virtual string GetGamepadName() = 0;
    virtual void SetVibrationPower(float InPower) = 0;
};

// The following services provide concrete implementations of the above interface.

class XBoxGamepad : public IGamepadFunctionality {
    float VibrationPower = 1.0f;
public:
    string GetGamepadName() override { return "Xbox controller"; }
    void SetVibrationPower(float InPower)override { VibrationPower = Clamp(InPower, 0.0f, 1.0f); }
};

class PlaystationJoystick : IGamepadFunctionality
{
    float VibratingPower = 100.0f;
public:
    string GetGamepadName()  override { return "PlayStation controller"; }
    void SetVibrationPower(float InPower) override { VibratingPower = Clamp(InPower * 100.0f, 0.0f, 100.0f); }
};

class SteamController : public IGamepadFunctionality {
    double Vibrating = 1.0;
public:
    string GetGamepadName()  override { return "Steam controller"; }
    void SetVibrationPower(float InPower) override { Vibrating = static_cast<double>(Clamp(InPower, 0.0f, 1.0f)); }

};

// This class is the client which receives a service.
class Gamepad
{
    IGamepadFunctionality* _GamepadFunctionality;

public:
    // The service is injected through the constructor and stored in the above field.
    Gamepad(IGamepadFunctionality* InGamepadFunctionality)
    {
        _GamepadFunctionality = InGamepadFunctionality;
    }

    void Showcase()
    {
        // The injected service is used.
        string gamepadName = _GamepadFunctionality->GetGamepadName();
        std::cout << "We're using the " << gamepadName << " right now, do you want to change the vibrating power?\n";
    }
};

int main() {

    IGamepadFunctionality* steamController = new SteamController();
    // We could have also passed in an XboxController, PlaystationJoystick, etc.
    // The gamepad doesn't know what it's using and doesn't need to.
    Gamepad* gamepad = new Gamepad(steamController);
    gamepad->Showcase();

    delete steamController;
    delete gamepad;

    return 0;
}