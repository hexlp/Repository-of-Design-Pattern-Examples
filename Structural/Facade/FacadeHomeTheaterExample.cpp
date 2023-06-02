#include <iostream>

// Subsystem 1: Lights
class Lights {
public:
    void turnOn() {
        std::cout << "Lights turned on." << std::endl;
    }

    void turnOff() {
        std::cout << "Lights turned off." << std::endl;
    }
};

// Subsystem 2: TV
class TV {
public:
    void turnOn() {
        std::cout << "TV turned on." << std::endl;
    }

    void turnOff() {
        std::cout << "TV turned off." << std::endl;
    }

    void changeChannel(int channel) {
        std::cout << "TV channel changed to " << channel << std::endl;
    }
};

// Subsystem 3: Sound System
class SoundSystem {
public:
    void turnOn() {
        std::cout << "Sound System turned on." << std::endl;
    }

    void turnOff() {
        std::cout << "Sound System turned off." << std::endl;
    }

    void setVolume(int volume) {
        std::cout << "Sound System volume set to " << volume << std::endl;
    }
};

// Facade
class HomeTheaterFacade {
private:
    Lights lights;
    TV tv;
    SoundSystem soundSystem;

public:
    void watchMovie(const std::string& movie) {
        std::cout << "Preparing to watch movie: " << movie << std::endl;

        lights.turnOff();
        tv.turnOn();
        tv.changeChannel(3);
        soundSystem.turnOn();
        soundSystem.setVolume(8);
    }

    void endMovie() {
        std::cout << "Ending movie." << std::endl;

        lights.turnOn();
        tv.turnOff();
        soundSystem.turnOff();
    }
};

int main() {
    // Client code interacts with the home theater using the Facade
    HomeTheaterFacade homeTheater;
    homeTheater.watchMovie("Avengers: Endgame");

    // Simulate some actions during the movie
    std::cout << "Doing something during the movie..." << std::endl;

    homeTheater.endMovie();

    return 0;
}
