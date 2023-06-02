#include <iostream>

class IFlyStrategy
{
public:
	virtual void fly() = 0;
};

class RobotFlyBehaviour : public IFlyStrategy
{
public:
	virtual void fly() override
	{
		std::cout << "jet fly\n";
	}
};

class BirdFlyBehaviour : public IFlyStrategy
{
public:
	virtual void fly() override
	{
		std::cout << "wings fly\n";
	}
};

class Animal
{

private:
	IFlyStrategy* flyStrategy;

public:
	virtual void sound() = 0;

	void setFlyStrategy(IFlyStrategy* strategy)
	{
		this->flyStrategy = strategy;
	}

	void fly() { 
		if (!flyStrategy) return;
		return flyStrategy->fly();
	}
	
};

class Dog : public Animal
{
public:
	virtual void sound() override
	{
		std::cout << "bau\n";
	}
};

class Cat : public Animal
{
public:
	virtual void sound() override
	{
		std::cout << "meow\n";
	}
};

class RobotDog : public Animal
{
	virtual void sound() override
	{
		std::cout << "bark synth\n";
	}
};

class Bird : public Animal
{
public:
	virtual void sound() override
	{
		std::cout << "whistle\n";
	}		
};


int main() {

	BirdFlyBehaviour birdFlyBehaviour;
	Bird bird;	
	bird.setFlyStrategy(&birdFlyBehaviour);

	bird.fly();
	bird.sound();

	return 0;
}

