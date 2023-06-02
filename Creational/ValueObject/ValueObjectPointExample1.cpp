/*
The Value Object Pattern is a design pattern used to represent immutable objects whose
equality is based on their values rather than their identity. Value objects are typically used to
encapsulate a group of related attributes or properties into a single object.

Value objects are typically immutable, meaning their state cannot be modified after creation. 
This immutability guarantees that the values of value objects remain consistent and enables them 
to be used safely in multithreaded environments. 
*/

#include <iostream>
#include <string>

class Point {
private:
    int x;
    int y;

public:
    Point(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    // Equality comparison operator
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // Inequality comparison operator
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

int main() {
    Point p1(2, 3);
    Point p2(2, 3);
    Point p3(4, 5);

    // Equality comparison
    if (p1 == p2) {
        std::cout << "p1 and p2 are equal." << std::endl;
    } else {
        std::cout << "p1 and p2 are not equal." << std::endl;
    }

    if (p1 == p3) {
        std::cout << "p1 and p3 are equal." << std::endl;
    } else {
        std::cout << "p1 and p3 are not equal." << std::endl;
    }

    // Inequality comparison
    if (p1 != p2) {
        std::cout << "p1 and p2 are not equal." << std::endl;
    } else {
        std::cout << "p1 and p2 are equal." << std::endl;
    }

    if (p1 != p3) {
        std::cout << "p1 and p3 are not equal." << std::endl;
    } else {
        std::cout << "p1 and p3 are equal." << std::endl;
    }

    return 0;
}

/*
By using the Value Object Pattern, we ensure that the equality of Point objects is based 
on their values rather than their memory locations. This allows us to compare Point
objects easily and reliably, making them suitable for scenarios where value-based equality is
 desired, such as in mathematical calculations or when working with geometric coordinates.
*/
