

#include <iostream>
#include <vector>

// Forward declaration of item classes
class Item;
class Book;
class Clothing;
class Electronic;

// Visitor interface
class ShoppingCartVisitor {
public:
    virtual void visit(Book& book) = 0;
    virtual void visit(Clothing& clothing) = 0;
    virtual void visit(Electronic& electronic) = 0;
};

// Abstract item class
class Item {
public:
    virtual void accept(ShoppingCartVisitor& visitor) = 0;
    virtual double getPrice() const = 0;
};

// Concrete item classes
class Book : public Item {
private:
    std::string title;
    double price;

public:
    Book(const std::string& title, double price) : title(title), price(price) {}

    void accept(ShoppingCartVisitor& visitor) override {
        visitor.visit(*this);
    }

    double getPrice() const override {
        return price;
    }

    const std::string& getTitle() const {
        return title;
    }
};

class Clothing : public Item {
private:
    std::string name;
    double price;

public:
    Clothing(const std::string& name, double price) : name(name), price(price) {}

    void accept(ShoppingCartVisitor& visitor) override {
        visitor.visit(*this);
    }

    double getPrice() const override {
        return price;
    }

    const std::string& getName() const {
        return name;
    }
};

class Electronic : public Item {
private:
    std::string brand;
    double price;

public:
    Electronic(const std::string& brand, double price) : brand(brand), price(price) {}

    void accept(ShoppingCartVisitor& visitor) override {
        visitor.visit(*this);
    }

    double getPrice() const override {
        return price;
    }

    const std::string& getBrand() const {
        return brand;
    }
};

// Concrete visitor class to calculate total price
class PriceCalculatorVisitor : public ShoppingCartVisitor {
private:
    double totalPrice = 0.0;

public:
    void visit(Book& book) override {
        totalPrice += book.getPrice();
    }

    void visit(Clothing& clothing) override {
        totalPrice += clothing.getPrice();
    }

    void visit(Electronic& electronic) override {
        totalPrice += electronic.getPrice();
    }

    double getTotalPrice() const {
        return totalPrice;
    }
};

int main() {
    std::vector<Item*> items;
    items.push_back(new Book("The Catcher in the Rye", 10.99));
    items.push_back(new Clothing("T-Shirt", 15.99));
    items.push_back(new Electronic("Headphones", 49.99));

    PriceCalculatorVisitor priceCalculator;
    for (Item* item : items) {
        item->accept(priceCalculator);
    }

    std::cout << "Total Price: $" << priceCalculator.getTotalPrice() << std::endl;

    // Clean up dynamic memory
    for (Item* item : items) {
        delete item;
    }

    return 0;
}


/*

In this example, we have the Item base class and its derived classes Book, Clothing, and Electronic.
We also have a concrete visitor class PriceCalculatorVisitor that implements the ShoppingCartVisitor interface.

The Item base class defines the accept method that takes a ShoppingCartVisitor object as an argument. 
Each concrete item class implements the accept method to call the appropriate visitor method.

The PriceCalculatorVisitor calculates the total price by visiting each item and adding its price to the totalPrice variable.

By using the Visitor Pattern, we can easily add new item types without modifying
the existing classes, allowing for flexible and extensible calculations in the shopping cart scenario.

*/