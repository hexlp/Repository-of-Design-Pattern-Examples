#include <iostream>
#include <map>
#include <string>

class Logger {
private:
    std::string name;

public:
    Logger(const std::string& name)
        : name(name) {
    }

    void log(const std::string& message) {
        std::cout << "[" << name << "] " << message << std::endl;
    }
};

class LogManager {
private:
    static std::map<std::string, Logger*> loggers;

public:
    static Logger* getLogger(const std::string& name) {
        if (loggers.find(name) == loggers.end()) {
            // Logger does not exist for the given name, create a new one
            Logger* logger = new Logger(name);
            loggers[name] = logger;
        }

        return loggers[name];
    }
};

std::map<std::string, Logger*> LogManager::loggers;

int main() {
    // Get or create loggers
    Logger* logger1 = LogManager::getLogger("App");
    Logger* logger2 = LogManager::getLogger("Network");
    Logger* logger3 = LogManager::getLogger("App");

    // Log messages using the loggers
    logger1->log("Initializing application");
    logger2->log("Sending request to server");
    logger3->log("Application started");

    return 0;
}
