#include <iostream>
#include <string>


class IWeaponBehaviour
{
public:
	virtual void useWeapon() = 0;
};

class KnifeBehaviour : public IWeaponBehaviour
{
public:
	 void useWeapon() override { std::cout << "Knife Behaviour.\n"; };
};


class SwordBehaviour : public IWeaponBehaviour
{
public:
	 void useWeapon() override  { std::cout << "Sword Behaviour.\n"; };
};

class AxeBehaviour : public IWeaponBehaviour
{
public:
	 void useWeapon() override { std::cout << "Axe Behaviour.\n"; };
};

class Character
{
	IWeaponBehaviour * mWeaponBehaviour;
public:

	virtual void setWeaponBehavior(IWeaponBehaviour &tWeaponBehaviour) { this->mWeaponBehaviour = &tWeaponBehaviour; }
	virtual void fight() { mWeaponBehaviour->useWeapon(); }
};

class King : public Character
{
public:

};

class Troll : public Character
{
public:
	
};

class Knight : public Character
{
public:
	
};

int main() {

	SwordBehaviour sword_behaviour;
	AxeBehaviour axe_behaviour;

	Character * knight = new Knight;
	knight->setWeaponBehavior(sword_behaviour);
	knight->fight();

	knight->setWeaponBehavior(axe_behaviour);
	knight->fight();

	std::getchar();
	return 0;
}