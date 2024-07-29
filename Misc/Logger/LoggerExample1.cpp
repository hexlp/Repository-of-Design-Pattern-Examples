#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <mutex>
#include <fstream>


// This is a cross-platform version of localtime function that is thread-safe and doesn't use static buffer
inline std::tm localtime_xp(const std::time_t* timer)
{
    std::tm bt;
#if defined(__unix__)
    localtime_r(timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(timer);
#endif
    return bt;
}

// Custom time stamp format with a given time
inline std::string time_stamp(const std::string& fmt, std::tm bt)
{
    char buf[64];
    return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}



// This macro converts an enum value to a string at compile time.
#define TO_STRING(x) #x

// This function extracts the part after the scope operator at runtime.
std::string GetEnumName(const std::string& enumString) {
    size_t pos = enumString.find_last_of(':');
    if (pos != std::string::npos) {
        return enumString.substr(pos + 1);
    }
    return enumString;
}

// This macro will convert an enum to a string.
#define ENUM_TO_STRING_CASE(x) case x: return TO_STRING(x);

// This macro will convert an enum name to a string.
#define ENUM_NAME_TO_STRING_CASE(x) case x: return GetEnumName(TO_STRING(x));


enum class LogLevel {
    Critical, Fatal, Panic, Error, Warning, Notice, Info, Debug, Trace, Verbose
};

std::string LogLevelToString(LogLevel level) {
    switch (level) {
        ENUM_NAME_TO_STRING_CASE(LogLevel::Critical);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Fatal);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Panic);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Error);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Warning);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Notice);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Info);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Debug);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Trace);
        ENUM_NAME_TO_STRING_CASE(LogLevel::Verbose);
    default: return "Unknown";
    }
}

//CRTP Singleton
template <typename T>
class Singleton {

protected:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }
};

class Logger : public Singleton<Logger> {

    LogLevel level = LogLevel::Info;
    bool enableFileOutput = false;
    std::string logFileName = "application.log";
    bool enableConsoleOutput = true;
    bool enableTimestamp = false;

    // Mutex to protect the log file and console output 
    std::mutex mutex;

public:
    // Log a message with a specific log level
    template<typename... Args>
    void log(LogLevel level, Args ...args) {

        std::lock_guard<std::mutex> lock(mutex);

        // Check if the log level is enabled
        if (level > this->level) {
            return;
        }

        // Create a log message
        std::ostringstream oss;

        if (enableTimestamp) {
            // Add timestamp to the log message
            std::time_t now = std::time(nullptr);
            std::string timeStampFormat = "%F %T"; // Default timestamp format
            oss << time_stamp(timeStampFormat, localtime_xp(&now)) << " ";
        }

        oss << LogLevelToString(level) << ": ";
        (oss << ... << args);  // Fold expression to handle all arguments

        // Output the log message to the console
        if (enableConsoleOutput) {
            std::cout << oss.str() << std::endl;
        }

        // Output the log message to the log file
        if (enableFileOutput) {
            // Open the log file in append mode
            std::ofstream logFile(logFileName, std::ios_base::app);
            if (logFile.is_open()) {
                logFile << oss.str() << std::endl;
            }
        }
    }

    // Set the log level
    void set_level(LogLevel level) {
        this->level = level;
    }

    // Get the current log level
    LogLevel get_level() const {
        return level;
    }

    // Enable or disable file output
    void set_enable_file_output(bool enable) {
        enableFileOutput = enable;
    }

    // Check if file output is enabled
    bool get_enable_file_output() const {
        return enableFileOutput;
    }

    // Set the log file name
    void set_log_file_name(const std::string& fileName) {
        logFileName = fileName;
    }

    // Get the log file name
    std::string get_log_file_name() const {
        return logFileName;
    }

    // Enable or disable console output
    void set_enable_console_output(bool enable) {
        enableConsoleOutput = enable;
    }

    // Check if console output is enabled
    bool get_enable_console_output() const {
        return enableConsoleOutput;
    }

    // Enable or disable timestamp
    void set_enable_timestamp(bool enable) {
        enableTimestamp = enable;
    }

    // Check if timestamp is enabled
    bool get_enable_timestamp() const {
        return enableTimestamp;
    }

};

#define LOG(level, ...) Logger::GetInstance().log(level, __VA_ARGS__)

#define LOG_CRITICAL(...) LOG(LogLevel::Critical, __VA_ARGS__)
#define LOG_FATAL(...) LOG(LogLevel::Fatal, __VA_ARGS__)
#define LOG_PANIC(...) LOG(LogLevel::Panic, __VA_ARGS__)
#define LOG_ERROR(...) LOG(LogLevel::Error, __VA_ARGS__)
#define LOG_WARNING(...) LOG(LogLevel::Warning, __VA_ARGS__)
#define LOG_NOTICE(...) LOG(LogLevel::Notice, __VA_ARGS__)
#define LOG_INFO(...) LOG(LogLevel::Info, __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LogLevel::Debug, __VA_ARGS__)
#define LOG_TRACE(...) LOG(LogLevel::Trace, __VA_ARGS__)
#define LOG_VERBOSE(...) LOG(LogLevel::Verbose, __VA_ARGS__)


int main() {
    int userId = 123;
    std::string userName = "Alice";
    double accountBalance = 456.78;

    LOG(LogLevel::Critical, "This is a critical message");
    LOG(LogLevel::Fatal, "This is a fatal message");
    LOG(LogLevel::Panic, "This is a panic message");
    LOG(LogLevel::Error, "This is an error message");
    LOG(LogLevel::Warning, "This is a warning message");
    LOG(LogLevel::Notice, "This is a notice message");
    LOG(LogLevel::Info, "This is an info message");
    LOG(LogLevel::Debug, "This is a debug message");
    LOG(LogLevel::Trace, "This is a trace message");
    LOG(LogLevel::Verbose, "This is a verbose message");

    LOG(LogLevel::Info, "User ", userId, " (", userName, ") has an account balance of $", accountBalance);

    return 0;
}

