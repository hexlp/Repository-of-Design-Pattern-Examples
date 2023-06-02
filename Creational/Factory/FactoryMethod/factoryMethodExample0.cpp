#include <iostream>
#include <string>

enum PIZZA_TYPE
{
	Margherita,
	Capricciosa,
	Biancaneve
};

class Pizza
{
private:
	std::string ID;
protected:
	void setID(std::string id) { ID = id; }
public:	
	std::string getID() { return ID; }
};

class PMargherita : public Pizza
{
public:
	PMargherita()
	{
		setID("Margherita");
	}
};
class PCapricciosa : public Pizza
{
public:
	PCapricciosa()
	{
		setID("Capricciosa");
	}
};
class PBiancaneve : public Pizza
{
public:
	PBiancaneve()
	{
		setID("Biancaneve");
	}
};

class SimplePizzaFactory
{
public:
	Pizza * makePizza(PIZZA_TYPE tPizzaType)
	{
		switch (tPizzaType)
		{
		case Margherita:  return new PMargherita;		
		case Capricciosa: return new PCapricciosa;
		case Biancaneve:  return new PBiancaneve;
		default: return new PMargherita;			
		}
	}
};

int main() {

	SimplePizzaFactory pizzaFactory;
	Pizza * pizza = pizzaFactory.makePizza(Biancaneve);
	std::cout << pizza->getID() << std::endl;
	std::getchar();
	return 0;
}