#include <iostream>

// Forward declaration of classes
class Player;
class Warrior;
class Mage;
class Thief;
class NPC;
class Villager;
class Blacksmith;

class NPC {
public:
    virtual void interact(Player& player) = 0;
    virtual void interactWith(Warrior& warrior) = 0;
    virtual void interactWith(Mage& mage) = 0;
    virtual void interactWith(Thief& thief) = 0;
};

class Player {
public:
    virtual void interact(NPC& npc) = 0;
};

class Warrior : public Player {
public:
    void interact(NPC& npc) override;
};

class Mage : public Player {
public:
    void interact(NPC& npc) override;
};

class Thief : public Player {
public:
    void interact(NPC& npc) override;
};

class Villager : public NPC {
public:
    void interact(Player& player) override;
    void interactWith(Warrior& warrior) override;
    void interactWith(Mage& mage) override;
    void interactWith(Thief& thief) override;
};

class Blacksmith : public NPC {
public:
    void interact(Player& player) override;
    void interactWith(Warrior& warrior) override;
    void interactWith(Mage& mage) override;
    void interactWith(Thief& thief) override;
};

// Implementation of Player classes

void Warrior::interact(NPC& npc) {
    npc.interactWith(*this);
}

void Mage::interact(NPC& npc) {
    npc.interactWith(*this);
}

void Thief::interact(NPC& npc) {
    npc.interactWith(*this);
}

// Implementation of NPC classes

void Villager::interact(Player& player) {
    std::cout << "NPC interacts with Player" << std::endl;
    player.interact(*this);
}

void Villager::interactWith(Warrior& warrior) {
    std::cout << "Villager interacts with Warrior" << std::endl;
}

void Villager::interactWith(Mage& mage) {
    std::cout << "Villager interacts with Mage" << std::endl;
}

void Villager::interactWith(Thief& thief) {
    std::cout << "Villager interacts with Thief" << std::endl;
}

void Blacksmith::interact(Player& player) {
    std::cout << "NPC interacts with Player" << std::endl;
    player.interact(*this);
}

void Blacksmith::interactWith(Warrior& warrior) {
    std::cout << "Blacksmith interacts with Warrior" << std::endl;
}

void Blacksmith::interactWith(Mage& mage) {
    std::cout << "Blacksmith interacts with Mage" << std::endl;
}

void Blacksmith::interactWith(Thief& thief) {
    std::cout << "Blacksmith interacts with Thief" << std::endl;
}

int main() {
    Warrior warrior;
    Mage mage;
    Thief thief;
    Villager villager;
    Blacksmith blacksmith;

    warrior.interact(villager);
    mage.interact(blacksmith);
    thief.interact(villager);

    return 0;
}
