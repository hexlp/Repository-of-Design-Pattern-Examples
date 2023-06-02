#include <map>
#include <memory>

class Font {
public:
    Font(std::string name, int size) : name_(name), size_(size) {}

    std::string getName() const {
        return name_;
    }

    int getSize() const {
        return size_;
    }

private:
    std::string name_;
    int size_;
};

class FontFactory {
public:
    std::shared_ptr<Font> getFont(std::string name, int size) {
        // Check if the font already exists in the pool
        std::string key = name + std::to_string(size);
        auto it = fonts_.find(key);
        if (it != fonts_.end()) {
            // Font already exists, return it
            return it->second;
        }

        // Font does not exist, create a new one and add it to the pool
        auto font = std::make_shared<Font>(name, size);
        fonts_[key] = font;
        return font;
    }

private:
    std::map<std::string, std::shared_ptr<Font>> fonts_;
};

int main(){


    FontFactory fontFactory;

    // Display some text using a 12pt Arial font
    auto font1 = fontFactory.getFont("Arial", 12);
    std::cout << "Text in " << font1->getName() << " " << font1->getSize() << "pt font\n";

    // Display some text using a 16pt Times New Roman font
    auto font2 = fontFactory.getFont("Times New Roman", 16);
    std::cout << "Text in " << font2->getName() << " " << font2->getSize() << "pt font\n";

    // Display some more text using the same 12pt Arial font as before
    auto font3 = fontFactory.getFont("Arial", 12);
    std::cout << "More text in " << font3->getName() << " " << font3->getSize() << "pt font\n";

    return 0;
}