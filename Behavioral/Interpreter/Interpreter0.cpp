/*
The Interpreter pattern is used to define a language or grammar 
and interpret sentences or expressions in that language. 
*/

#include <iostream>
#include <string>
#include <unordered_map>

class Context {
public:
    bool isTrue(const std::string& variable) const {
        auto it = variables.find(variable);
        if (it != variables.end()) {
            return it->second;
        }
        return false;
    }

    void setVariable(const std::string& variable, bool value) {
        variables[variable] = value;
    }

private:
    std::unordered_map<std::string, bool> variables;
};

class Expression {
public:
    virtual bool evaluate(const Context& context) const = 0;
};

class VariableExpression : public Expression {
public:
    explicit VariableExpression(const std::string& variable) : variable(variable) {}

    bool evaluate(const Context& context) const override {
        return context.isTrue(variable);
    }

private:
    std::string variable;
};

class AndExpression : public Expression {
public:
    AndExpression(const Expression* left, const Expression* right)
        : left(left), right(right) {}

    bool evaluate(const Context& context) const override {
        return left->evaluate(context) && right->evaluate(context);
    }

private:
    const Expression* left;
    const Expression* right;
};

class OrExpression : public Expression {
public:
    OrExpression(const Expression* left, const Expression* right)
        : left(left), right(right) {}

    bool evaluate(const Context& context) const override {
        return left->evaluate(context) || right->evaluate(context);
    }

private:
    const Expression* left;
    const Expression* right;
};

int main() {
    // Create the context
    Context context;

    // Set the variables in the context
    context.setVariable("A", true);
    context.setVariable("B", false);
    context.setVariable("C", true);

    // Define the expressions
    Expression* expression1 = new AndExpression(
        new VariableExpression("A"),
        new OrExpression(
            new VariableExpression("B"),
            new VariableExpression("C")
        )
    );

    Expression* expression2 = new AndExpression(
        new VariableExpression("A"),
        new VariableExpression("B")
    );

    // Evaluate the expressions
    std::cout << "Expression 1 evaluation: " << expression1->evaluate(context) << std::endl;
    std::cout << "Expression 2 evaluation: " << expression2->evaluate(context) << std::endl;

    // Clean up
    delete expression1;
    delete expression2;

    return 0;
}
