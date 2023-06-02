#include <iostream>
#include <string>
#include <vector>

// Abstract Component
class FileSystemComponent {
public:
    virtual void displayInfo() const = 0;
};

// Leaf Component
class File : public FileSystemComponent {
private:
    std::string name;

public:
    File(const std::string& name) : name(name) {}

    void displayInfo() const override {
        std::cout << "File: " << name << std::endl;
    }
};

// Composite Component
class Directory : public FileSystemComponent {
private:
    std::string name;
    std::vector<FileSystemComponent*> components;

public:
    Directory(const std::string& name) : name(name) {}

    void addComponent(FileSystemComponent* component) {
        components.push_back(component);
    }

    void displayInfo() const override {
        std::cout << "Directory: " << name << std::endl;
        for (const auto& component : components) {
            component->displayInfo();
        }
    }
};

// Client
int main() {
    // Create file system components
    File* file1 = new File("file1.txt");
    File* file2 = new File("file2.txt");

    Directory* dir1 = new Directory("Directory 1");
    Directory* dir2 = new Directory("Directory 2");

    dir1->addComponent(file1);
    dir2->addComponent(file2);

    Directory* root = new Directory("Root");
    root->addComponent(dir1);
    root->addComponent(dir2);

    // Display file system hierarchy
    root->displayInfo();

    // Clean up
    delete root;

    return 0;
}
