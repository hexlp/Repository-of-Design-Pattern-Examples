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


int main()
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
}