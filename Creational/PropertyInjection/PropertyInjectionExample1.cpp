/*

The Property Injection Pattern is a design pattern used in object-oriented programming to 
inject dependencies into an object through its properties or setter methods. It is a form of 
dependency injection where dependencies are provided to an object after its creation,
typically through configuration or external sources.

In the Property Injection Pattern, an object declares properties or setter methods that 
represent its dependencies. The dependencies are then set or injected into the object from 
an external source, such as a configuration file, dependency container, or manually by the application code.

The Property Injection Pattern allows for loose coupling between objects and their
dependencies. It provides flexibility in configuring and changing dependencies without
modifying the object's code. However, it also comes with the responsibility of ensuring that 
the dependencies are properly set before they are used to avoid null references or unexpected behavior.

*/



#include <iostream>
#include <string>

class DatabaseConnection {
private:
    std::string connectionString;

public:
    void setConnectionString(const std::string& connectionStr) {
        connectionString = connectionStr;
    }

    void connect() {
        std::cout << "Connecting to database: " << connectionString << std::endl;
        // Logic to establish a database connection
    }
};

class UserRepository {
private:
    DatabaseConnection* databaseConnection; // Dependency

public:
    void setDatabaseConnection(DatabaseConnection* connection) {
        databaseConnection = connection;
    }

    void saveUser(const std::string& username) {
        databaseConnection->connect();
        // Logic to save user to the database
        std::cout << "Saving user: " << username << std::endl;
    }
};

int main() {
    DatabaseConnection dbConnection;
    dbConnection.setConnectionString("mysql://localhost:3306/mydatabase");

    UserRepository userRepository;
    userRepository.setDatabaseConnection(&dbConnection);

    userRepository.saveUser("tommy_gunn");

    return 0;
}

