#include <iostream>
#include <string>

// Subject interface
class Image {
public:
    virtual void display() = 0;
};

// Real subject
class RealImage : public Image {
private:
    std::string filename;

public:
    RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk();
    }

    void display() override {
        std::cout << "Displaying image: " << filename << std::endl;
    }

    void loadFromDisk() {
        std::cout << "Loading image from disk: " << filename << std::endl;
    }
};

// Proxy class
class ImageProxy : public Image {
private:
    std::string filename;
    RealImage* realImage;

public:
    ImageProxy(const std::string& filename) : filename(filename), realImage(nullptr) {}

    void display() override {
        if (realImage == nullptr) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
};

int main() {
    // Creating a proxy object
    Image* image = new ImageProxy("image.jpg");

    // Image is loaded and displayed on demand
    image->display();

    // Image is already loaded, so it's displayed directly from the proxy
    image->display();

    delete image;

    return 0;
}
