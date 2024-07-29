#include <iostream>
#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <typeinfo>
#include <stdexcept>

template<typename T>
class Dictionary {
private:
    std::unordered_map<std::string, std::any> data;

public:
    // Constructor
    Dictionary() = default;

    // Copy constructor
    Dictionary(const Dictionary& other) : data(other.data) {}

    // Move constructor
    Dictionary(Dictionary&& other) noexcept : data(std::move(other.data)) {}

    // Copy assignment operator
    Dictionary& operator=(const Dictionary& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Move assignment operator
    Dictionary& operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

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
        keys.reserve(data.size());
        for (const auto& pair : data) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    // Get all values
    std::vector<T> values() const {
        std::vector<T> values;
        values.reserve(data.size());
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

    // Const operator overload for accessing elements
    const T& operator[](const std::string& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return std::any_cast<const T&>(it->second);
        }
        throw std::out_of_range("Key not found: " + key);
    }

    // Apply a function to all key-value pairs
    void for_each(const std::function<void(const std::string&, const T&)>& func) const {
        for (const auto& pair : data) {
            try {
                func(pair.first, std::any_cast<T>(pair.second));
            }
            catch (const std::bad_any_cast&) {
                throw std::runtime_error("Type mismatch for key: " + pair.first);
            }
        }
    }

    // Find keys that match a predicate
    std::vector<std::string> find_keys(const std::function<bool(const std::string&, const T&)>& predicate) const {
        std::vector<std::string> result;
        for (const auto& pair : data) {
            try {
                if (predicate(pair.first, std::any_cast<T>(pair.second))) {
                    result.push_back(pair.first);
                }
            }
            catch (const std::bad_any_cast&) {
                throw std::runtime_error("Type mismatch for key: " + pair.first);
            }
        }
        return result;
    }

    // Merge with another Dictionary
    void merge(const Dictionary& other) {
        for (const auto& pair : other.data) {
            data[pair.first] = pair.second;
        }
    }

    // Convert to string representation
    std::string to_string() const {
        std::ostringstream oss;
        oss << "{";
        bool first = true;
        for (const auto& pair : data) {
            if (!first) {
                oss << ", ";
            }
            oss << pair.first << ": ";
            try {
                oss << std::any_cast<T>(pair.second);
            }
            catch (const std::bad_any_cast&) {
                oss << "ERROR";
            }
            first = false;
        }
        oss << "}";
        return oss.str();
    }
};


// Example usage
int main() {

    Dictionary<int> dict;

    dict.add("one", 1);
    dict.add("two", 2);
    dict.add("three", 3);

    std::cout << "Dictionary size: " << dict.count() << std::endl;

    std::cout << "Value for key 'two': " << dict.get("two") << std::endl;

    std::cout << "Contains key 'four': " << (dict.contains_key("four") ? "true" : "false") << std::endl;

    std::cout << "All keys: ";
    for (const auto& key : dict.keys()) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    std::cout << "All values: ";
    for (const auto& value : dict.values()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    auto keys = dict.find_keys([](const std::string& key, const int& value) {
        return value % 2 == 0; // Find keys with even values 
        });

    std::cout << "Keys with even values: ";
    for (const auto& key : keys) {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    Dictionary<int> dict2;
    dict2.add("four", 4);
    dict2.add("five", 5);
    dict2.add("six", 6);
    dict.merge(dict2);

    std::cout << "Merged dictionary: " << dict.to_string() << std::endl;

    return 0;
}