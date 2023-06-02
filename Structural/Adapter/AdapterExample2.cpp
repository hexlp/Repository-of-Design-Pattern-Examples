#include <iostream>
#include <string>

// MessagingService is the target interface that the client expects to interact with
class MessagingService {
public:
    virtual void sendMessage(const std::string& message) = 0;
};

// EmailService is a concrete implementation of the MessagingService interface
class EmailService : public MessagingService {
public:
    void sendMessage(const std::string& message) override {
        std::cout << "Sending email: " << message << std::endl;
        // Actual email sending code here
        std::cout << "Email sent successfully." << std::endl;
    }
};

// SMSService is a concrete implementation of the MessagingService interface
class SMSService : public MessagingService {
public:
    void sendMessage(const std::string& message) override {
        std::cout << "Sending SMS: " << message << std::endl;
        // Actual SMS sending code here
        std::cout << "SMS sent successfully." << std::endl;
    }
};

// MessagingAdapter is the interface for adapting a messaging service to another messaging service
class MessagingAdapter {
public:
    virtual void sendMessage(const std::string& message) = 0;
};

// Adapting the EmailService to the MessagingAdapter interface
class EmailServiceAdapter : public MessagingAdapter {
public:
    EmailServiceAdapter(EmailService* emailService) : emailService_(emailService) {}

    void sendMessage(const std::string& message) override {
        emailService_->sendMessage(message);
    }

private:
    EmailService* emailService_;
};

int main() {
    // Client code
    MessagingService* emailService = new EmailService();
    MessagingAdapter* adapter = new EmailServiceAdapter(static_cast<EmailService*>(emailService));
    adapter->sendMessage("Hello, this is an email message.");

    std::cout << "-----------------" << std::endl;

    MessagingService* smsService = new SMSService();
    adapter = static_cast<MessagingAdapter*>(smsService);  // Directly use the SMSService as an adapter
    adapter->sendMessage("Hello, this is an SMS message.");

    delete emailService;
    delete adapter;
    delete smsService;

    return 0;
}
