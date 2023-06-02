#include <iostream>
#include <string>

class Email {
private:
    std::string address;

public:
    Email(const std::string& address) : address(address) {}

    std::string getAddress() const {
        return address;
    }

    // Equality comparison operator
    bool operator==(const Email& other) const {
        return address == other.address;
    }

    // Inequality comparison operator
    bool operator!=(const Email& other) const {
        return !(*this == other);
    }
};

int main() {
    Email email1("john@example.com");
    Email email2("john@example.com");
    Email email3("jane@example.com");

    // Equality comparison
    if (email1 == email2) {
        std::cout << "Email 1 and Email 2 are equal." << std::endl;
    } else {
        std::cout << "Email 1 and Email 2 are not equal." << std::endl;
    }

    if (email1 == email3) {
        std::cout << "Email 1 and Email 3 are equal." << std::endl;
    } else {
        std::cout << "Email 1 and Email 3 are not equal." << std::endl;
    }

    // Inequality comparison
    if (email1 != email2) {
        std::cout << "Email 1 and Email 2 are not equal." << std::endl;
    } else {
        std::cout << "Email 1 and Email 2 are equal." << std::endl;
    }

    if (email1 != email3) {
        std::cout << "Email 1 and Email 3 are not equal." << std::endl;
    } else {
        std::cout << "Email 1 and Email 3 are equal." << std::endl;
    }

    return 0;
}
