#include <iostream>
#include <string>

// Subject interface
class File {
public:
    virtual void open() = 0;
    virtual void close() = 0;
};

// Real subject
class TextFile : public File {
private:
    std::string filename;

public:
    TextFile(const std::string& filename) : filename(filename) {}

    void open() override {
        std::cout << "Opening text file: " << filename << std::endl;
        // Perform actual file opening operations
    }

    void close() override {
        std::cout << "Closing text file: " << filename << std::endl;
        // Perform actual file closing operations
    }
};

// Proxy class
class ProtectedFile : public File {
private:
    File* file;

public:
    ProtectedFile(const std::string& filename) {
        // Only allow access to files with ".txt" extension
        if (filename.substr(filename.length() - 4) == ".txt") {
            file = new TextFile(filename);
        }
        else {
            file = nullptr;
            std::cout << "Access denied! Only text files are allowed." << std::endl;
        }
    }

    void open() override {
        if (file != nullptr) {
            file->open();
        }
    }

    void close() override {
        if (file != nullptr) {
            file->close();
        }
    }
};

int main() {
    // Creating a protected file object
    File* file = new ProtectedFile("document.txt");

    // Opening and closing the file
    file->open();
    file->close();

    delete file;

    // Trying to access a non-text file
    File* invalidFile = new ProtectedFile("image.png");
    invalidFile->open();
    invalidFile->close();

    delete invalidFile;

    return 0;
}
