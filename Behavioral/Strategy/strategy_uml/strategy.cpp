#include <iostream>
#include <string>

struct IStrategy
{
	virtual void useStrategy() = 0;			
};
struct ConcreteStrategy1 : public IStrategy
{
	void useStrategy() override { std::cout << "Strategy 1\n"; }
};
struct ConcreteStrategy2 : public IStrategy 
{
	void useStrategy() override { std::cout << "Strategy 2\n"; }
};

class Context
{
public:
	enum STRAT
	{
		S1,
		S2
	};
private:

	IStrategy * mStrategy;

public:
	Context(STRAT s)
	{
		switch (s)
		{
		case Context::S1: mStrategy = new ConcreteStrategy1;
			break;
		case Context::S2: mStrategy = new ConcreteStrategy2;
			break;
		default:
			break;
		}
	}	

	void useStrategy() { mStrategy->useStrategy(); }
};




int main() {
	   
	Context c(Context::S2);
	c.useStrategy();

	std::getchar();
	return 0;
}