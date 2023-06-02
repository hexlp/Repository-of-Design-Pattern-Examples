#include <iostream>
#include <string>
#include <memory>

// Core object interface
class Object {
public:
    virtual void render() const = 0;
};

// Extension object interface for materials
class MaterialExtension {
public:
    virtual void setMaterial(const std::string& material) = 0;
};

// Extension object interface for lighting
class LightingExtension {
public:
    virtual void setLighting(bool enable) = 0;
};

// Extension object interface for textures
class TextureExtension {
public:
    virtual void setTexture(const std::string& texture) = 0;
};

// Concrete core object
class Mesh : public Object {
public:
    void render() const override {
        std::cout << "Rendering Mesh" << std::endl;
    }
};

// Concrete extension object for materials
class MaterialExtensionImpl : public MaterialExtension {
public:
    void setMaterial(const std::string& material) override {
        std::cout << "Setting material: " << material << std::endl;
    }
};

// Concrete extension object for lighting
class LightingExtensionImpl : public LightingExtension {
public:
    void setLighting(bool enable) override {
        std::cout << "Setting lighting: " << (enable ? "On" : "Off") << std::endl;
    }
};

// Concrete extension object for textures
class TextureExtensionImpl : public TextureExtension {
public:
    void setTexture(const std::string& texture) override {
        std::cout << "Setting texture: " << texture << std::endl;
    }
};

// Extension object factory for materials
class MaterialExtensionFactory {
public:
    std::shared_ptr<MaterialExtension> createMaterialExtension() {
        return std::make_shared<MaterialExtensionImpl>();
    }
};

// Extension object factory for lighting
class LightingExtensionFactory {
public:
    std::shared_ptr<LightingExtension> createLightingExtension() {
        return std::make_shared<LightingExtensionImpl>();
    }
};

// Extension object factory for textures
class TextureExtensionFactory {
public:
    std::shared_ptr<TextureExtension> createTextureExtension() {
        return std::make_shared<TextureExtensionImpl>();
    }
};

int main() {
    // Create a core object
    std::unique_ptr<Object> mesh = std::make_unique<Mesh>();

    // Attach material extension to the core object
    MaterialExtensionFactory materialExtensionFactory;
    std::shared_ptr<MaterialExtension> materialExtension = materialExtensionFactory.createMaterialExtension();

    // Set material using the extension object
    materialExtension->setMaterial("Metallic");

    // Attach lighting extension to the core object
    LightingExtensionFactory lightingExtensionFactory;
    std::shared_ptr<LightingExtension> lightingExtension = lightingExtensionFactory.createLightingExtension();

    // Enable lighting using the extension object
    lightingExtension->setLighting(true);

    // Attach texture extension to the core object
    TextureExtensionFactory textureExtensionFactory;
    std::shared_ptr<TextureExtension> textureExtension = textureExtensionFactory.createTextureExtension();

    // Set texture using the extension object
    textureExtension->setTexture("Texture.png");

    // Render the object
    mesh->render();

    return 0;
}
/*

In the given example, the Extension Object Pattern is implemented without maintaining a 
direct pointer to the extensions in the core object. Instead, the extensions are created
 separately using their respective factories and interacted with independently.

The core object (`Mesh` in this case) remains unaware of the specific extensions attached 
to it. It only interacts with the extensions through their common interfaces
(`MaterialExtension`, `LightingExtension`, `TextureExtension`), which allows 
 for loose coupling and flexibility.

By using this approach, the core object can be extended with different combinations of 
extensions at runtime without requiring modifications to its implementation. 
The extensions can be dynamically attached or detached as needed, providing a flexible and scalable design.

However, it's important to note that the decision of whether to maintain a direct pointer
to the extensions in the core object depends on the specific requirements and design considerations
of your application. In some cases, it may be beneficial to have a direct reference to the extensions
for more direct communication and access. The design choice will depend on factors such as the 
complexity of the interactions between the core object and the extensions, the desired level of 
flexibility, and the trade-offs between loose coupling and direct control.

*/