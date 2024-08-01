#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// Forward declarations
class GameEvent;
class GameObject;
class GameObjectFactory;

// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const GameEvent& event) = 0;
};

// Subject interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers(const GameEvent& event) = 0;
};

// Concrete Subject: EventManager
class EventManager : public Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const GameEvent& event) override {
        for (auto observer : observers) {
            observer->onNotify(event);
        }
    }
};

// Game Event class
class GameEvent {
public:
    enum class Type { Collision, ScoreChange, GameOver };

private:
    Type type;
    std::string message;

public:
    GameEvent(Type type, const std::string& message) : type(type), message(message) {}

    Type getType() const { return type; }
    const std::string& getMessage() const { return message; }
};

// Abstract Product: GameObject
class GameObject : public Observer {
protected:
    std::string name;

public:
    GameObject(const std::string& name) : name(name) {}
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void render() const = 0;

    const std::string& getName() const { return name; }
};

// Concrete Products
class Player : public GameObject {
public:
    Player(const std::string& name) : GameObject(name) {}

    void update() override {
        std::cout << "Updating player: " << name << std::endl;
    }

    void render() const override {
        std::cout << "Rendering player: " << name << std::endl;
    }

    void onNotify(const GameEvent& event) override {
        std::cout << "Player " << name << " received event: " << event.getMessage() << std::endl;
        if (event.getType() == GameEvent::Type::Collision) {
            std::cout << "Player " << name << " is checking for damage" << std::endl;
        }
    }
};

class Enemy : public GameObject {
public:
    Enemy(const std::string& name) : GameObject(name) {}

    void update() override {
        std::cout << "Updating enemy: " << name << std::endl;
    }

    void render() const override {
        std::cout << "Rendering enemy: " << name << std::endl;
    }

    void onNotify(const GameEvent& event) override {
        std::cout << "Enemy " << name << " received event: " << event.getMessage() << std::endl;
        if (event.getType() == GameEvent::Type::ScoreChange) {
            std::cout << "Enemy " << name << " is adjusting difficulty" << std::endl;
        }
    }
};

// Abstract Factory: GameObjectFactory
class GameObjectFactory {
public:
    virtual ~GameObjectFactory() = default;
    virtual std::unique_ptr<GameObject> createGameObject(const std::string& name) = 0;
};

// Concrete Factories
class PlayerFactory : public GameObjectFactory {
public:
    std::unique_ptr<GameObject> createGameObject(const std::string& name) override {
        return std::make_unique<Player>(name);
    }
};

class EnemyFactory : public GameObjectFactory {
public:
    std::unique_ptr<GameObject> createGameObject(const std::string& name) override {
        return std::make_unique<Enemy>(name);
    }
};

// Game class to demonstrate the usage
class Game {
private:
    EventManager eventManager;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::unique_ptr<GameObjectFactory> playerFactory;
    std::unique_ptr<GameObjectFactory> enemyFactory;

public:
    Game() :
        playerFactory(std::make_unique<PlayerFactory>()),
        enemyFactory(std::make_unique<EnemyFactory>()) {}

    void initialize() {
        // Create game objects using factories
        auto player = playerFactory->createGameObject("Player1");
        auto enemy1 = enemyFactory->createGameObject("Enemy1");
        auto enemy2 = enemyFactory->createGameObject("Enemy2");

        // Add game objects as observers
        eventManager.addObserver(player.get());
        eventManager.addObserver(enemy1.get());
        eventManager.addObserver(enemy2.get());

        // Store game objects
        gameObjects.push_back(std::move(player));
        gameObjects.push_back(std::move(enemy1));
        gameObjects.push_back(std::move(enemy2));
    }

    void update() {
        for (auto& obj : gameObjects) {
            obj->update();
        }
    }

    void render() const {
        for (const auto& obj : gameObjects) {
            obj->render();
        }
    }

    void simulateEvents() {
        eventManager.notifyObservers(GameEvent(GameEvent::Type::Collision, "Collision detected!"));
        eventManager.notifyObservers(GameEvent(GameEvent::Type::ScoreChange, "Score increased!"));
        eventManager.notifyObservers(GameEvent(GameEvent::Type::GameOver, "Game Over!"));
    }
};

int main() {
    Game game;
    game.initialize();

    std::cout << "Updating game objects:" << std::endl;
    game.update();

    std::cout << "\nRendering game objects:" << std::endl;
    game.render();

    std::cout << "\nSimulating game events:" << std::endl;
    game.simulateEvents();

    return 0;
}