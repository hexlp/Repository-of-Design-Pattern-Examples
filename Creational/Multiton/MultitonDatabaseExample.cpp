

#include <iostream>
#include <map>
#include <string>

class DatabaseConnection {
private:
    std::string connectionString;

public:
    DatabaseConnection(const std::string& connectionString)
        : connectionString(connectionString) {
    }

    void connect() {
        std::cout << "Connected to database: " << connectionString << std::endl;
        // Connect to the database
    }

    void disconnect() {
        std::cout << "Disconnected from database: " << connectionString << std::endl;
        // Disconnect from the database
    }
};

class DatabaseConnectionManager {
private:
    static std::map<std::string, DatabaseConnection*> connections;

public:
    static DatabaseConnection* getInstance(const std::string& key) {
        if (connections.find(key) == connections.end()) {
            // Connection does not exist for the given key, create a new one
            DatabaseConnection* connection = new DatabaseConnection(key);
            connections[key] = connection;
        }

        return connections[key];
    }
};

std::map<std::string, DatabaseConnection*> DatabaseConnectionManager::connections;

int main() {
    // Get or create database connections
    DatabaseConnection* connection1 = DatabaseConnectionManager::getInstance("DB1");
    DatabaseConnection* connection2 = DatabaseConnectionManager::getInstance("DB2");
    DatabaseConnection* connection3 = DatabaseConnectionManager::getInstance("DB1");

    // Use the database connections
    connection1->connect();
    connection2->connect();
    connection3->connect();

    // Disconnect from the databases
    connection1->disconnect();
    connection2->disconnect();
    connection3->disconnect();

    return 0;
}