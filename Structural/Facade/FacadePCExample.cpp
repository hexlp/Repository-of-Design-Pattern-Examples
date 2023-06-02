
#include <iostream>
#include <string>

// Subsystem 1: CPU
class CPU {
public:
    void freeze() {
        std::cout << "CPU: Freezing system." << std::endl;
    }

    void jump(const std::string& address) {
        std::cout << "CPU: Jumping to address " << address << std::endl;
    }

    void execute() {
        std::cout << "CPU: Executing instructions." << std::endl;
    }
};

// Subsystem 2: Memory
class Memory {
public:
    void load(const std::string& address, const std::string& data) {
        std::cout << "Memory: Loading data " << data << " at address " << address << std::endl;
    }
};

// Subsystem 3: Hard Drive
class HardDrive {
public:
    std::string read(const std::string& sector, const int& size) {
        std::cout << "Hard Drive: Reading " << size << " bytes from sector " << sector << std::endl;
        return "Data from sector " + sector;
    }
};

// Facade
class Computer {
private:
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;

public:
    void start() {
        std::cout << "Computer: Starting the computer." << std::endl;
        cpu.freeze();
        memory.load("BOOT_ADDRESS", "BOOT_DATA");
        cpu.jump("BOOT_ADDRESS");
        cpu.execute();
    }

    void shutdown() {
        std::cout << "Computer: Shutting down the computer." << std::endl;
        // Additional cleanup steps go here
    }

    std::string readDataFromHardDrive(const std::string& sector, const int& size) {
        return hardDrive.read(sector, size);
    }
};

int main() {
    // Client code interacts with the computer using the Facade
    Computer computer;
    computer.start();

    std::string data = computer.readDataFromHardDrive("SECTOR_1", 1024);
    std::cout << "Client: Read data from hard drive: " << data << std::endl;

    computer.shutdown();

    return 0;
}


