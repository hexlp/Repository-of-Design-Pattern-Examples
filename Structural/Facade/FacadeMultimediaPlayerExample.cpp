#include <iostream>

// Subsystem 1: MP3 Codec
class MP3Codec {
public:
    void decode(const std::string& filePath) {
        std::cout << "Decoding MP3 file: " << filePath << std::endl;
        // Additional decoding logic goes here
    }
};

// Subsystem 2: WAV Codec
class WAVCodec {
public:
    void decode(const std::string& filePath) {
        std::cout << "Decoding WAV file: " << filePath << std::endl;
        // Additional decoding logic goes here
    }
};

// Subsystem 3: MP4 Codec
class MP4Codec {
public:
    void decode(const std::string& filePath) {
        std::cout << "Decoding MP4 file: " << filePath << std::endl;
        // Additional decoding logic goes here
    }
};

// Facade
class MultimediaPlayer {
private:
    MP3Codec mp3Codec;
    WAVCodec wavCodec;
    MP4Codec mp4Codec;

public:
    void play(const std::string& filePath) {
        // Determine the file format based on the file extension
        std::string extension = getFileExtension(filePath);

        if (extension == "mp3") {
            mp3Codec.decode(filePath);
            std::cout << "Playing MP3 file." << std::endl;
        } else if (extension == "wav") {
            wavCodec.decode(filePath);
            std::cout << "Playing WAV file." << std::endl;
        } else if (extension == "mp4") {
            mp4Codec.decode(filePath);
            std::cout << "Playing MP4 file." << std::endl;
        } else {
            std::cout << "Unsupported file format." << std::endl;
        }
    }

private:
    std::string getFileExtension(const std::string& filePath) {
        // Extract the file extension from the file path
        size_t dotPos = filePath.find_last_of('.');
        if (dotPos != std::string::npos) {
            return filePath.substr(dotPos + 1);
        }
        return "";
    }
};

int main() {
    // Client code interacts with the multimedia player using the Facade
    MultimediaPlayer player;

    // Play different media files
    player.play("music.mp3");
    player.play("audio.wav");
    player.play("video.mp4");

    return 0;
}
