#include <iostream>
#include <memory>

using namespace std;

class MovieTheaterFacade {
public:
    void watchMovie() {
        // Turn on the projector
        turnOnProjector();

        // Set the audio system
        setAudioSystem();

        // Start the movie
        startMovie();
    }

    void buyTicket() {
        // Calculate the ticket price
        int price = calculateTicketPrice();

        // Print the ticket
        printTicket(price);
    }

    void getRefreshments() {
        // Get the popcorn
        getPopcorn();

        // Get the drink
        getDrink();
    }

private:
    void turnOnProjector() {
        cout << "Turning on the projector..." << endl;
    }

    void setAudioSystem() {
        cout << "Setting the audio system..." << endl;
    }

    void startMovie() {
        cout << "Starting the movie..." << endl;
    }

    int calculateTicketPrice() {
        return 10;
    }

    void printTicket(int price) {
        cout << "Ticket price: " << price << " dollars." << endl;
    }

    void getPopcorn() {
        cout << "Getting popcorn..." << endl;
    }

    void getDrink() {
        cout << "Getting drink..." << endl;
    }
};


// Here's how a customer can use the `MovieTheaterFacade` class to watch a movie, buy a ticket, and get refreshments:

int main() {
    MovieTheaterFacade facade;

    // Watch a movie
    facade.watchMovie();

    // Buy a ticket
    facade.buyTicket();

    // Get refreshments
    facade.getRefreshments();

    return 0;
}

/*
Suppose you are running a movie theater and you want to simplify the process of watching a movie for your customers.
You can create a Facade class called `MovieTheaterFacade` that hides the complexity of the inner workings of the movie theater
and provides a simple interface for the customers to use. The `MovieTheaterFacade` class can provide methods such as `watchMovie()`, `buyTicket()`, and `getRefreshments()`.
*/

