#include <iostream>
#include <string>
#include <vector>

// Product class
class Product {
public:
    Product(const std::string& name, const std::string& brand, const std::string& category, double price)
        : name_(name), brand_(brand), category_(category), price_(price) {}

    std::string getName() const { return name_; }
    std::string getBrand() const { return brand_; }
    std::string getCategory() const { return category_; }
    double getPrice() const { return price_; }

private:
    std::string name_;
    std::string brand_;
    std::string category_;
    double price_;
};

// Specification interface
class Specification {
public:
    virtual bool isSatisfiedBy(const class Product& product) const = 0;
};

// Concrete specification: Price range
class PriceSpecification : public Specification {
public:
    PriceSpecification(double minPrice, double maxPrice)
        : minPrice_(minPrice), maxPrice_(maxPrice) {}

    bool isSatisfiedBy(const class Product& product) const override {
        double price = product.getPrice();
        return (price >= minPrice_ && price <= maxPrice_);
    }

private:
    double minPrice_;
    double maxPrice_;
};

// Concrete specification: Brand
class BrandSpecification : public Specification {
public:
    explicit BrandSpecification(const std::string& brand)
        : brand_(brand) {}

    bool isSatisfiedBy(const class Product& product) const override {
        return (product.getBrand() == brand_);
    }

private:
    std::string brand_;
};

// Concrete specification: Category
class CategorySpecification : public Specification {
public:
    explicit CategorySpecification(const std::string& category)
        : category_(category) {}

    bool isSatisfiedBy(const class Product& product) const override {
        return (product.getCategory() == category_);
    }

private:
    std::string category_;
};

// Composite specification: AND operator
class AndSpecification : public Specification {
public:
    AndSpecification(const Specification& spec1, const Specification& spec2)
        : spec1_(spec1), spec2_(spec2) {}

    bool isSatisfiedBy(const class Product& product) const override {
        return (spec1_.isSatisfiedBy(product) && spec2_.isSatisfiedBy(product));
    }

private:
    const Specification& spec1_;
    const Specification& spec2_;
};

// Search function using specifications
std::vector<Product> searchProducts(const std::vector<Product>& products, const Specification& specification) {
    std::vector<Product> result;
    for (const auto& product : products) {
        if (specification.isSatisfiedBy(product)) {
            result.push_back(product);
        }
    }
    return result;
}

int main() {
    std::vector<Product> products = {
        Product("Product 1", "Brand A", "Category X", 100.0),
        Product("Product 2", "Brand B", "Category Y", 150.0),
        Product("Product 3", "Brand A", "Category X", 200.0),
        Product("Product 4", "Brand C", "Category Z", 120.0)
    };

    // Create specifications
    PriceSpecification priceSpec(100.0, 200.0);
    BrandSpecification brandSpec("Brand A");
    CategorySpecification categorySpec("Category X");

    // Combine specifications using AND operator
    AndSpecification combinedSpec = AndSpecification(priceSpec, brandSpec);

    // Search for products matching the combined specification
    std::vector<Product> searchResult = searchProducts(products, combinedSpec);

    // Display the search result
    for (const auto& product : searchResult) {
        std::cout << product.getName() << std::endl;
    }

    return 0;
}