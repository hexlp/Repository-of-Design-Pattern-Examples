#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>

// Abstract base class for the command expression
class CommandExpression {
public:
    virtual void execute(const std::vector<std::string>& arguments) const = 0;
};

// Concrete implementation of a command expression
class SetGodModeExpression : public CommandExpression {
public:
    void execute(const std::vector<std::string>& arguments) const override {
        if (arguments.size() > 0) {
            std::string username = arguments[0];
            // Implement the logic to enable god mode for the specified user
            std::cout << "God mode enabled for user: " << username << std::endl;
        }
        else {
            std::cout << "Invalid command: set_godmode" << std::endl;
        }
    }
};

class SetRunningSpeedExpression : public CommandExpression {
public:
    void execute(const std::vector<std::string>& arguments) const override {
        if (arguments.size() > 0) {
            float speed = std::stof(arguments[0]);
            // Implement the logic to set the running speed to the specified value
            std::cout << "Running speed set to: " << speed << std::endl;
        }
        else {
            std::cout << "Invalid command: set_runningspeed" << std::endl;
        }
    }
};

class SetPasswordExpression : public CommandExpression {
public:
    void execute(const std::vector<std::string>& arguments) const override {
        if (arguments.size() >= 2) {
            std::string currentPassword = arguments[0];
            std::string newPassword = arguments[1];
            // Implement the logic to set the new password using the current password
            std::cout << "Password changed successfully. New password: " << newPassword << std::endl;
        }
        else {
            std::cout << "Invalid command: set_password" << std::endl;
        }
    }
};

// ... Other command expressions for different commands

class CommandParser {
private:
    std::unordered_map<std::string, CommandExpression*> commandMap;

public:
    void registerCommand(const std::string& commandName, CommandExpression* expression) {
        commandMap[commandName] = expression;
    }

    void parseCommand(const std::string& command) {
        std::istringstream iss(command);
        std::string commandName;
        iss >> commandName;

        auto it = commandMap.find(commandName);
        if (it != commandMap.end()) {
            CommandExpression* expression = it->second;

            std::vector<std::string> arguments;
            std::string argument;
            while (iss >> argument) {
                arguments.push_back(argument);
            }

            expression->execute(arguments);
        }
        else {
            std::cout << "Invalid command: " << commandName << std::endl;
        }
    }

    void cleanup() {
        for (auto& pair : commandMap) {
            delete pair.second;          
        }
        commandMap.clear();
    }

    ~CommandParser() {
        cleanup();
    }


};

int main() {
    CommandParser commandParser;

    // Register commands and their corresponding expressions
    commandParser.registerCommand("set_godmode", new SetGodModeExpression());
    commandParser.registerCommand("set_runningspeed", new SetRunningSpeedExpression());
    commandParser.registerCommand("set_password", new SetPasswordExpression());
    // ... Register other commands and their expressions

    // Parse commands
    commandParser.parseCommand("set_godmode username");
    commandParser.parseCommand("set_runningspeed 3.5");
    commandParser.parseCommand("set_password currentpwd newpwd");
    // ... Parse other commands

    // Clean up
    commandParser.cleanup();

    return 0;
}
