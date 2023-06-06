#include <iostream>
#include <string>
#include <vector>

// Memento
class DocumentMemento {
private:
    std::string content;

public:
    DocumentMemento(const std::string& content) : content(content) {}

    std::string getContent() const {
        return content;
    }
};

// Originator
class Document {
private:
    std::string content;

public:
    void setContent(const std::string& newContent) {
        content = newContent;
    }

    std::string getContent() const {
        return content;
    }

    DocumentMemento save() {
        return DocumentMemento(content);
    }

    void restore(const DocumentMemento& memento) {
        content = memento.getContent();
    }
};

// Caretaker
class History {
private:
    std::vector<DocumentMemento> mementos;

public:
    void addMemento(const DocumentMemento& memento) {
        mementos.push_back(memento);
    }

    DocumentMemento getMemento(int index) const {
        return mementos[index];
    }
};

int main() {
    Document document;
    History history;

    // Editing the document
    document.setContent("This is the initial content of the document.");
    std::cout << "Current content: " << document.getContent() << std::endl;

    // Save the current state
    history.addMemento(document.save());

    // Modify the document
    document.setContent("Modified content of the document.");
    std::cout << "Current content: " << document.getContent() << std::endl;

    // Save the modified state
    history.addMemento(document.save());

    // Restore the initial state
    document.restore(history.getMemento(0));
    std::cout << "Restored content: " << document.getContent() << std::endl;

    return 0;
}
