/*
The Specification Pattern is a behavioral design pattern that allows you 
to define and combine business rules or conditions to make complex queries 
or evaluations. It separates the specification of the rules from the actual 
logic that uses those rules. The pattern is commonly used in scenarios where 
you need to filter or select objects based on specific criteria.

The Specification Pattern allows us to encapsulate complex business rules
or conditions in separate specification classes. It promotes flexibility and
reusability by decoupling the rule specification from the client code that 
uses those rules. This pattern is particularly useful in scenarios where you 
have a variety of filtering or querying requirements and want to avoid cluttering
the client code with conditional logic.*/


#include <iostream>
#include <vector>
#include <string>

// Product class representing an item
class Product {
public:
    std::string name;
    std::string category;
    double price;

    Product(const std::string& name, const std::string& category, double price)
        : name(name), category(category), price(price) {}
};

// Specification interface defining the rule
class Specification {
public:
    virtual bool isSatisfied(const Product& product) const = 0;
};

// Concrete specification for filtering products by category
class CategorySpecification : public Specification {
private:
    std::string category;

public:
    CategorySpecification(const std::string& category) : category(category) {}

    bool isSatisfied(const Product& product) const override {
        return product.category == category;
    }
};

// Concrete specification for filtering products by price
class PriceSpecification : public Specification {
private:
    double minPrice;
    double maxPrice;

public:
    PriceSpecification(double minPrice, double maxPrice)
        : minPrice(minPrice), maxPrice(maxPrice) {}

    bool isSatisfied(const Product& product) const override {
        return product.price >= minPrice && product.price <= maxPrice;
    }
};

// Composite specification for combining multiple specifications with AND operator
class AndSpecification : public Specification {
private:
    const Specification& spec1;
    const Specification& spec2;

public:
    AndSpecification(const Specification& spec1, const Specification& spec2)
        : spec1(spec1), spec2(spec2) {}

    bool isSatisfied(const Product& product) const override {
        return spec1.isSatisfied(product) && spec2.isSatisfied(product);
    }
};

// ProductFilter class for filtering products based on specifications
class ProductFilter {
public:
    std::vector<Product> filter(const std::vector<Product>& products, const Specification& spec) {
        std::vector<Product> result;
        for (const auto& product : products) {
            if (spec.isSatisfied(product)) {
                result.push_back(product);
            }
        }
        return result;
    }
};

int main() {
    // Creating some sample products
    Product p1("Phone", "Electronics", 999.99);
    Product p2("Shirt", "Apparel", 49.99);
    Product p3("TV", "Electronics", 1499.99);
    Product p4("Shoes", "Apparel", 79.99);
	Product p5("Digital Camera", "Electronics", 99.99);
	
    std::vector<Product> products = {p1, p2, p3, p4, p5};

    // Creating specifications
    Specification* electronicsSpec = new CategorySpecification("Electronics");
    Specification* affordableSpec = new PriceSpecification(0, 100);

    // Using the ProductFilter to filter products based on specifications
    ProductFilter filter;
    std::vector<Product> filteredProducts = filter.filter(products, *electronicsSpec);
    std::cout << "Electronics products:" << std::endl;
    for (const auto& product : filteredProducts) {
        std::cout << product.name << " - $" << product.price << std::endl;
    }

    filteredProducts = filter.filter(products, *affordableSpec);
    std::cout << "\nAffordable products:" << std::endl;
    for (const auto& product : filteredProducts) {
        std::cout << product.name << " - $" << product.price << std::endl;
    }

    // Creating a composite specification using AND operator
    Specification* electronicsAndAffordableSpec = new AndSpecification(*electronicsSpec, *affordableSpec);
    filteredProducts = filter.filter(products, *electronicsAndAffordableSpec);
    std::cout << "\nElectronics and affordable products:" << std::endl;
    for (const auto& product : filteredProducts) {
        std::cout << product.name << " - $" << product.price << std::endl;
    }

    // Clean up dynamically allocated memory
    delete electronicsSpec;
    delete affordableSpec;
    delete electronicsAndAffordableSpec;

    return 0;
}

