/*


The Dependency Injection pattern is a software design pattern that allows the decoupling 
of dependencies between classes. It enables the inversion of control by externalizing the
creation and management of object dependencies. In other words, instead of objects creating
and managing their dependencies directly, they are provided with dependencies from an external source.

The main idea behind the Dependency Injection pattern is to promote loose coupling and improve
code reusability and testability. It makes classes more modular and flexible by removing the
responsibility of creating and managing dependencies, and instead, injecting them from the outside.

There are three common types of dependency injection:

Constructor Injection: Dependencies are provided through a class's constructor. 
The class declares its dependencies as parameters in the constructor, and an external
entity is responsible for creating the object and passing in the dependencies.

Setter Injection: Dependencies are provided through setter methods or properties of a class.
The class exposes setter methods or properties for each dependency it requires, and an 
external entity sets these dependencies after creating the object.

Interface Injection: Dependencies are provided through an interface. 
The class implements an interface that defines methods to inject the required dependencies.
The external entity, usually a framework or container, injects the dependencies by invoking the methods defined in the interface.

*/



#include <iostream>

// Dependency: Logger
class Logger {
public:
    void log(const std::string& message) {
        std::cout << "Logging: " << message << std::endl;
    }
};

// Dependent Class: UserService
class UserService {
private:
    Logger& logger;  // Dependency

public:
    // Constructor Injection
    UserService(Logger& logger) : logger(logger) {}

    void createUser(const std::string& username) {
        logger.log("Creating user: " + username);
        // Additional logic for creating a user
    }
};

int main() {
    // Create the Logger instance
    Logger logger;

    // Create the UserService instance and inject the Logger dependency
    UserService userService(logger);

    // Use the UserService
    userService.createUser("JohnDoe");

    return 0;
}
