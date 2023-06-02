/*

The Mediator pattern is a behavioral design pattern that promotes loose coupling between objects 
by encapsulating their interaction within a mediator object. It allows objects to communicate with 
each other indirectly through the mediator, rather than directly coupling and depending on one another. 
This pattern centralizes the communication logic, reducing the dependencies and simplifying the overall system architecture.

*/

#include <iostream>
#include <string>
#include <vector>

class Participant; // Forward declaration

class ChatRoom {
private:
    std::vector<Participant*> participants;

public:
    void registerParticipant(Participant* participant);
    void sendMessage(const std::string& sender, const std::string& receiver, const std::string& message);
    const std::vector<Participant*>& getParticipants() const { return participants; }   
};

class Participant {
protected:
    ChatRoom* chatRoom;
    std::string name;

public:
    Participant(const std::string& n) : name(n), chatRoom(nullptr) {}

    virtual void sendMessage(const std::string& message) = 0;
    virtual void receiveMessage(const std::string& sender, const std::string& message) = 0;

    void setChatRoom(ChatRoom* room) { chatRoom = room; }
    std::string getName() const { return name; }
};

void ChatRoom::registerParticipant(Participant* participant) {
    participants.push_back(participant);
    participant->setChatRoom(this);
}

void ChatRoom::sendMessage(const std::string& sender, const std::string& receiver, const std::string& message) {
    for (auto participant : participants) {
        if (participant->getName() == receiver) {
            participant->receiveMessage(sender, message);
            break;
        }
    }
}

class User : public Participant {
public:
    User(const std::string& name) : Participant(name) {}

    void sendMessage(const std::string& message) override {
        chatRoom->sendMessage(name, "Admin", message);
    }

    void receiveMessage(const std::string& sender, const std::string& message) override {
        std::cout << "User " << name << " received a message from " << sender << ": " << message << std::endl;
    }
};

class Admin : public Participant {
public:
    Admin(const std::string& name) : Participant(name) {}

    void sendMessage(const std::string& message) override {
        for (auto participant : chatRoom->getParticipants()) {
            if (participant->getName() != name) {
                participant->receiveMessage(name, message);
            }
        }
    }

    void receiveMessage(const std::string& sender, const std::string& message) override {
        std::cout << "Admin " << name << " received a message from " << sender << ": " << message << std::endl;
    }
};

int main() {
    ChatRoom chatRoom;

    User user1("Alice");
    User user2("Bob");
    Admin admin("Admin");

    chatRoom.registerParticipant(&user1);
    chatRoom.registerParticipant(&user2);
    chatRoom.registerParticipant(&admin);

    user1.sendMessage("Hello, everyone!");
    admin.sendMessage("Welcome to the chat room!");
    user2.sendMessage("Nice to meet you all!");

    return 0;
}
