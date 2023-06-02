/*
The Flyweight pattern is a structural design pattern that is used to minimize memory usage by sharing as much 
data as possible with other similar objects. The idea is to reuse objects instead of creating new ones, 
and share the common data across multiple objects. This reduces memory usage, as well as the amount 
of data that needs to be copied or transferred between objects.
*/

#include <iostream>
#include <map>

    // Flyweight class
class Character {
public:
    virtual void print() = 0;
};

// Concrete flyweight class
class ConcreteCharacter : public Character {
public:
    ConcreteCharacter(char c) : m_char(c) {}

    void print() override {
        std::cout << "Character: " << m_char << std::endl;
    }

private:
    char m_char;
};

// Flyweight factory class
class CharacterFactory {
public:
    Character* getCharacter(char c) {
        if (m_characters.find(c) == m_characters.end()) {
            // Character not found, create a new one
            m_characters[c] = new ConcreteCharacter(c);
        }

        return m_characters[c];
    }

private:
    std::map<char, Character*> m_characters;
};

// Client code
int main() {
    CharacterFactory factory;

    // Get the characters 'a' and 'b'
    Character* a = factory.getCharacter('a');
    Character* b = factory.getCharacter('b');

    // Print the characters
    a->print();
    b->print();

    // Get the character 'a' again
    Character* a2 = factory.getCharacter('a');

    // Check if it's the same object as the first 'a'
    std::cout << "a == a2: " << (a == a2 ? "true" : "false") << std::endl;

    return 0;
}
