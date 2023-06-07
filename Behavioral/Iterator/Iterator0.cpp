#include <iostream>
#include <vector>

// Iterator interface
class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual int next() = 0;
};

// Concrete Iterator implementation for a vector
class VectorIterator : public Iterator {
private:
    const std::vector<int>& collection;
    size_t currentIndex;

public:
    VectorIterator(const std::vector<int>& collection)
        : collection(collection), currentIndex(0) {}

    bool hasNext() const override {
        return currentIndex < collection.size();
    }

    int next() override {
        return collection[currentIndex++];
    }
};

// Collection class that provides an Iterator
class Collection {
private:
    std::vector<int> elements;

public:
    void addElement(int element) {
        elements.push_back(element);
    }

    Iterator* createIterator() const {
        return new VectorIterator(elements);
    }
};

int main() {
    Collection collection;
    collection.addElement(1);
    collection.addElement(2);
    collection.addElement(3);
    collection.addElement(4);

    Iterator* iterator = collection.createIterator();
    while (iterator->hasNext()) {
        int element = iterator->next();
        std::cout << element << " ";
    }
    std::cout << std::endl;

    delete iterator;

    return 0;
}
