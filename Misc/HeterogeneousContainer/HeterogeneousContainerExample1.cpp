#include <any>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <string>
#include <iostream>

// Tag structs for specialization
struct Shrinkable {};
struct NonShrinkable {};

// We define two exceptions for the container
class ContainerException : public std::runtime_error {
public:
    explicit ContainerException(const std::string& message) : std::runtime_error(message) {}
};

class InvalidIndexException : public ContainerException {
public:
    explicit InvalidIndexException(size_t index)
        : ContainerException("Invalid index: " + std::to_string(index)) {}
};

class TypeMismatchException : public ContainerException {
public:
    explicit TypeMismatchException(const std::string& expected, const std::string& actual)
        : ContainerException("Type mismatch. Expected: " + expected + ", Actual: " + actual) {}
};

// Interface for objects that can return their size
struct ISizedObject {
    virtual size_t size() const = 0;
    virtual ~ISizedObject() = default;
};

// Implementation of the interface for objects of type T
template<typename T>
class SizedObject : public ISizedObject {
private:
    std::unique_ptr<T> value;
    size_t object_size;

public:
    template<typename U>
    SizedObject(U&& val) : value(std::make_unique<T>(std::forward<U>(val))),
        object_size(sizeof(T) + sizeof(std::unique_ptr<T>)) {}

    const T& get() const { return *value; }
    T& get() { return *value; }
    size_t size() const override { return object_size; }
};

// The main container class
template<typename ShrinkPolicy>
class HeterogeneousContainer {
private:
    std::vector<std::any> data;
    std::unordered_map<std::type_index, std::vector<size_t>> type_indices;
    std::vector<size_t> free_indices;

public:

    template<typename T>
    size_t insert(T&& value) {
        size_t index;
        std::shared_ptr<ISizedObject> sized_obj = std::make_shared<SizedObject<std::decay_t<T>>>(std::forward<T>(value));
        if (!free_indices.empty()) {
            index = free_indices.back();
            free_indices.pop_back();
            data[index] = sized_obj;
        }
        else {
            index = data.size();
            data.push_back(sized_obj);
        }
        type_indices[std::type_index(typeid(T))].push_back(index);
        return index;
    }

    template<typename T>
    T& get(size_t index) {
        if (index >= data.size()) {
            throw InvalidIndexException(index);
        }
        auto ptr = std::any_cast<std::shared_ptr<ISizedObject>>(&data[index]);
        if (!ptr) {
            throw TypeMismatchException(typeid(T).name(), data[index].type().name());
        }
        auto derived_ptr = std::dynamic_pointer_cast<SizedObject<T>>(*ptr);
        if (!derived_ptr) {
            throw TypeMismatchException(typeid(T).name(), typeid(*ptr->get()).name());
        }
        return derived_ptr->get();
    }

    template<typename T>
    const T& get(size_t index) const {
        return const_cast<HeterogeneousContainer*>(this)->get<T>(index);
    }

    size_t size_bytes() const {
        size_t total_size = sizeof(*this);

        // Data vector
        total_size += sizeof(std::vector<std::any>) + (data.capacity() * sizeof(std::any));

        // Type indices map
        total_size += sizeof(std::unordered_map<std::type_index, std::vector<size_t>>);
        for (const auto& [type, indices] : type_indices) {
            total_size += sizeof(std::type_index) + sizeof(std::vector<size_t>) + (indices.capacity() * sizeof(size_t));
        }

        // Free indices vector
        total_size += sizeof(std::vector<size_t>) + (free_indices.capacity() * sizeof(size_t));

        // Actual stored objects
        for (const auto& item : data) {
            if (item.has_value()) {
                auto sized_obj = std::any_cast<std::shared_ptr<ISizedObject>>(item);
                total_size += sized_obj->size() + sizeof(std::shared_ptr<ISizedObject>);
            }
        }

        return total_size;
    }

    void remove(size_t index) {
        if (index >= data.size() || !data[index].has_value()) {
            throw InvalidIndexException(index);
        }

        const std::type_info& type = data[index].type();
        auto type_index = std::type_index(type);

        // Clear the data at the index
        data[index].reset();

        // Remove the index from type_indices
        auto& indices = type_indices[type_index];
        indices.erase(std::remove(indices.begin(), indices.end(), index), indices.end());

        // If the type no longer has any indices, remove it from type_indices
        if (indices.empty()) {
            type_indices.erase(type_index);
        }

        // Add to free_indices
        free_indices.push_back(index);

        shrink(ShrinkPolicy{});
    }

private:

    void shrink(NonShrinkable) {
        // Do nothing for non-shrinkable container
    }

    void shrink(Shrinkable) {
        if (free_indices.empty()) return;

        // Always compact if there are free indices
        compact();

        // Shrink to fit the data vector
        data.shrink_to_fit();

        // Shrink to fit all vectors in type_indices
        for (auto& [_, indices] : type_indices) {
            indices.shrink_to_fit();
        }

        // Shrink to fit free_indices
        free_indices.shrink_to_fit();
    }


    void compact() {
        size_t write = 0;
        for (size_t read = 0; read < data.size(); ++read) {
            if (data[read].has_value()) {
                if (write != read) {
                    data[write] = std::move(data[read]);
                    // Update type_indices
                    for (auto& [_, indices] : type_indices) {
                        std::replace(indices.begin(), indices.end(), read, write);
                    }
                }
                ++write;
            }
        }
        data.resize(write);
        free_indices.clear();
    }

};

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    try {

        HeterogeneousContainer<Shrinkable> shrinkable_container;

        auto index1 = shrinkable_container.insert(42);
        auto index2 = shrinkable_container.insert(3.14);
        auto index3 = shrinkable_container.insert(Point{ 1, 2 });

        std::cout << "Value at index1: " << shrinkable_container.get<int>(index1) << std::endl;
        std::cout << "Value at index2: " << shrinkable_container.get<double>(index2) << std::endl;
        std::cout << "Value at index3: " << shrinkable_container.get<Point>(index3).x << ", " << shrinkable_container.get<Point>(index3).y << std::endl;

        std::cout << "Size of shrinkable_container: " << shrinkable_container.size_bytes() << " bytes\n";

        std::cout << "Removing index1\n";
        shrinkable_container.remove(index1);

        std::cout << "Removing index2\n";
        shrinkable_container.remove(index2);

        std::cout << "Size of shrinkable_container: " << shrinkable_container.size_bytes() << " bytes\n";

    }
    catch (const ContainerException& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}


