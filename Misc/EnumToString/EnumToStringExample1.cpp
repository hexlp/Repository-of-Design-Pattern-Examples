#include <iostream>
#include <string>

enum Color {
    RED,
    GREEN,
    BLUE,
    COLOR_COUNT // To count the number of enums
};

const char* ColorStrings[] = {
    "RED",
    "GREEN",
    "BLUE"
};

const char* ColorToString(Color color) {
    if (color >= 0 && color < COLOR_COUNT) {
        return ColorStrings[color];
    }
    return "Unknown";
}

int main() {
    Color myColor = GREEN;
    std::cout << "The color is: " << ColorToString(myColor) << std::endl;

    return 0;
}
