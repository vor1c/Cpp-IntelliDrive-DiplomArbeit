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
        fonts[name] = font;
    }
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    return fonts.at(name);
}

std::vector<sf::Texture>
ResourceManager::loadImagesInBulk(std::string path, std::string prefix, std::string postfix) {
    std::vector<sf::Texture> textures;

    sf::Texture texture;

    int cnt = 01;

    while (true){
        std::string tilePath = path + prefix + (cnt < 10 ? "0" : "") + std::to_string(cnt) + postfix;
        if (!texture.loadFromFile(tilePath)) {
            break;
        }else{
            textures.emplace_back(texture);
        }
        cnt++;
    }

    return textures;
}
