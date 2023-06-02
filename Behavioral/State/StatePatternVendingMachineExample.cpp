#include <iostream>
#include <string>
using namespace std;

// Forward declarations
class VendingMachine;

// Abstract base class for vending machine states
class VendingMachineState
{
public:
    virtual ~VendingMachineState() {}
    virtual void selectProduct(VendingMachine &machine) = 0;
    virtual void insertCoin(VendingMachine &machine, int value) = 0;
    virtual void dispenseProduct(VendingMachine &machine) = 0;
    virtual void returnChange(VendingMachine &machine) = 0;
};

// Concrete state classes
class ReadyState : public VendingMachineState
{
public:
    virtual void selectProduct(VendingMachine &machine) override
    {
        cout << "Product selected." << endl;
        machine.setState(new SelectionState());
    }
    virtual void insertCoin(VendingMachine &machine, int value) override
    {
        cout << "Coins inserted: " << value << "." << endl;
        machine.addCredit(value);
    }
    virtual void dispenseProduct(VendingMachine &machine) override
    {
        cout << "No product selected yet." << endl;
    }
    virtual void returnChange(VendingMachine &machine) override
    {
        cout << "No change to return." << endl;
    }
};

class SelectionState : public VendingMachineState
{
public:
    virtual void selectProduct(VendingMachine &machine) override
    {
        cout << "Product already selected." << endl;
    }
    virtual void insertCoin(VendingMachine &machine, int value) override
    {
        cout << "Coins inserted: " << value << "." << endl;
        machine.addCredit(value);
    }
    virtual void dispenseProduct(VendingMachine &machine) override
    {
        if (machine.getCredit() >= 50)
        {
            cout << "Product dispensed." << endl;
            machine.setState(new DispenseState());
        }
        else
        {
            cout << "Insufficient credit." << endl;
        }
    }
    virtual void returnChange(VendingMachine &machine) override
    {
        cout << "Change returned." << endl;
        machine.setState(new ChangeState());
    }
};

class DispenseState : public VendingMachineState
{
public:
    virtual void selectProduct(VendingMachine &machine) override
    {
        cout << "Product already selected." << endl;
    }
    virtual void insertCoin(VendingMachine &machine, int value) override
    {
        cout << "Coins inserted: " << value << "." << endl;
        machine.addCredit(value);
    }
    virtual void dispenseProduct(VendingMachine &machine) override
    {
        cout << "Product already dispensed." << endl;
    }
    virtual void returnChange(VendingMachine &machine) override
    {
        cout << "No change to return." << endl;
    }
};

class ChangeState : public VendingMachineState
{
public:
    virtual void selectProduct(VendingMachine &machine) override
    {
        cout << "Product already dispensed." << endl;
    }
    virtual void insertCoin(VendingMachine &machine, int value) override
    {
        cout << "Coins inserted: " << value << "." << endl;
        machine.addCredit(value);
    }

    virtual void dispenseProduct(VendingMachine &machine) override
    {
        cout << "Product already dispensed." << endl;
    }

    virtual void returnChange(VendingMachine &machine) override
    {
        int change = machine.getCredit();
        cout << "Change returned: " << change << "." << endl;
        machine.resetCredit();
        machine.setState(new ReadyState());
    }
};

// Vending machine class
class VendingMachine
{
public:
    VendingMachine() : m_state(new ReadyState()), m_credit(0) {}

    void setState(VendingMachineState *state)
    {
        delete m_state;
        m_state = state;
    }

    void selectProduct()
    {
        m_state->selectProduct(*this);
    }

    void insertCoin(int value)
    {
        m_state->insertCoin(*this, value);
    }

    void dispenseProduct()
    {
        m_state->dispenseProduct(*this);
    }

    void returnChange()
    {
        m_state->returnChange(*this);
    }

    void addCredit(int value)
    {
        m_credit += value;
    }

    int getCredit()
    {
        return m_credit;
    }

    void resetCredit()
    {
        m_credit = 0;
    }

private:
    VendingMachineState *m_state;
    int m_credit;
};

int main()
{

    //VendingMachine machine;
    return 0;
}
