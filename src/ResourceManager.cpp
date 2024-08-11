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
