#include <iostream>
#include <string>
#include <unordered_map>

// Asset service for managing assets
class AssetService {
public:
    std::string loadTexture(const std::string& filename) {
        // Simulating loading and processing of texture asset
        return "Loaded texture: " + filename;
    }

    std::string loadModel(const std::string& filename) {
        // Simulating loading and processing of model asset
        return "Loaded model: " + filename;
    }

    // Other asset loading and management methods...
};

// API Gateway for asset management
class AssetGateway {
public:
    AssetGateway() : assetService() {}

    std::string loadAsset(const std::string& type, const std::string& filename) {
        if (type == "texture") {
            return assetService.loadTexture(filename);
        }
        else if (type == "model") {
            return assetService.loadModel(filename);
        }
        else {
            return "Unsupported asset type";
        }
    }

private:
    AssetService assetService;
};

int main() {
    // Client requesting asset loading through the AssetGateway
    AssetGateway assetGateway;

    // Simulating client requests to load assets
    std::cout << assetGateway.loadAsset("texture", "texture.png") << std::endl;
    std::cout << assetGateway.loadAsset("model", "model.obj") << std::endl;
    std::cout << assetGateway.loadAsset("sound", "sound.wav") << std::endl;

    return 0;
}
