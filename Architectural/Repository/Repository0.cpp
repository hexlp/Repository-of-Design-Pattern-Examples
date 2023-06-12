#include <iostream>
#include <vector>

// Model
class User {
private:
    std::string username;

public:
    User(const std::string& username) : username(username) {}

    std::string getUsername() const {
        return username;
    }
};

// Repository Interface
class UserRepository {
public:
    virtual void addUser(const User& user) = 0;
    virtual void removeUser(const User& user) = 0;
    virtual User getUserByUsername(const std::string& username) const = 0;
};

// Concrete Repository
class InMemoryUserRepository : public UserRepository {
private:
    std::vector<User> users;

public:
    void addUser(const User& user) override {
        users.push_back(user);
    }

    void removeUser(const User& user) override {
        // Find and remove the user from the repository
        auto it = std::find_if(users.begin(), users.end(), [&](const User& u) {
            return u.getUsername() == user.getUsername();
            });

        if (it != users.end()) {
            users.erase(it);
        }
    }

    User getUserByUsername(const std::string& username) const override {
        // Find the user with the given username in the repository
        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getUsername() == username;
            });

        if (it != users.end()) {
            return *it;
        }

        throw std::runtime_error("User not found in the repository");
    }
};

// Client code
int main() {
    // Create repository instance
    UserRepository* userRepository = new InMemoryUserRepository();

    // Add users to the repository
    User user1("JohnDoe");
    userRepository->addUser(user1);

    User user2("JaneSmith");
    userRepository->addUser(user2);

    // Retrieve user from the repository
    User retrievedUser = userRepository->getUserByUsername("JohnDoe");
    std::cout << "Retrieved User: " << retrievedUser.getUsername() << std::endl;

    // Remove user from the repository
    userRepository->removeUser(user1);

    delete userRepository;

    return 0;
}
