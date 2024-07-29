#include <iostream>
#include <string>
#include <unordered_map>
#include <any>
#include <typeinfo>
#include <stdexcept>

template<typename T>
class Dictionary {
private:
    std::unordered_map<std::string, std::any> data;

public:
    // Add or update an item
    void add(const std::string& key, const T& value) {
        data[key] = value;
    }

    // Remove an item
    bool remove(const std::string& key) {
        return data.erase(key) > 0;
    }

    // Get value by key
    T get(const std::string& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            try {
                return std::any_cast<T>(it->second);
            }
            catch (const std::bad_any_cast&) {
                throw std::runtime_error("Type mismatch for key: " + key);
            }
        }
        throw std::out_of_range("Key not found: " + key);
    }

    // Check if key exists
    bool contains_key(const std::string& key) const {
        return data.find(key) != data.end();
    }

    // Get number of items
    size_t count() const {
        return data.size();
    }

    // Clear all items
    void clear() {
        data.clear();
    }

    // Get all keys
    std::vector<std::string> keys() const {
        std::vector<std::string> keys;
        for (const auto& pair : data) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    // Get all values
    std::vector<T> values() const {
        std::vector<T> values;
        for (const auto& pair : data) {
            try {
                values.push_back(std::any_cast<T>(pair.second));
            }
            catch (const std::bad_any_cast&) {
                throw std::runtime_error("Type mismatch for key: " + pair.first);
            }
        }
        return values;
    }

    // Operator overload for accessing elements
    T& operator[](const std::string& key) {
        if (!contains_key(key)) {
            data[key] = T();
        }
        return std::any_cast<T&>(data[key]);
    }
};

int main() {
    Dictionary<int> intDict;

    intDict.add("one", 1);
    intDict.add("two", 2);
    intDict["three"] = 3;

    std::cout << "Value of 'two': " << intDict.get("two") << std::endl;
    std::cout << "Contains 'four': " << (intDict.contains_key("four") ? "Yes" : "No") << std::endl;

    intDict.remove("one");
    std::cout << "Count after removal: " << intDict.count() << std::endl;

    std::cout << "All keys: ";
    for (const auto& key : intDict.keys()) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    std::cout << "All values: ";
    for (const auto& value : intDict.values()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}