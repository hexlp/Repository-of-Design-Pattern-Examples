#include <iostream>
#include <vector>

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display() const = 0;
};

class File : public FileSystemComponent {
private:
    std::string name;

public:
    explicit File(const std::string& name) : name(name) {}

    void display() const override {
        std::cout << "File: " << name << std::endl;
    }

    ~File() {
        std::cout << "Deleting File: " << name << std::endl;
    }
};

class Directory : public FileSystemComponent {
private:
    std::string name;
    std::vector<FileSystemComponent*> children;

public:
    explicit Directory(const std::string& name) : name(name) {}

    void display() const override {
        std::cout << "Directory: " << name << std::endl;
        for (const auto& child : children) {
            child->display();
        }
    }

    void addComponent(FileSystemComponent* component) {
        children.push_back(component);
    }

    ~Directory() {
        std::cout << "Deleting Directory: " << name << std::endl;
        for (const auto& child : children) {
            delete child;
        }
    }
};

int main() {
    // Create files
    FileSystemComponent* file1 = new File("file1.txt");
    FileSystemComponent* file2 = new File("file2.txt");
    FileSystemComponent* file3 = new File("file3.txt");

    // Create directories
    Directory* dir1 = new Directory("Folder 1");
    Directory* dir2 = new Directory("Folder 2");
    Directory* root = new Directory("Root");

    // Compose file system hierarchy
    dir1->addComponent(file1);
    dir2->addComponent(file2);
    dir2->addComponent(file3);
    root->addComponent(dir1);
    root->addComponent(dir2);

    // Display the file system hierarchy
    root->display();

    // Clean up
    delete root; 

    return 0;
}
