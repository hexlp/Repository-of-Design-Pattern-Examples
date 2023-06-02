
class Pizza {
public:
    void setDough(const std::string& dough) {
        m_dough = dough;
    }
    void setSauce(const std::string& sauce) {
        m_sauce = sauce;
    }
    void setTopping(const std::string& topping) {
        m_topping = topping;
    }
    void open() const {
        std::cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and " << m_topping << " topping. Mmm!\n";
    }
private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
};

class PizzaBuilder {
public:
    PizzaBuilder& setDough(const std::string& dough) {
        m_dough = dough;
        return *this;
    }
    PizzaBuilder& setSauce(const std::string& sauce) {
        m_sauce = sauce;
        return *this;
    }
    PizzaBuilder& setTopping(const std::string& topping) {
        m_topping = topping;
        return *this;
    }
    Pizza build() {
        Pizza pizza;
        pizza.setDough(m_dough);
        pizza.setSauce(m_sauce);
        pizza.setTopping(m_topping);
        return pizza;
    }
private:
    std::string m_dough;
    std::string m_sauce;
    std::string m_topping;
};

int main() {

    PizzaBuilder builder;
    Pizza margherita = builder.setDough("regular").setSauce("tomato").setTopping("mozzarella").build();
    margherita.open(); // Output: Pizza with regular dough, tomato sauce and mozzarella topping. Mmm!

    return 0;
}
