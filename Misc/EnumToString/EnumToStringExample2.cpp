#include <string>
#include <iostream>

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
#define ENUM_NAME_TO_STRING(x) case x: return GetEnumName(TO_STRING(x));


enum class LogLevel {
    Critical, Fatal, Panic, Error, Warning, Notice, Info, Debug, Trace, Verbose
};

std::string LogLevelToString(LogLevel level) {
    switch (level) {
        ENUM_TO_STRING_CASE(LogLevel::Critical);
        ENUM_TO_STRING_CASE(LogLevel::Fatal);
        ENUM_TO_STRING_CASE(LogLevel::Panic);
        ENUM_TO_STRING_CASE(LogLevel::Error);
        ENUM_TO_STRING_CASE(LogLevel::Warning);
        ENUM_TO_STRING_CASE(LogLevel::Notice);
        ENUM_TO_STRING_CASE(LogLevel::Info);
        ENUM_TO_STRING_CASE(LogLevel::Debug);
        ENUM_TO_STRING_CASE(LogLevel::Trace);
        ENUM_TO_STRING_CASE(LogLevel::Verbose);
    default: return "Unknown";
    }
}

int main() {
    LogLevel level = LogLevel::Debug;
    std::cout << "Log level: " << LogLevelToString(level) << std::endl;
    std::cout << "Log level name: " << GetEnumName(TO_STRING(LogLevel::Debug)) << std::endl;
    return 0;
}


