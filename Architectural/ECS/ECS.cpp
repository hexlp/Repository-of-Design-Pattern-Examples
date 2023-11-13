 //Entity-Component System (ECS) 

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
};

// Example components
class PositionComponent : public Component {
public:
    float x, y;

    PositionComponent(float x, float y) : x(x), y(y) {}
};

class RenderComponent : public Component {
public:
    std::string sprite;

    RenderComponent(const std::string& sprite) : sprite(sprite) {}
};

class MovementComponent : public Component {
public:
    float speed;

    MovementComponent(float speed) : speed(speed) {}
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

    // Get a component from an entity
    template <typename T>
    T* GetComponent(Entity* entity) {
        auto it = entity->components.find(typeid(T).name());
        if (it != entity->components.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
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

    // Access and use components
    PositionComponent* playerPosition = ecs.GetComponent<PositionComponent>(player);
    if (playerPosition) {
        std::cout << "Player Position: (" << playerPosition->x << ", " << playerPosition->y << ")\n";
    }

    RenderComponent* enemyRender = ecs.GetComponent<RenderComponent>(enemy);
    if (enemyRender) {
        std::cout << "Enemy Sprite: " << enemyRender->sprite << "\n";
    }

    return 0;
}
