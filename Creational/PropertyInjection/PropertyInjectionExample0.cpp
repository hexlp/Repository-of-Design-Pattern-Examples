class Logger {
private:
    std::string logLevel;

public:
    void setLogLevel(const std::string& level) {
        logLevel = level;
    }

    void log(const std::string& message) {
        std::cout << "[" << logLevel << "] " << message << std::endl;
    }
};

class Application {
private:
    Logger* logger; // Dependency

public:
    void setLogger(Logger* logger) {
        this->logger = logger;
    }

    void doSomething() {
        logger->log("Doing something...");
    }
};

int main() {
    Logger logger;
    logger.setLogLevel("INFO");

    Application app;
    app.setLogger(&logger);

    app.doSomething();

    return 0;
}
