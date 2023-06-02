#include <iostream>
#include <string>

// Dependency: Database Connection
class DatabaseConnection {
public:
    void connect() {
        std::cout << "Connected to the database." << std::endl;
        // Additional logic for establishing the database connection
    }

    void disconnect() {
        std::cout << "Disconnected from the database." << std::endl;
        // Additional logic for closing the database connection
    }

    // Other database-related methods...
};

// Dependent Class: UserRepository
class UserRepository {
private:
    DatabaseConnection& database;  // Dependency

public:
    // Constructor Injection
    UserRepository(DatabaseConnection& database) : database(database) {}

    void saveUser(const std::string& username) {
        database.connect();
        // Logic to save the user to the database
        std::cout << "User '" << username << "' saved to the database." << std::endl;
        database.disconnect();
    }
};

int main() {
    // Create the DatabaseConnection instance
    DatabaseConnection databaseConnection;

    // Create the UserRepository instance and inject the DatabaseConnection dependency
    UserRepository userRepository(databaseConnection);

    // Use the UserRepository to save a user
    userRepository.saveUser("JohnDoe");

    return 0;
}
