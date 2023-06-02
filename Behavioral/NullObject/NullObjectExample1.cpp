#include <iostream>
#include <memory>

// Abstract base class defining the interface
class Renderer {
public:
    virtual void render() = 0;
};

// Concrete implementation of Renderer
class OpenGLRenderer : public Renderer {
public:
    void render() override {
        std::cout << "Rendering using OpenGL" << std::endl;
    }
};

// NullObjectRenderer representing a null or no-op behavior
class NullObjectRenderer : public Renderer {
public:
    void render() override {
        // Do nothing (null behavior)
    }
};

// Client class that uses the Renderer
class Scene {
private:
    std::unique_ptr<Renderer> renderer;

public:
    Scene() : renderer(std::make_unique<NullObjectRenderer>()) {}

    void setRenderer(std::unique_ptr<Renderer> newRenderer) {
        if (newRenderer) {
            renderer = std::move(newRenderer);
        }
    }

    void renderScene() {
        renderer->render();
    }
};

int main() {
    Scene scene;

    // Render scene using OpenGL if available
    bool useOpenGL = true;
    if (useOpenGL) {
        scene.setRenderer(std::make_unique<OpenGLRenderer>());
    }

    scene.renderScene();

    return 0;
}
/*

In this example, we have an abstract base class Renderer that defines the rendering interface. 
The OpenGLRenderer class is a concrete implementation of the Renderer interface, which performs
rendering using the OpenGL graphics library.

The NullObjectRenderer class represents the null object or no-op behavior. It also implements
the Renderer interface, but its render method does nothing. It is used as the default renderer
in the Scene class when no specific renderer is provided.

The Scene class acts as the client class that uses the renderer. It has a member variable 
renderer of type std::unique_ptr<Renderer> to hold the renderer object. By default, it is 
initialized with a NullObjectRenderer instance.

The Scene class provides a setRenderer method to update the renderer. It performs a null 
check before setting the new renderer, ensuring that only valid renderer objects are assigned.

The renderScene method of the Scene class calls the render method of the current renderer,
regardless of whether it is the actual OpenGLRenderer or the NullObjectRenderer.

In the main function, we create a Scene object and set the renderer based on a condition (useOpenGL).
If useOpenGL is true, we set the renderer to an instance of OpenGLRenderer, enabling rendering using OpenGL.
Otherwise, the default NullObjectRenderer is used, which allows the scene to be rendered without any errors or null checks.

By utilizing the Null Object Pattern, we ensure that the scene can always be rendered even when 
a specific renderer is not available or provided. It eliminates the need for explicit null checks,
enhances code robustness, and simplifies the handling of absent objects.


*/