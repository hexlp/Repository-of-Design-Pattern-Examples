#include <iostream>
#include <string>


class Beverage
{
private:
public:
	Beverage() {}
	~Beverage(){}

	virtual int cost() = 0;
	virtual std::string description() = 0;
};

class Espresso : public Beverage
{
public:
	 int cost() override { return 1; }	
	 std::string description() override { return "Espresso "; }
};

class Milk : public Beverage
{
public:
	int cost() override { return 1; }
	std::string description()  override  { return "Milk "; }
};


class AddOnDecorator : public Beverage
{
private:
public:
	AddOnDecorator(){}
	~AddOnDecorator(){}
	virtual int cost() = 0;
	virtual std::string description() = 0;
};

class Caramel : public AddOnDecorator
{
private:
	Beverage * mBeverage;
public:	
	Caramel(Beverage * tBeverage):mBeverage(tBeverage){}
	
	int cost() override { return mBeverage->cost() + 1; }
	std::string description()  override { return mBeverage->description() + "Caramel "; }
};

class Chocolate : public AddOnDecorator
{
private:
	Beverage * mBeverage;
public:
	Chocolate(Beverage * tBeverage) :mBeverage(tBeverage) {}
	int cost() override { return mBeverage->cost() + 1; }
	std::string description()  override { return mBeverage->description() + "Chocolate "; }
};



int main() {

	Milk milk;
	Chocolate chocolate_milk(&milk);
	std::cout << chocolate_milk.description() << " : " << chocolate_milk.cost() << "\n";

	Espresso espresso;
	Caramel caramel_espresso(&espresso);
	Chocolate chocolate_caramel_espresso(&caramel_espresso);
	std::cout << chocolate_caramel_espresso.description() << " : " << chocolate_caramel_espresso.cost();

	std::getchar();
	return 0;
}