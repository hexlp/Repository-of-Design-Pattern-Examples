/*
The Private Class Data Pattern, also known as the Data Object Pattern, is 
a design pattern that aims to encapsulate data and restrict direct access 
to it by providing controlled access through methods. It focuses on separating 
the data and behavior of a class, promoting data encapsulation and information hiding.

*/

#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    std::string customerName;

public:
    BankAccount(const std::string& accNum, double initialBalance, const std::string& custName)
        : accountNumber(accNum), balance(initialBalance), customerName(custName) {}

    std::string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void setBalance(double newBalance) {
        if (newBalance >= 0) {
            balance = newBalance;
        } else {
            std::cout << "Invalid balance value. Balance remains unchanged.\n";
        }
    }

    std::string getCustomerName() const {
        return customerName;
    }
};

int main() {
    BankAccount account("123456789", 1000.0, "John Doe");

    std::cout << "Account Number: " << account.getAccountNumber() << std::endl;
    std::cout << "Current Balance: " << account.getBalance() << std::endl;
    std::cout << "Customer Name: " << account.getCustomerName() << std::endl;

    account.setBalance(1500.0);
    std::cout << "Updated Balance: " << account.getBalance() << std::endl;

    account.setBalance(-500.0);  // Trying to set an invalid negative balance
    std::cout << "Balance after invalid update: " << account.getBalance() << std::endl;

    return 0;
}
