#include <iostream>
#include <string>

void print(std::string x) {	std::cout << x << "\n";}

class PizzaRecipe
{
	std::string id;

protected:
	void makingTheDough() { print("Mixing the dough..."); };  
	virtual void addBase() = 0;
	virtual void addCondiment() = 0;
	virtual void addTopping() = 0;
	void bake() { print("Cooking in oven..."); };      
	void done() { print("Pizza is served!"); }

public:
	PizzaRecipe(std::string id)
	{
		this->id = id;
	}

	void makePizza()                                             // Template method
	{
		print("Making " + id + " Pizza");
		makingTheDough();
		addBase();
		addCondiment();
		addTopping();
		bake();
		done();
	}
};

class Margherita : public PizzaRecipe
{
private:
	void addBase()override { print("Adding Tomato sauce..."); }
	void addCondiment()override { print("Adding Mozzarella Cheese..."); }
	void addTopping()override { print("Adding olive oil and basil..."); };

public:	
	Margherita(): PizzaRecipe("Margherita"){}
};

class Biancaneve : public PizzaRecipe
{
protected:
	void addBase()override { print("No sauce needed..."); }
	void addCondiment()override { print("Adding Mozzarella Cheese..."); }
	void addTopping()override { print("Adding rosemary..."); };

public:
	Biancaneve() : PizzaRecipe("Biancaneve") {}
};

int main()
{
	PizzaRecipe* a = new Margherita();	
	a->makePizza();
	
	std::cout << std::endl;

	PizzaRecipe* b = new Biancaneve();
	b->makePizza();

	delete a;
	delete b;
	return 0;
}