#include <iostream>
#include <string>
#include <array>

using namespace std;

class IShapeVisitor
{
public:
      virtual void visit(class Triangle* shape) = 0;
      virtual void visit(class Quad*     shape) = 0;
      virtual void visit(class Circle*   shape) = 0;
};


class ConcreteVisitor: public IShapeVisitor
{   
public:
      virtual void visit(class Triangle* shape)
      {
          std::cout << "Triangle Concrete Visitor\n";        
      }

      virtual void visit(class Quad* shape)
      {
           std::cout << "Quad Concrete Visitor\n";
      }

      virtual void visit(class Circle* shape)
      {
           std::cout << "Circle Concrete Visitor\n";
      }
};


class IShape
{
public:
   virtual void accept(IShapeVisitor* shapeVisitor) = 0;

};

class Triangle : public IShape
{
    
public:

   virtual void accept(IShapeVisitor *visitor)
   { 
      return visitor->visit(this);
   }

}; 

class Circle : public IShape 
{
public:
   virtual void accept(IShapeVisitor *visitor)
   { 
      return visitor->visit(this);
   }
}; 

class Quad : public IShape 
{
public:
   virtual void accept(IShapeVisitor *visitor)
   { 
      return visitor->visit(this);
   }
}; 


/*
class B;

class A
{
   int x = 0;  
   friend B;

 public: 
    void accept(B &b)
    {
        b.visit(*this);        
    } 

};

class B
{    
public:
    void visit(class A &s)
    {
      s.x = 1;          
    }       
};*/

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

class Animal
{
     friend class PetCareCenter;

     string name = "not_set";

     DefaultSoundBehaviour defaultSoundBehaviour;
     SoundBehaviour* soundBehaviour = &defaultSoundBehaviour;

protected:

   void setSoundBehaviour(SoundBehaviour* soundBehaviour)
   {
      this->soundBehaviour = soundBehaviour;
   }

public:   
   virtual ~Animal() 
   {
     delete soundBehaviour;      
   }

   string getName() const { return name; }

   virtual void makeSound()
   {
      if(!soundBehaviour) return;     
      soundBehaviour->play();
   }
        
};

class Dog : public Animal 
{   
};

class Cat : public Animal 
{ 
};

struct PetCareCenter
{
   void accept(Animal* animal)
   {
      animal->name = "fuffi";         
      //animal->setSoundBehaviour(new DogSoundBehaviour);
   }

};

/*int main()
{   
   IShapeVisitor * sv = new ConcreteVisitor();
   std::array<IShape*,3> v = { new Triangle, new Circle, new Quad};

  for (auto&& e: v)
   {

      e->accept(sv);    

   } 

   std::cout << "press any key to exit";
   std::getchar();

	return 0;
}*/

int main()
{   

/*
   Animal* animal = new Dog;

   //PetCareCenter pcc;

   //pcc.accept(animal);   
  
   //std::cout << animal->getName() << "\n";
   animal->makeSound();

   delete animal;*/


   int x = 0;
   int * ptr = &x;

   delete ptr; 

	return 0;
}