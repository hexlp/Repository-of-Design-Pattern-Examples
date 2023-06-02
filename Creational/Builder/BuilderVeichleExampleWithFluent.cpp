
#include <iostream>
#include <string>

struct VeichlePart
{
    std::string partName;
    int         partID;

public:

    VeichlePart(std::string tPartName, int tPartID)
    {
        this->partID = tPartID;
        this->partName = tPartName;
    }

    std::string getPartName() { return this->partName; }
    int getPartID() { return this->partID; }

};

class Engine : public VeichlePart
{
    std::string factory;
    int horsePower;

public:
    Engine() : VeichlePart("Engine", 0)
    {
        this->factory = "Poleswagen";
        this->horsePower = 50;
    }

    int  getHorsePower() { return this->horsePower; }
    void setHorsePower(int tHorsePower) { this->horsePower = tHorsePower; }

};
class Wheels : public VeichlePart
{
    int wheelsNumber;
public:
    Wheels() : VeichlePart("Wheels", 10)
    {
        this->wheelsNumber = 4;
    }
    int  getNumOfWheels() { return this->wheelsNumber; }
    void   setNumOfWheels(int tWheelsNumber) { this->wheelsNumber = tWheelsNumber; }
};
class Battery : public VeichlePart
{
    float chargeLevel;

public:
    Battery() : VeichlePart("Battery", 1250)
    {
        this->chargeLevel = 0;
    }

    float  getChargeLevel() { return this->chargeLevel; }
    void   setChargeLevel(float tChargeLevel) { this->chargeLevel = tChargeLevel; }
};
class Storage : public VeichlePart
{
    int storageSize;

public:
    Storage() : VeichlePart("Storage", 1250)
    {
        this->storageSize = 0;
    }

    int  getStorageSize() { return this->storageSize; }
    void setStorageSize(int tStorageSize) { this->storageSize = tStorageSize; }

};

class Veichle
{
    Engine engine;
    Wheels wheels;
    Battery battery;
    Storage storage;

private:
    std::string getPartName(VeichlePart& part) { return part.getPartName(); }

public:

    void setEngine(Engine& tEngine) { this->engine = tEngine; }
    void setWheels(Wheels& tWheels) { this->wheels = tWheels; }
    void setBattery(Battery& tBattery) { this->battery = tBattery; }
    void setStorage(Storage& tStorage) { this->storage = tStorage; }

    void showcase()
    {
        std::cout << typeid(*this).name() << "\n";
        std::cout << engine.getPartName() << " " << engine.getHorsePower() << "\n";
        std::cout << wheels.getPartName() << " " << wheels.getNumOfWheels() << "\n";
        std::cout << battery.getPartName() << " " << battery.getChargeLevel() << "\n";
        std::cout << storage.getPartName() << " " << storage.getStorageSize() << "\n";
    }

};


class VeichleBuilder
{

protected:

    Veichle* veichle;

public:

    VeichleBuilder()
    {
        this->veichle = new Veichle;
    }

    virtual VeichleBuilder& buildEngine() = 0;
    virtual VeichleBuilder& buildWheels() = 0;
    virtual VeichleBuilder& buildBattery() = 0;
    virtual VeichleBuilder& buildStorage() = 0;

    Veichle* build()
    {
        return this->veichle;
    }
};

class ConcreteVeichleBuilder : public VeichleBuilder
{
public:

    virtual VeichleBuilder& buildEngine() override
    {
        Engine e;
        e.setHorsePower(260);
        this->veichle->setEngine(e);
        return *this;
    }

    virtual VeichleBuilder& buildWheels() override
    {
        Wheels w;
        w.setNumOfWheels(4);
        this->veichle->setWheels(w);
        return *this;
    }

    virtual VeichleBuilder& buildBattery() override
    {
        Battery b;
        b.setChargeLevel(100.0f);
        this->veichle->setBattery(b);
        return *this;
    }

    virtual VeichleBuilder& buildStorage() override
    {
        Storage s;
        s.setStorageSize(1000);
        this->veichle->setStorage(s);
        return *this;
    }

};

int main()
{
    ConcreteVeichleBuilder vbuilder;


    Veichle* veichle = vbuilder.buildEngine()
                               .buildWheels()
                               .buildBattery()
                               .buildStorage()
                               .build();


    veichle->showcase();
    delete veichle;
    return 0;
}
