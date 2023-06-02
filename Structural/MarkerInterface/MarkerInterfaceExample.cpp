/*
The Marker Interface Pattern is a design pattern that involves creating an empty interface,
also known as a marker interface, with no methods or properties. The sole purpose of this
interface is to mark or tag a class that implements it, indicating that the marked class 
has a certain capability or characteristic.

Key Points about the Marker Interface Pattern:

1. Empty Interface: A marker interface is an interface that does not declare any 
   methods or properties. It serves as a way to classify or identify certain types of objects or classes.

2. Tagging or Marking: By implementing a marker interface, a class is marked or 
   tagged with a specific characteristic or capability. This provides additional
   information or metadata about the class to the system or other components.

3. Reflective Behavior: The marker interface is often used in reflection or runtime
   processing to identify classes that have implemented the interface. It allows the
   system to perform certain actions or behaviors based on the presence of the marker interface.

4. No Additional Behavior: The marker interface itself does not define any behavior or functionality. 
   Its purpose is solely to mark or tag classes and provide a way to categorize them.

Benefits of the Marker Interface Pattern:

- Metadata and Classification: The marker interface allows classes to be categorized or classified
  based on their capabilities or characteristics. This can be useful for system-level processing or to enable certain behaviors.

- Flexibility and Extensibility: The pattern allows for dynamic behavior based on the presence of
  the marker interface. It enables flexible customization and extension of functionality without modifying the core code.

- Readability and Intent: The use of marker interfaces can make the code more readable and expressive
  by clearly indicating certain capabilities or traits of the marked classes.

*/


// Marker interface for editable media files
class Editable {
public:
    // Empty interface, no methods or properties
};

// Image file class implementing the Editable marker interface
class ImageFile : public Editable {
public:
    // Image file-specific implementation
};

// Video file class implementing the Editable marker interface
class VideoFile : public Editable {
public:
    // Video file-specific implementation
};

// Audio file class (not implementing the Editable marker interface)
class AudioFile {
public:
    // Audio file-specific implementation
};

void applyEffects(const Editable& mediaFile) {
    // Apply effects to the editable media file
    // ...
}

void processMediaFile(const Editable& mediaFile) {
    // Process the editable media file
    // ...
}

int main() {
    ImageFile image;      // Editable media file
    VideoFile video;      // Editable media file
    AudioFile audio;      // Non-editable media file

    applyEffects(image);  // Apply effects to the image file
    processMediaFile(video);  // Process the video file

    // Attempting to apply effects or process a non-editable media file
    // will result in a compilation error or warning
    // applyEffects(audio); // Compilation error

    return 0;
}