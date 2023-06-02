#include <iostream>
#include <string>

class TrafficSignalState {
public:
    virtual void handle() = 0;
};

class RedSignalState : public TrafficSignalState {
public:
    void handle() {
        std::cout << "Stop!\n";
    }
};

class YellowSignalState : public TrafficSignalState {
public:
    void handle() {
        std::cout << "Slow down!\n";
    }
};

class GreenSignalState : public TrafficSignalState {
public:
    void handle() {
        std::cout << "Go!\n";
    }
};

class TrafficSignal {
private:
    TrafficSignalState* currentState;

public:
    TrafficSignal() {
        currentState = new RedSignalState();
    }

    void setState(TrafficSignalState* state) {
        currentState = state;
    }

    void handleSignal() {
        currentState->handle();
    }
};

int main() {
    TrafficSignal trafficSignal;

    trafficSignal.handleSignal();

    trafficSignal.setState(new GreenSignalState());
    trafficSignal.handleSignal();

    trafficSignal.setState(new YellowSignalState());
    trafficSignal.handleSignal();

    trafficSignal.setState(new RedSignalState());
    trafficSignal.handleSignal();

    return 0;
}
