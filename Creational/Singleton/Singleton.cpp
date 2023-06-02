#include <iostream>


class Singleton
{
private:
	static Singleton* instance;
	Singleton(){}

public:
	static Singleton* getInstance()
	{
		if (instance == 0)
		{
			instance = new Singleton();
		}
		return instance;
	}

	void f() { std::cout << "!\n"; }
};

Singleton* Singleton::instance = 0;

int main() {
	
	Singleton * s1 = Singleton::getInstance();
	Singleton * s2 = Singleton::getInstance();

	std::cout << "s1: "<<  s1 << "\n";
	std::cout << "s2: " << s2 << "\n";	

	std::getchar();
	return 0;
}