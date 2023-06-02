#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

class DatabaseConnection {
public:
    void query(const std::string& sql) {
        std::cout << "Executing SQL query: " << sql << std::endl;
    }
};

class DatabaseConnectionPool {
private:
    std::vector<std::shared_ptr<DatabaseConnection>> connections;
    std::mutex mutex;

public:
    DatabaseConnectionPool(int size) {
        initializePool(size);
    }

    std::shared_ptr<DatabaseConnection> acquireConnection() {
        std::unique_lock<std::mutex> lock(mutex);
        if (connections.empty()) {
            std::cout << "No available connections. Creating a new one." << std::endl;
            return std::make_shared<DatabaseConnection>();
        } else {
            std::cout << "Reusing an existing connection." << std::endl;
            auto connection = connections.back();
            connections.pop_back();
            return connection;
        }
    }

    void releaseConnection(std::shared_ptr<DatabaseConnection> connection) {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << "Returning the connection to the pool." << std::endl;
        connections.push_back(connection);
    }

    void initializePool(int size) {
        std::unique_lock<std::mutex> lock(mutex);
        std::cout << "Initializing the connection pool." << std::endl;
        for (int i = 0; i < size; ++i) {
            connections.push_back(std::make_shared<DatabaseConnection>());
        }
    }
};

int main() {
    DatabaseConnectionPool connectionPool(5);

    // Simulating multiple client requests
    for (int i = 0; i < 10; ++i) {
        // Acquire a connection from the pool
        auto connection = connectionPool.acquireConnection();

        // Perform database operations
        connection->query("SELECT * FROM customers");

        // Release the connection back to the pool
        connectionPool.releaseConnection(connection);
    }

    return 0;
}


/*

Consider a web server that needs to handle multiple client requests concurrently. 
Each client request requires a database connection to fetch data. Creating and closing
a database connection for each request can be time-consuming and resource-intensive. 
Instead, we can use the Object Pool Pattern to manage a pool of pre-initialized database connections.


In this example, we have a DatabaseConnection class representing a database connection that can execute SQL queries.
The DatabaseConnectionPool class represents the object pool that manages a collection of pre-initialized database connections.

The DatabaseConnectionPool class maintains a vector of database connections and uses a mutex to synchronize access to the pool.
The acquireConnection() method is used to acquire a connection from the pool. If no connections are available, a new connection is created. 
If connections are available, an existing connection is reused from the pool. The releaseConnection() method is used to return a connection back to the pool for reuse.


In the main function, we simulate multiple client requests by acquiring a connection from the pool, executing a database query, and then releasing the connection back 
to the pool. By reusing database connections from the pool, we can avoid the overhead of creating and closing connections for each client request, leading to improved 
performance and efficient resource utilization.

In a real-world scenario, a web server could use the Object Pool Pattern to manage various types of resources, such as database connections, network sockets, 
threads, or any resource-intensive objects that require efficient reuse. By maintaining a pool of initialized objects, the web server can handle concurrent 
requests more effectively and ensure optimal utilization of system resources.

*/