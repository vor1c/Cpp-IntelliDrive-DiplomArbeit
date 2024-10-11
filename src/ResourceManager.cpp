//
// Created by Voric on 11/08/2024.
//

#include "../include/ResourceManager.h"

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadFont(const std::string& name, const std::string& filename) {
    sf::Font font;
    if (font.loadFromFile(filename)) {
        fonts[name] = std::move(font);
    } else {
        std::cerr << "Error loading font: " << filename << std::endl;
    }
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    return fonts.at(name);
}

void ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        textures[name] = std::move(texture);
    } else {
        std::cerr << "Error loading texture: " << filename << std::endl;
    }
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}

void ResourceManager::loadTexturesInBulk(const std::string& path, const std::string& prefix, const std::string& postfix) {
    bulkTextures.clear(); // Clear the vector before loading new textures -- not ChatGPT (Devrim)
    int cnt = 1;

    while (true) {
        std::string tilePath = path + prefix + (cnt < 10 ? "0" : "") + std::to_string(cnt) + postfix;
        sf::Texture texture;
        if (!texture.loadFromFile(tilePath)) {
            break;
        } else {
            bulkTextures.push_back(std::move(texture));
        }
        cnt++;
    }

    if (bulkTextures.empty()) {
        std::cerr << "No textures loaded in bulk from path: " << path << std::endl;
    }
}

const std::vector<sf::Texture>& ResourceManager::getBulkTextures() {
    return bulkTextures;
}
