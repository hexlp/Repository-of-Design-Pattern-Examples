#include <iostream>
#include <string>
#include <vector>

class EditorMemento {
public:
    explicit EditorMemento(const std::string& content) : content(content) {}

    std::string getContent() const {
        return content;
    }

private:
    std::string content;
};

class Editor {
public:
    Editor() : content(""), currentIndex(-1) {
        save(); // Save initial state
    }

    void type(const std::string& words) {
        content += words;
    }

    std::string getContent() const {
        return content;
    }

    void save() {
        mementos.push_back(EditorMemento(content));
        currentIndex = mementos.size() - 1;
    }

    void undo() {
        if (currentIndex > 0) {
            currentIndex--;
            content = mementos[currentIndex].getContent();
        }
    }

    void redo() {
        if (currentIndex < mementos.size() - 1) {
            currentIndex++;
            content = mementos[currentIndex].getContent();
        }
    }

private:
    std::string content;
    std::vector<EditorMemento> mementos;
    int currentIndex;
};

int main() {
    Editor editor;

    editor.type("Hello, ");
    editor.save();
    editor.type("world!");
    editor.save();

    std::cout << "Current content: " << editor.getContent() << std::endl;

    editor.undo();
    std::cout << "Undo 1: " << editor.getContent() << std::endl;

    editor.undo();
    std::cout << "Undo 2: " << editor.getContent() << std::endl;

    editor.redo();
    std::cout << "Redo 1: " << editor.getContent() << std::endl;

    editor.redo();
    std::cout << "Redo 2: " << editor.getContent() << std::endl;

    return 0;
}
