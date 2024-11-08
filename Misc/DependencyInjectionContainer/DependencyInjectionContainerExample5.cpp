






#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set> // Aggiunto per unordered_set
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include <mutex>
#include <set>
#include <string>

// Enum per definire la durata di vita delle dipendenze
enum class Lifetime {
    Singleton,
    Transient,
    Scoped
};

// Forward declaration della classe Scope
class Scope;

// DependencyManager modificato per supportare nomi di registrazione
class DependencyManager {
public:
    // Singleton accessor
    static DependencyManager& getInstance() {
        static DependencyManager instance;
        return instance;
    }

    // Metodi per registrare le dipendenze con un identificatore opzionale
    template<typename T>
    void addSingleton(std::function<std::shared_ptr<T>(Scope&)> factory, const std::string& name = "") {
        registerDependency<T>(factory, Lifetime::Singleton, name);
    }

    template<typename T>
    void addTransient(std::function<std::shared_ptr<T>(Scope&)> factory, const std::string& name = "") {
        registerDependency<T>(factory, Lifetime::Transient, name);
    }

    template<typename T>
    void addScoped(std::function<std::shared_ptr<T>(Scope&)> factory, const std::string& name = "") {
        registerDependency<T>(factory, Lifetime::Scoped, name);
    }

    // Metodo per creare uno scope
    Scope createScope();

    // Delete copy constructor and assignment operator
    DependencyManager(const DependencyManager&) = delete;
    DependencyManager& operator=(const DependencyManager&) = delete;

private:
    DependencyManager() = default;

    // Struct per contenere le informazioni della factory
    struct FactoryInfo {
        std::function<std::shared_ptr<void>(Scope&)> factory;
        Lifetime lifetime;
    };

    // Chiave composta da type_index e nome
    struct TypeNamePair {
        std::type_index type;
        std::string name;

        bool operator==(const TypeNamePair& other) const {
            return type == other.type && name == other.name;
        }
    };

    // Hash per TypeNamePair
    struct TypeNamePairHash {
        std::size_t operator()(const TypeNamePair& key) const {
            return std::hash<std::type_index>()(key.type) ^ std::hash<std::string>()(key.name);
        }
    };

    // Mappa da TypeNamePair a FactoryInfo
    std::unordered_map<TypeNamePair, FactoryInfo, TypeNamePairHash> factories;

    // Mappa per le istanze Singleton
    std::unordered_map<TypeNamePair, std::shared_ptr<void>, TypeNamePairHash> singletonInstances;

    // **Cambiato std::set in std::unordered_set**
    // Unordered set per tracciare le dipendenze in fase di risoluzione (per rilevare cicli)
    std::unordered_set<TypeNamePair, TypeNamePairHash> resolving;

    // Recursive mutex per la thread safety
    std::recursive_mutex mutex;

    // Metodo privato per registrare una dipendenza
    template<typename T>
    void registerDependency(std::function<std::shared_ptr<T>(Scope&)> factory, Lifetime lifetime, const std::string& name) {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        TypeNamePair key{ typeid(T), name };

        if (factories.find(key) != factories.end()) {
            throw std::runtime_error("Factory già registrata per il tipo: " + std::string(typeid(T).name()) + " con nome: " + name);
        }

        factories[key] = FactoryInfo{
            [factory](Scope& scope) -> std::shared_ptr<void> {
                return factory(scope);
            },
            lifetime
        };
    }

    // Metodo interno per risolvere una dipendenza
    template<typename T>
    std::shared_ptr<T> resolve(Scope& scope, const std::string& name);

    friend class Scope;
};

// Classe per gestire gli scope
class Scope {
public:
    explicit Scope(DependencyManager& manager)
        : manager(manager) {}

    // Metodo per risolvere una dipendenza con un nome opzionale
    template<typename T>
    std::shared_ptr<T> resolve(const std::string& name = "") {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        return manager.resolve<T>(*this, name);
    }

private:
    DependencyManager& manager;

    // Mappa per le istanze Scoped
    std::unordered_map<DependencyManager::TypeNamePair, std::shared_ptr<void>, DependencyManager::TypeNamePairHash> scopedInstances;

    // Recursive mutex per la thread safety
    std::recursive_mutex mutex;

    // Metodo per memorizzare un'istanza Scoped
    template<typename T>
    void storeInstance(const std::string& name, std::shared_ptr<T> instance) {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        DependencyManager::TypeNamePair key{ typeid(T), name };
        scopedInstances[key] = instance;
    }

    friend class DependencyManager;
};

// Implementazione del metodo createScope
inline Scope DependencyManager::createScope() {
    return Scope(*this);
}

// Implementazione del metodo resolve
template<typename T>
std::shared_ptr<T> DependencyManager::resolve(Scope& scope, const std::string& name) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    TypeNamePair key{ typeid(T), name };

    // Controllo per dipendenze circolari
    if (resolving.find(key) != resolving.end()) {
        throw std::runtime_error("Dipendenza circolare rilevata per il tipo: " + std::string(typeid(T).name()) + " con nome: " + name);
    }

    // Segna il tipo come in fase di risoluzione
    resolving.insert(key);

    // Gestione Singleton
    auto singletonIt = singletonInstances.find(key);
    if (singletonIt != singletonInstances.end()) {
        resolving.erase(key);
        return std::static_pointer_cast<T>(singletonIt->second);
    }

    // Gestione Scoped
    // Cerca l'istanza nello scope corrente
    auto it = scope.scopedInstances.find(key);
    if (it != scope.scopedInstances.end()) {
        resolving.erase(key);
        return std::static_pointer_cast<T>(it->second);
    }

    // Trova la factory per il tipo e il nome
    auto factoryIt = factories.find(key);
    if (factoryIt == factories.end()) {
        resolving.erase(key);
        throw std::runtime_error("Nessuna factory registrata per il tipo: " + std::string(typeid(T).name()) + " con nome: " + name);
    }

    // Crea l'istanza usando la factory
    std::shared_ptr<void> instance_void = factoryIt->second.factory(scope);

    // Rimuove il tipo dal set di risoluzione
    resolving.erase(key);

    // Casta l'istanza al tipo corretto
    std::shared_ptr<T> instance = std::static_pointer_cast<T>(instance_void);
    if (!instance) {
        throw std::runtime_error("Il cast dell'istanza è fallito per il tipo: " + std::string(typeid(T).name()) + " con nome: " + name);
    }

    // Salva l'istanza se necessario
    if (factoryIt->second.lifetime == Lifetime::Singleton) {
        singletonInstances[key] = instance;
    }
    else if (factoryIt->second.lifetime == Lifetime::Scoped) {
        scope.storeInstance<T>(name, instance);
    }

    return instance;
}






#include <iostream>
#include <cassert>

// (Assicurati di includere il codice del DependencyManager qui)

// Interfaccia ILogger
class ILogger {
public:
    virtual void log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};

// Implementazioni di ILogger
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "[Console] " << message << std::endl;
    }
};

class FileLogger : public ILogger {
public:
    void log(const std::string& message) override {
        // Simulazione della scrittura su file
        std::cout << "[File] " << message << std::endl;
    }
};

// Classe che utilizza ILogger
class Application {
public:
    Application(std::shared_ptr<ILogger> logger) : logger(logger) {}

    void run() {
        logger->log("Application is running.");
    }

private:
    std::shared_ptr<ILogger> logger;
};

int main() {
    DependencyManager& dm = DependencyManager::getInstance();

    // Registrazione di due implementazioni di ILogger
    dm.addSingleton<ILogger>([](Scope&) {
        return std::make_shared<ConsoleLogger>();
        }, "ConsoleLogger");

    dm.addSingleton<ILogger>([](Scope&) {
        return std::make_shared<FileLogger>();
        }, "FileLogger");

    // Registrazione di Application che dipende da ILogger "ConsoleLogger"
    dm.addTransient<Application>([](Scope& scope) {
        auto logger = scope.resolve<ILogger>("ConsoleLogger");
        return std::make_shared<Application>(logger);
        });

    // Registrazione di Application che dipende da ILogger "FileLogger"
    dm.addTransient<Application>([](Scope& scope) {
        auto logger = scope.resolve<ILogger>("FileLogger");
        return std::make_shared<Application>(logger);
        }, "FileApplication");

    // Creazione dello scope
    Scope scope = dm.createScope();

    // Risoluzione e utilizzo di Application con ConsoleLogger
    auto appConsole = scope.resolve<Application>();
    appConsole->run(); // Output: [Console] Application is running.

    // Risoluzione e utilizzo di Application con FileLogger
    auto appFile = scope.resolve<Application>("FileApplication");
    appFile->run(); // Output: [File] Application is running.

    // Verifica che le istanze Logger siano Singleton
    auto logger1 = scope.resolve<ILogger>("ConsoleLogger");
    auto logger2 = scope.resolve<ILogger>("ConsoleLogger");
    assert(logger1 == logger2);

    auto logger3 = scope.resolve<ILogger>("FileLogger");
    auto logger4 = scope.resolve<ILogger>("FileLogger");
    assert(logger3 == logger4);

    std::cout << "Esempio completo superato con successo!" << std::endl;

    return 0;
}
