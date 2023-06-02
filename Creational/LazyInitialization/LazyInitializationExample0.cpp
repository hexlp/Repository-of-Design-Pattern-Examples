class ExpensiveObject {
public:
    ExpensiveObject() {
        // Expensive initialization process
        //         
        // ...
        std::cout << "Expensive initialization executed." << "\n";
    }

    void performOperation() {
        // Perform some operation
        std::cout << "Operation executed." << "\n";
    }
};

class LazyInitialization {
private:
    ExpensiveObject* actualObject = nullptr;

public:
    void performOperation() {
        if (actualObject == nullptr) {
            actualObject = new ExpensiveObject();
        }
        actualObject->performOperation();     
    }      

};



int main() {
    LazyInitialization lazyInitialization;
    lazyInitialization.performOperation();
    return 0;
}
