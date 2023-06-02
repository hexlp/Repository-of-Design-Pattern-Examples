#include <iostream>
#include <string>

// CelsiusSensor is a specific class representing a temperature sensor that measures in Celsius
class CelsiusSensor {
public:
    float getCelsiusTemperature() const {
        // Simulate temperature reading from the sensor
        return 25.0f;
    }
};

// FahrenheitSensor is a specific class representing a temperature sensor that measures in Fahrenheit
class FahrenheitSensor {
public:
    float getFahrenheitTemperature() const {
        // Simulate temperature reading from the sensor
        return 77.0f;
    }
};

// TemperatureReader is the target interface that the client expects to interact with
class TemperatureReader {
public:
    virtual float getTemperature() const = 0;
};

// Adapter class for adapting the CelsiusSensor to the TemperatureReader interface
class CelsiusAdapter : public TemperatureReader {
public:
    CelsiusAdapter(const CelsiusSensor* celsiusSensor) : celsiusSensor_(celsiusSensor) {}

    float getTemperature() const override {
        // Convert Celsius temperature to Fahrenheit
        return (celsiusSensor_->getCelsiusTemperature() * 9 / 5) + 32;
    }

private:
    const CelsiusSensor* celsiusSensor_;
};

// Adapter class for adapting the FahrenheitSensor to the TemperatureReader interface
class FahrenheitAdapter : public TemperatureReader {
public:
    FahrenheitAdapter(const FahrenheitSensor* fahrenheitSensor) : fahrenheitSensor_(fahrenheitSensor) {}

    float getTemperature() const override {
        // Convert Fahrenheit temperature to Celsius
        return (fahrenheitSensor_->getFahrenheitTemperature() - 32) * 5 / 9;
    }

private:
    const FahrenheitSensor* fahrenheitSensor_;
};

int main() {
    // Client code
    const CelsiusSensor celsiusSensor;
    const FahrenheitSensor fahrenheitSensor;

    const CelsiusAdapter celsiusAdapter(&celsiusSensor);
    const FahrenheitAdapter fahrenheitAdapter(&fahrenheitSensor);

    std::cout << "Temperature in Celsius: " << celsiusAdapter.getTemperature() << " °C" << std::endl;
    std::cout << "Temperature in Fahrenheit: " << fahrenheitAdapter.getTemperature() << " °F" << std::endl;

    return 0;
}
