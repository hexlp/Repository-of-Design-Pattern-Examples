

// This example shows how to use the visitor pattern to access components in an ECS system.
// The visitor pattern is a way to separate an algorithm from an object structure on which it operates.
// It allows you to add new operations to an object structure without modifying it.
// It will take advantage of polymorphism to call the correct function for each object type still avoiding dynamic casts. 
// Code complexity is increased, but it is a good solution for a large number of object types.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// Forward declaration
class Entity;

// Component base class
class Component {
public:
    virtual ~Component() = default;
    virtual void Accept(class ComponentVisitor& visitor) = 0;
};

// Visitor interface
class ComponentVisitor {
public:
    virtual ~ComponentVisitor() = default;
    virtual void Visit(PositionComponent& component) = 0;
    virtual void Visit(RenderComponent& component) = 0;
    virtual void Visit(MovementComponent& component) = 0;
};

// Example components
class PositionComponent : public Component {
public:
    float x, y;

    PositionComponent(float x, float y) : x(x), y(y) {}

    void Accept(ComponentVisitor& visitor) override {
        visitor.Visit(*this);
    }
};

class RenderComponent : public Component {
public:
    std::string sprite;

    RenderComponent(const std::string& sprite) : sprite(sprite) {}

    void Accept(ComponentVisitor& visitor) override {
        visitor.Visit(*this);
    }
};

class MovementComponent : public Component {
public:
    float speed;

    MovementComponent(float speed) : speed(speed) {}

    void Accept(ComponentVisitor& visitor) override {
        visitor.Visit(*this);
    }
};

// Entity class
class Entity {
public:
    std::unordered_map<std::string, Component*> components;

    ~Entity() {
        for (auto& pair : components) {
            delete pair.second;
        }
    }
};

// ECS manager
class ECS {
public:
    std::vector<Entity*> entities;

    ~ECS() {
        for (Entity* entity : entities) {
            delete entity;
        }
    }

    // Create a new entity
    Entity* CreateEntity() {
        Entity* entity = new Entity();
        entities.push_back(entity);
        return entity;
    }

    // Add a component to an entity
    template <typename T, typename... Args>
    T* AddComponent(Entity* entity, Args&&... args) {
        T* component = new T(std::forward<Args>(args)...);
        entity->components[typeid(T).name()] = component;
        return component;
    }

    // Use a visitor to get a component from an entity
    template <typename T>
    T* GetComponent(Entity* entity, ComponentVisitor& visitor) {
        auto it = entity->components.find(typeid(T).name());
        if (it != entity->components.end()) {
            it->second->Accept(visitor);
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }
};

// Concrete visitor implementation
class PrintComponentVisitor : public ComponentVisitor {
public:
    void Visit(PositionComponent& component) override {
        std::cout << "Position Component: (" << component.x << ", " << component.y << ")\n";
    }

    void Visit(RenderComponent& component) override {
        std::cout << "Render Component: " << component.sprite << "\n";
    }

    void Visit(MovementComponent& component) override {
        std::cout << "Movement Component: Speed " << component.speed << "\n";
    }
};

int main() {
    ECS ecs;

    // Create entities and add components
    Entity* player = ecs.CreateEntity();
    ecs.AddComponent<PositionComponent>(player, 0.0f, 0.0f);
    ecs.AddComponent<RenderComponent>(player, "PlayerSprite");
    ecs.AddComponent<MovementComponent>(player, 5.0f);

    Entity* enemy = ecs.CreateEntity();
    ecs.AddComponent<PositionComponent>(enemy, 10.0f, 5.0f);
    ecs.AddComponent<RenderComponent>(enemy, "EnemySprite");
    ecs.AddComponent<MovementComponent>(enemy, 2.0f);

    // Access and use components using the visitor pattern
    PrintComponentVisitor printVisitor;

    PositionComponent* playerPosition = ecs.GetComponent<PositionComponent>(player, printVisitor);
    RenderComponent* enemyRender = ecs.GetComponent<RenderComponent>(enemy, printVisitor);

    return 0;
}
