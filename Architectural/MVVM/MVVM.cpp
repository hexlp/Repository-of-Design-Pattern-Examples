/*
The Model-View-ViewModel (MVVM) is a software architectural 
pattern that separates the user interface (View) from the 
underlying data (Model) and introduces a mediator called 
ViewModel. MVVM is commonly used in the development of graphical 
user interfaces (GUIs) and is particularly popular in frameworks 
like WPF (Windows Presentation Foundation) and Xamarin.

In MVVM, the responsibilities are divided as follows:

1. Model: The Model represents the data and business logic of 
the application. It encapsulates the data and provides methods 
to access, manipulate, and validate it.

2. View: The View represents the user interface and is responsible 
for displaying the data to the user and capturing user interactions. 
It is typically implemented using markup languages like XAML in WPF or XML in Android.

3. ViewModel: The ViewModel acts as an intermediary between the View 
and the Model. It exposes the necessary data and commands required by 
the View to display and interact with the data. It provides data bindings, 
which allow the View to automatically update when the data in the ViewModel 
changes, and vice versa.

The ViewModel is responsible for:

- Exposing properties and commands that the View can bind to.
- Managing the state and behavior of the View.
- Providing data transformation and formatting.
- Coordinating data retrieval and manipulation with the Model.

*/

#include <iostream>
#include <string>

// Model
class UserModel {
private:
    std::string username;

public:
    void setUsername(const std::string& username) {
        this->username = username;
    }

    std::string getUsername() const {
        return username;
    }
};

// ViewModel
class UserViewModel {
private:
    UserModel model;

public:
    void setUsername(const std::string& username) {
        model.setUsername(username);
    }

    std::string getUsername() const {
        return model.getUsername();
    }
};

// View
class UserView {
public:
    void displayUsername(const std::string& username) {
        std::cout << "Username: " << username << std::endl;
    }
};

// Application
int main() {
    UserViewModel viewModel;
    UserView view;

    // Simulate user input
    std::string usernameInput = "JohnDoe";

    // Update ViewModel with user input
    viewModel.setUsername(usernameInput);

    // Get data from ViewModel and display in View
    std::string username = viewModel.getUsername();
    view.displayUsername(username);

    return 0;
}
