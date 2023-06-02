
#include <iostream>
#include <string>
#include <array>
#include <map>

using namespace std;

class SoundBehaviour
{
public:
    virtual void play() = 0;

};

class DefaultSoundBehaviour : public SoundBehaviour
{
public:
    virtual void play() override
    {
        std::cout << "default_sound\n";
    }

};

class DogSoundBehaviour : public SoundBehaviour
{
public:
    virtual void play() override
    {
        std::cout << "bark\n";
    }
};

class CatSoundBehaviour : public SoundBehaviour
{
public:
    virtual void play() override
    {
        std::cout << "meow\n";
    }
};

enum class SoundType
{
    DEFAULT,
    DOG,
    CAT
};

struct SoundFactory
{
    virtual SoundBehaviour* createSoundBeahaviour(SoundType soundType)
    {
        switch (soundType)
        {
        case SoundType::DEFAULT:
            return new DefaultSoundBehaviour;
            break;
        case SoundType::DOG:
            return new DogSoundBehaviour;
            break;
        case SoundType::CAT:
            return new CatSoundBehaviour;
            break;
        default:
            return new DefaultSoundBehaviour;
            break;
        }
    }

};

// this should be singleton
class SoundFactoryMap
{
private:

    map<SoundType, SoundBehaviour*> m;

    void bind(SoundType soundType, SoundBehaviour* soundBehaviour)
    {
        this->m.insert(make_pair(SoundType::DEFAULT, soundBehaviour));
    }

public:

    SoundFactoryMap()
    {
        bind(SoundType::DEFAULT, new DefaultSoundBehaviour);
        bind(SoundType::DOG, new DogSoundBehaviour);
        bind(SoundType::CAT, new CatSoundBehaviour);
    }

    ~SoundFactoryMap()
    {
        for (std::map<SoundType, SoundBehaviour*>::iterator itr = m.begin(); itr != m.end(); itr++)
        {
            delete (itr->second);
        }                
    }

    SoundBehaviour* getSoundBeahaviour(SoundType soundType)
    {
        if(m.find(soundType) == m.end())
            return this->m[SoundType::DEFAULT];
        return this->m[soundType];
    }

};

class Animal 
{
    friend class PetCareCenter;

    SoundFactoryMap soundFactory;
    SoundBehaviour* soundBehaviour = nullptr;
    string name = "not_set";

protected:

    void setName(string name)
    {
        this->name = name;
    }

    void setSoundBehaviour(SoundType sound)
    {       
        this->soundBehaviour = soundFactory.getSoundBeahaviour(sound);
    }

public:
    Animal() : soundBehaviour(soundFactory.getSoundBeahaviour(SoundType::DEFAULT))
    {

    }

    virtual ~Animal()
    {
        delete soundBehaviour;
    }

    string getName() const { return name; }

    virtual void makeSound()
    {
        if (soundBehaviour == nullptr)
            return;

        soundBehaviour->play();
    }

};

class Dog : public Animal {};
class Cat : public Animal {};

struct PetCareCenter
{
    void accept(Animal* animal)
    {
        animal->setName("fuffi");
        animal->setSoundBehaviour(SoundType::DOG);
        //animal->setSoundBehaviour(SoundFactory().createSoundBeahaviour(SoundType::DOG));      
    }
};

int main()
{

    Animal* animal = new Dog;

    PetCareCenter pcc;
    pcc.accept(animal);

   // std::cout << animal->getName() << "\n";
    //animal->makeSound();



    delete animal;    
    return 0;
}