/*

The Adapter pattern is a structural design pattern that allows objects with incompatible interfaces to work together. 
It acts as a bridge between two incompatible interfaces, converting the interface of one class into another interface that the client expects.

The primary purpose of the Adapter pattern is to enable communication and interaction between classes or systems that wouldn't otherwise 
be possible due to incompatible interfaces. It allows the client code to work with different classes or systems through a common interface provided by the adapter.

By using adapters, the existing codebase can be reused without the need for modification, even when integrating with new or third-party 
components that have different interfaces. Adapters encapsulate the necessary conversions or mappings between the interfaces, providing 
a seamless integration experience.

In summary, the Adapter pattern provides a way to make two incompatible interfaces work together by introducing an adapter class that 
translates or adapts the interface of one class to match the expectations of the other class. It promotes flexibility, reusability, 
and interoperability between different components or systems in a codebase.

*/



#include <iostream>
#include <string>


// AudioPlayer is the target interface that the client expects to interact with
class AudioPlayer {
public:
    virtual void playAudio(const std::string& audioType, const std::string& fileName) = 0;
};

// MP3Player is a concrete implementation of the AudioPlayer interface
class MP3Player : public AudioPlayer {
public:
    void playAudio(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            std::cout << "Playing MP3 file: " << fileName << std::endl;
        }
        else {
            std::cout << "Unsupported audio format." << std::endl;
        }
    }
};

// AdvancedAudioPlayer is the interface for advanced audio formats
class AdvancedAudioPlayer {
public:
    virtual void playMP4(const std::string& fileName) = 0;
    virtual void playWMA(const std::string& fileName) = 0;
};

// VLCPlayer is a concrete implementation of the AdvancedAudioPlayer interface
class VLCPlayer : public AdvancedAudioPlayer {
public:
    void playMP4(const std::string& fileName) override {
        std::cout << "Playing MP4 file: " << fileName << std::endl;
    }

    void playWMA(const std::string& fileName) override {
        std::cout << "Playing WMA file: " << fileName << std::endl;
    }
};

// Adapter class that adapts the AdvancedAudioPlayer interface to the AudioPlayer interface
class AudioPlayerAdapter : public AudioPlayer {
public:
    AudioPlayerAdapter(AdvancedAudioPlayer* advancedAudioPlayer) : advancedAudioPlayer_(advancedAudioPlayer) {}

    void playAudio(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp4") {
            advancedAudioPlayer_->playMP4(fileName);
        }
        else if (audioType == "wma") {
            advancedAudioPlayer_->playWMA(fileName);
        }
        else {
            std::cout << "Unsupported audio format." << std::endl;
        }
    }

private:
    AdvancedAudioPlayer* advancedAudioPlayer_;
};

int main() {
    // Client code
    AudioPlayer* audioPlayer = new MP3Player();
    audioPlayer->playAudio("mp3", "song.mp3");
    audioPlayer->playAudio("mp4", "movie.mp4");  // Unsupported format

    std::cout << "-----------------" << std::endl;

    AdvancedAudioPlayer* vlcPlayer = new VLCPlayer();
    AudioPlayer* adapter = new AudioPlayerAdapter(vlcPlayer);
    adapter->playAudio("mp3", "audio.mp3");  // Unsupported format
    adapter->playAudio("mp4", "video.mp4");
    adapter->playAudio("wma", "audio.wma");

    delete audioPlayer;
    delete vlcPlayer;
    delete adapter;

    return 0;
}
