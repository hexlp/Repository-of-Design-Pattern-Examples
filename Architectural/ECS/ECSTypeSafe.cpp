// This example demonstrates the use of std::type_index to create a type-safe object container.
// The container can store objects of any type and retrieve them later.
// It is also responsible for cleaning up the objects it contains.
// Static casts are employed to convert the base Object pointer to the derived type,
// but this approach is limited to non-polymorphic types known at compile time.

#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <string>

// Base interface
class Object {
public:
    virtual ~Object() = default;
    virtual void PrintInfo() const = 0;
};

// Example object types
class TypeA : public Object {
public:
    void PrintInfo() const override {
        std::cout << "TypeA Object\n";
    }
};

class TypeB : public Object {
public:
    void PrintInfo() const override {
        std::cout << "TypeB Object\n";
    }
};

// Type-safe object container
class ObjectContainer {
public:
    // Destructor to clean up objects
    ~ObjectContainer() {
        for (auto& pair : objects) {
            delete pair.second;
        }
    }

    // Add an object to the container
    template <typename T>
    void AddObject(T* object) {
        objects[typeid(T)] = object;
    }

    // Get an object from the container
    template <typename T>
    T* GetObject() const {
        auto it = objects.find(typeid(T));
        if (it != objects.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }
private:
    std::unordered_map<std::type_index, Object*> objects;
};

int main() {
    ObjectContainer container;

    // Add objects to the container
    container.AddObject(new TypeA);
    container.AddObject(new TypeB);

    // Retrieve and use objects
    TypeA* objA = container.GetObject<TypeA>();
    if (objA) {
        objA->PrintInfo();
    }
    else {
        std::cout << "TypeA object not found\n";
    }

    TypeB* objB = container.GetObject<TypeB>();
    if (objB) {
        objB->PrintInfo();
    }
    else {
        std::cout << "TypeB object not found\n";
    }

    // Clean up
    delete objA;
    delete objB;

    return 0;
}
