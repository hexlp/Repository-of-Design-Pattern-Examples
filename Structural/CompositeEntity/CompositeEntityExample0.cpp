/*

The Composite Entity pattern is a design pattern that aims to provide a 
higher-level abstraction by treating a group of related entities as a 
single entity. It combines multiple entities into a composite entity, 
which can be manipulated and managed as a whole.

The key components of the Composite Entity pattern are:

1. Composite Entity: This represents the composite entity 
   that encapsulates a group of related entities. 
   It provides a higher-level interface for accessing and managing the underlying entities.

2. Coarse-Grained Object: This is the main object that 
   interacts with the client and represents the composite entity. 
   It is responsible for handling requests and delegating them to 
   the appropriate underlying entities.

3. Fine-Grained Objects: These are the individual entities or 
   components that make up the composite entity. 
   They are managed and coordinated by the composite entity.

4. Client: This is the external entity that interacts 
   with the composite entity by making requests and receiving responses.

The Composite Entity pattern provides several benefits:

1. Abstraction: It hides the complexity of managing multiple 
   entities behind a single composite entity, providing a 
   simplified interface to the client.
   
2. Modularity: It allows individual entities to be modified 
   or replaced without affecting the overall behavior of the composite entity.

3. Performance: It can optimize operations by performing bulk 
   operations on the group of entities instead of handling them individually.
   
4. Encapsulation: It encapsulates the interaction and coordination 
   between entities, providing a cohesive and unified view to the client.
   
*/


#include <iostream>
#include <string>
#include <vector>

// Fine-Grained Objects
class Entity {
public:
    virtual void process() = 0;
};

class EntityA : public Entity {
public:
    void process() override {
        std::cout << "Processing Entity A" << std::endl;
    }
};

class EntityB : public Entity {
public:
    void process() override {
        std::cout << "Processing Entity B" << std::endl;
    }
};

// Composite Entity
class CompositeEntity {
private:
    EntityA entityA;
    EntityB entityB;

public:
    void process() {
        entityA.process();
        entityB.process();
    }
};

// Client
int main() {
    CompositeEntity compositeEntity;
    compositeEntity.process();

    return 0;
}

/*

In this example, we have two fine-grained objects (`EntityA` and `EntityB`) that 
represent individual entities. The `CompositeEntity` class encapsulates these 
entities and provides a higher-level interface to the client. 
The `CompositeEntity` class delegates the processing to the underlying fine-grained objects.

When the client invokes the `process` method on the `CompositeEntity` instance, 
it triggers the processing of both `EntityA` and `EntityB` objects as a single entity. 
The client doesn't need to interact with the individual entities directly; 
it treats the composite entity as a cohesive unit.

The Composite Entity pattern can be extended to handle more complex scenarios 
with additional entities and operations. It is particularly useful when dealing 
with groups of related entities that need to be managed and manipulated together.

*/