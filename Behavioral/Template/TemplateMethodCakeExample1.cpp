#include <iostream>

// Abstract base class
class BakingRecipe {
public:
    // Template method
    void bakeCake() {
        prepareIngredients();
        mixIngredients();
        bakeInOven();
        if (needsFrosting()) {
            applyFrosting();
        }
        decorateCake();
    }

    // Abstract methods
    virtual void prepareIngredients() = 0;
    virtual void mixIngredients() = 0;
    virtual void bakeInOven() = 0;
    virtual void decorateCake() = 0;

    // Hook method
    virtual bool needsFrosting() {
        return true;
    }

    // Hook method
    virtual void applyFrosting() {
        std::cout << "Applying frosting" << std::endl;
    }
};

// Concrete subclass
class ChocolateCakeRecipe : public BakingRecipe {
public:
    void prepareIngredients() override {
        std::cout << "Preparing chocolate cake ingredients" << std::endl;
    }

    void mixIngredients() override {
        std::cout << "Mixing chocolate cake ingredients" << std::endl;
    }

    void bakeInOven() override {
        std::cout << "Baking chocolate cake in the oven" << std::endl;
    }

    void decorateCake() override {
        std::cout << "Decorating chocolate cake" << std::endl;
    }
};

// Concrete subclass
class VanillaCakeRecipe : public BakingRecipe {
public:
    void prepareIngredients() override {
        std::cout << "Preparing vanilla cake ingredients" << std::endl;
    }

    void mixIngredients() override {
        std::cout << "Mixing vanilla cake ingredients" << std::endl;
    }

    void bakeInOven() override {
        std::cout << "Baking vanilla cake in the oven" << std::endl;
    }

    void decorateCake() override {
        std::cout << "Decorating vanilla cake" << std::endl;
    }

    bool needsFrosting() override {
        return false;
    }
};

int main() {
    BakingRecipe* chocolateCakeRecipe = new ChocolateCakeRecipe();
    chocolateCakeRecipe->bakeCake();
    std::cout << "-------------" << std::endl;
    BakingRecipe* vanillaCakeRecipe = new VanillaCakeRecipe();
    vanillaCakeRecipe->bakeCake();

    delete chocolateCakeRecipe;
    delete vanillaCakeRecipe;

    return 0;
}
