#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include <mutex>
#include <set>
#include <iostream>


// Enum to define the lifetime of dependencies
enum class Lifetime {
    Singleton,
    Transient,
    Scoped
};

class Scope; // Forward declaration

class DependencyManager {
public:
    // Singleton accessor
    static DependencyManager& getInstance() {
        static DependencyManager instance;
        return instance;
    }

    // Methods to register dependencies
    template<typename T>
    void addSingleton(std::function<std::shared_ptr<T>(Scope&)> factory) {
        registerDependency<T>(factory, Lifetime::Singleton);
    }

    template<typename T>
    void addTransient(std::function<std::shared_ptr<T>(Scope&)> factory) {
        registerDependency<T>(factory, Lifetime::Transient);
    }

    template<typename T>
    void addScoped(std::function<std::shared_ptr<T>(Scope&)> factory) {
        registerDependency<T>(factory, Lifetime::Scoped);
    }

    template<typename T>
    void registerDependency(std::function<std::shared_ptr<T>(Scope&)> factory, Lifetime lifetime);


    // Method to create a scope
    Scope createScope();

    // Delete copy constructor and assignment operator
    DependencyManager(const DependencyManager&) = delete;
    DependencyManager& operator=(const DependencyManager&) = delete;

private:
    DependencyManager() = default;

    // Struct to hold factory info
    struct FactoryInfo {
        std::function<std::shared_ptr<void>(Scope&)> factory;
        Lifetime lifetime;
    };

    // Map from type_index to FactoryInfo
    std::unordered_map<std::type_index, FactoryInfo> factories;

    // Map for singleton instances
    std::unordered_map<std::type_index, std::shared_ptr<void>> singletonInstances;

    // Recursive mutex for thread safety and recursive locking
    std::recursive_mutex mutex;



    // For dependency cycle detection
    std::set<std::type_index> resolving;

    // Internal resolve method
    template<typename T>
    std::shared_ptr<T> resolve(Scope& scope);

    friend class Scope;
};

class Scope {
public:
    explicit Scope(DependencyManager& manager)
        : manager(manager) {}

    template<typename T>
    std::shared_ptr<T> resolve() {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        std::type_index typeIdx(typeid(T));

        // Check if instance is already in scopedInstances
        auto it = scopedInstances.find(typeIdx);
        if (it != scopedInstances.end()) {
            return std::static_pointer_cast<T>(it->second);
        }

        // Else, call manager's resolve
        return manager.resolve<T>(*this);
    }

private:
    DependencyManager& manager;

    // Map for scoped instances
    std::unordered_map<std::type_index, std::shared_ptr<void>> scopedInstances;

    // Recursive mutex for thread safety and recursive locking
    std::recursive_mutex mutex;

    // Store an instance
    template<typename T>
    void storeInstance(std::shared_ptr<T> instance) {
        std::lock_guard<std::recursive_mutex> lock(mutex);
        std::type_index typeIdx(typeid(T));
        scopedInstances[typeIdx] = instance;
    }

    friend class DependencyManager;
};

// Implementation of DependencyManager methods
inline Scope DependencyManager::createScope() {
    return Scope(*this);
}

template<typename T>
void DependencyManager::registerDependency(std::function<std::shared_ptr<T>(Scope&)> factory, Lifetime lifetime) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    std::type_index typeIdx(typeid(T));

    if (factories.find(typeIdx) != factories.end()) {
        throw std::runtime_error("Factory already registered for type: " + std::string(typeIdx.name()));
    }

    factories[typeIdx] = FactoryInfo{
        [factory](Scope& scope) -> std::shared_ptr<void> {
            return factory(scope);
        },
        lifetime
    };
}

template<typename T>
std::shared_ptr<T> DependencyManager::resolve(Scope& scope) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    std::type_index typeIdx(typeid(T));

    // Check for circular dependencies
    if (resolving.find(typeIdx) != resolving.end()) {
        throw std::runtime_error("Circular dependency detected for type: " + std::string(typeIdx.name()));
    }

    // Mark as resolving
    resolving.insert(typeIdx);

    std::shared_ptr<T> instance;

    // Handle singleton instances
    auto singletonIt = singletonInstances.find(typeIdx);
    if (singletonIt != singletonInstances.end()) {
        instance = std::static_pointer_cast<T>(singletonIt->second);
    }
    else {
        // Check if factory exists
        auto factoryIt = factories.find(typeIdx);
        if (factoryIt == factories.end()) {
            resolving.erase(typeIdx);
            throw std::runtime_error("No factory registered for type: " + std::string(typeIdx.name()));
        }

        // Create instance
        std::shared_ptr<void> instance_void = factoryIt->second.factory(scope);

        // Cast to correct type
        instance = std::static_pointer_cast<T>(instance_void);
        if (!instance) {
            resolving.erase(typeIdx);
            throw std::runtime_error("Failed to cast instance for type: " + std::string(typeIdx.name()));
        }

        // Store instance if needed
        if (factoryIt->second.lifetime == Lifetime::Singleton) {
            singletonInstances[typeIdx] = instance;
        }
        else if (factoryIt->second.lifetime == Lifetime::Scoped) {
            scope.storeInstance<T>(instance);
        }
    }

    // Remove from resolving
    resolving.erase(typeIdx);

    return instance;
}


//// Interface for IService
//class IService {
//public:
//    virtual void doSomething() = 0;
//    virtual ~IService() = default;
//};
//
//// Implementation of IService
//class ServiceImpl : public IService {
//public:
//    void doSomething() override {
//        std::cout << "ServiceImpl doing something!" << std::endl;
//    }
//};
//
//// Controller class that depends on IService
//class Controller {
//public:
//    explicit Controller(std::shared_ptr<IService> service)
//        : service(std::move(service)) {}
//
//    void process() {
//        service->doSomething();
//    }
//
//private:
//    std::shared_ptr<IService> service;
//};
//
//int main() {
//    // Get instance of DependencyManager
//    DependencyManager& dm = DependencyManager::getInstance();
//
//    // Register dependencies
//    dm.addSingleton<IService>([](Scope&) -> std::shared_ptr<IService> {
//        return std::make_shared<ServiceImpl>();
//        });
//
//    dm.addTransient<Controller>([](Scope& scope) -> std::shared_ptr<Controller> {
//        auto service = scope.resolve<IService>();
//        return std::make_shared<Controller>(service);
//        });
//
//    // Create a scope
//    Scope scope = dm.createScope();
//
//    // Resolve Controller
//    auto controller = scope.resolve<Controller>();
//
//    // Use controller
//    controller->process();
//
//    return 0;
//}
//
//
//
//
//
//
//


















// 1. Test della registrazione e risoluzione delle dipendenze con diverse durate di vita


#include <iostream>
#include <cassert>

// Interfacce per ogni tipo di durata di vita
class ISingletonExample {
public:
    virtual void doWork() = 0;
    virtual ~ISingletonExample() = default;
};

class ITransientExample {
public:
    virtual void doWork() = 0;
    virtual ~ITransientExample() = default;
};

class IScopedExample {
public:
    virtual void doWork() = 0;
    virtual ~IScopedExample() = default;
};

// Implementazioni per ciascuna interfaccia
class ExampleSingleton : public ISingletonExample {
public:
    void doWork() override {
        std::cout << "ExampleSingleton doing work." << std::endl;
    }
};

class ExampleTransient : public ITransientExample {
public:
    void doWork() override {
        std::cout << "ExampleTransient doing work." << std::endl;
    }
};

class ExampleScoped : public IScopedExample {
public:
    void doWork() override {
        std::cout << "ExampleScoped doing work." << std::endl;
    }
};

int DM_LifetimeTest() {
    DependencyManager& dm = DependencyManager::getInstance();

    // Registrazione delle dipendenze con tipi distinti
    dm.addSingleton<ISingletonExample>([](Scope&) {
        return std::make_shared<ExampleSingleton>();
        });

    dm.addTransient<ITransientExample>([](Scope&) {
        return std::make_shared<ExampleTransient>();
        });

    dm.addScoped<IScopedExample>([](Scope&) {
        return std::make_shared<ExampleScoped>();
        });

    // Creazione degli scope
    Scope scope1 = dm.createScope();
    Scope scope2 = dm.createScope();

    // Test per Singleton
    auto singleton1 = scope1.resolve<ISingletonExample>();
    auto singleton2 = scope2.resolve<ISingletonExample>();
    assert(singleton1 == singleton2); // Devono essere uguali

    // Test per Transient
    auto transient1 = scope1.resolve<ITransientExample>();
    auto transient2 = scope1.resolve<ITransientExample>();
    assert(transient1 != transient2); // Devono essere diversi

    // Test per Scoped
    auto scoped1_scope1 = scope1.resolve<IScopedExample>();
    auto scoped2_scope1 = scope1.resolve<IScopedExample>();
    auto scoped1_scope2 = scope2.resolve<IScopedExample>();
    assert(scoped1_scope1 == scoped2_scope1); // Devono essere uguali nello stesso scope
    assert(scoped1_scope1 != scoped1_scope2); // Devono essere diversi tra scope diversi

    std::cout << "Test delle durate di vita superato con successo!" << std::endl;

    return 0;
}


// 2. Test del rilevamento di dipendenze circolari



#include <iostream>
#include <exception>

class IA;
class IB;

class IA {
public:
    virtual void doA() = 0;
    virtual ~IA() = default;
};

class IB {
public:
    virtual void doB() = 0;
    virtual ~IB() = default;
};

class AImpl : public IA {
private:
    std::shared_ptr<IB> b;
public:
    AImpl(std::shared_ptr<IB> b) : b(std::move(b)) {}
    void doA() override {
        std::cout << "AImpl doing A." << std::endl;
        b->doB();
    }
};

class BImpl : public IB {
private:
    std::shared_ptr<IA> a;
public:
    BImpl(std::shared_ptr<IA> a) : a(std::move(a)) {}
    void doB() override {
        std::cout << "BImpl doing B." << std::endl;
        a->doA();
    }
};

int DM_CircularDependencyTest() {
    DependencyManager& dm = DependencyManager::getInstance();

    dm.addTransient<IA>([](Scope& scope) {
        auto b = scope.resolve<IB>();
        return std::make_shared<AImpl>(b);
        });

    dm.addTransient<IB>([](Scope& scope) {
        auto a = scope.resolve<IA>();
        return std::make_shared<BImpl>(a);
        });

    Scope scope = dm.createScope();

    try {
        auto a = scope.resolve<IA>();
    }
    catch (const std::runtime_error& e) {
        std::cout << "Dipendenza circolare rilevata correttamente: " << e.what() << std::endl;
        return 0;
    }

    std::cout << "Errore: dipendenza circolare non rilevata." << std::endl;
    return 1;
}


// 3. Test della thread safety durante la risoluzione delle dipendenze

#include <iostream>
#include <thread>
#include <vector>

class ICounter {
public:
    virtual void increment() = 0;
    virtual int getValue() const = 0;
    virtual ~ICounter() = default;
};

class Counter : public ICounter {
private:
    int value = 0;
    std::mutex mtx;
public:
    void increment() override {
        std::lock_guard<std::mutex> lock(mtx);
        ++value;
    }
    int getValue() const override {
        return value;
    }
};

int DM_ThreadSafetyTest() {
    DependencyManager& dm = DependencyManager::getInstance();

    dm.addSingleton<ICounter>([](Scope&) {
        return std::make_shared<Counter>();
        });

    Scope scope = dm.createScope();

    const int numThreads = 10;
    const int incrementsPerThread = 1000;
    std::vector<std::thread> threads;

    auto counter = scope.resolve<ICounter>();

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&scope]() {
            auto counter = scope.resolve<ICounter>();
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter->increment();
            }
            });
    }

    for (auto& t : threads) {
        t.join();
    }

    int expectedValue = numThreads * incrementsPerThread;
    int actualValue = counter->getValue();

    assert(actualValue == expectedValue);

    std::cout << "Valore atteso: " << expectedValue << ", Valore attuale: " << actualValue << std::endl;
    std::cout << "Test di thread safety superato con successo!" << std::endl;

    return 0;
}


// 4. Test della gestione delle eccezioni quando una dipendenza non è registrata


#include <iostream>

class INonRegistered {
public:
    virtual void doSomething() = 0;
    virtual ~INonRegistered() = default;
};

int DM_UnregisteredDependencyTest() {
    DependencyManager& dm = DependencyManager::getInstance();

    Scope scope = dm.createScope();

    try {
        auto instance = scope.resolve<INonRegistered>();
    }
    catch (const std::runtime_error& e) {
        std::cout << "Eccezione correttamente lanciata per dipendenza non registrata: " << e.what() << std::endl;
        return 0;
    }

    std::cout << "Errore: nessuna eccezione lanciata per dipendenza non registrata." << std::endl;
    return 1;
}



//  5. Test che verifica la corretta gestione delle istanze (controllo dei costruttori e distruttori)

#include <iostream>
#include <atomic>

std::atomic<int> singletonCount{ 0 };
std::atomic<int> transientCount{ 0 };
std::atomic<int> scopedCount{ 0 };

class SingletonClass {
public:
    SingletonClass() { ++singletonCount; }
    ~SingletonClass() { --singletonCount; }
};

class TransientClass {
public:
    TransientClass() { ++transientCount; }
    ~TransientClass() { --transientCount; }
};

class ScopedClass {
public:
    ScopedClass() { ++scopedCount; }
    ~ScopedClass() { --scopedCount; }
};

int DM_InstanceManagementTest() {
    DependencyManager& dm = DependencyManager::getInstance();

    dm.addSingleton<SingletonClass>([](Scope&) {
        return std::make_shared<SingletonClass>();
        });

    dm.addTransient<TransientClass>([](Scope&) {
        return std::make_shared<TransientClass>();
        });

    dm.addScoped<ScopedClass>([](Scope&) {
        return std::make_shared<ScopedClass>();
        });

    {
        Scope scope1 = dm.createScope();
        {
            auto singleton1 = scope1.resolve<SingletonClass>();
            auto transient1 = scope1.resolve<TransientClass>();
            auto scoped1 = scope1.resolve<ScopedClass>();
            assert(singletonCount == 1);
            assert(transientCount == 1);
            assert(scopedCount == 1);
        }
        // Dopo questo blocco, transient1 e scoped1 vengono distrutti
        assert(singletonCount == 1);
        assert(transientCount == 0);
        assert(scopedCount == 1);
    }
    // Dopo questo blocco, scoped1 viene distrutto
    assert(singletonCount == 1);
    assert(scopedCount == 0);

    // Singleton rimane finché il programma non termina
    std::cout << "Test di gestione delle istanze superato con successo!" << std::endl;

    return 0;
}



// 6. Test del riutilizzo degli scope

#include <iostream>
#include <cassert>

class ScopedResource {
public:
    int value;
    ScopedResource(int v) : value(v) {}
};

int  DM_ScopeReuseTest() {
    DependencyManager& dm = DependencyManager::getInstance();

    int creationCounter = 0;

    dm.addScoped<ScopedResource>([&creationCounter](Scope&) {
        ++creationCounter;
        return std::make_shared<ScopedResource>(creationCounter);
        });

    Scope scope1 = dm.createScope();
    auto res1_scope1 = scope1.resolve<ScopedResource>();
    auto res2_scope1 = scope1.resolve<ScopedResource>();
    assert(res1_scope1 == res2_scope1);
    assert(res1_scope1->value == 1);

    Scope scope2 = dm.createScope();
    auto res1_scope2 = scope2.resolve<ScopedResource>();
    assert(res1_scope2 != res1_scope1);
    assert(res1_scope2->value == 2);

    std::cout << "Test del riutilizzo degli scope superato con successo!" << std::endl;

    return 0;
}



// 7. Test delle dipendenze annidate

#include <iostream>
#include <cassert>

class IService {
public:
    virtual void perform() = 0;
    virtual ~IService() = default;
};

class Service : public IService {
public:
    void perform() override {
        std::cout << "Service performing action." << std::endl;
    }
};

class IController {
public:
    virtual void execute() = 0;
    virtual ~IController() = default;
};

class Controller : public IController {
private:
    std::shared_ptr<IService> service;
public:
    Controller(std::shared_ptr<IService> svc) : service(std::move(svc)) {}
    void execute() override {
        std::cout << "Controller executing." << std::endl;
        service->perform();
    }
};

int DM_NestedDependenciesTest() {
    DependencyManager& dm = DependencyManager::getInstance();

    dm.addSingleton<IService>([](Scope&) {
        return std::make_shared<Service>();
        });

    dm.addTransient<IController>([](Scope& scope) {
        auto service = scope.resolve<IService>();
        return std::make_shared<Controller>(service);
        });

    Scope scope = dm.createScope();

    auto controller = scope.resolve<IController>();
    controller->execute();

    std::cout << "Test delle dipendenze annidate superato con successo!" << std::endl;

    return 0;
}



// 8. Test delle dipendenze multiple dello stesso tipo con durate di vita diverse ( NON SUPPORTATO )



int main() {

    int result = 0;

    result += DM_LifetimeTest();
    result += DM_CircularDependencyTest();
    result += DM_ThreadSafetyTest();
    result += DM_UnregisteredDependencyTest();
    result += DM_InstanceManagementTest();
    result += DM_ScopeReuseTest();
    result += DM_NestedDependenciesTest();

    return result;
}